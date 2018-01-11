// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Simulation.h"
#include "IBackground.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "IComputation.h"
#include "ParameterPool.h"
#include "ParameterSample.h"
#include "StringUtils.h"
#include <thread>
#include <gsl/gsl_errno.h>
#include <iomanip>
#include <iostream>

namespace {
size_t getIndexStep(size_t total_size, size_t n_handlers);
size_t getStartIndex(size_t n_handlers, size_t current_handler, size_t n_elements);
size_t getElementNumber(size_t n_handlers, size_t current_handler, size_t n_elements);
}

Simulation::Simulation()
{
    initialize();
}

Simulation::Simulation(const MultiLayer& p_sample)
{
    initialize();
    m_sample_provider.setSample(p_sample);
}

Simulation::Simulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
{
    initialize();
    m_sample_provider.setSampleBuilder(p_sample_builder);
}

Simulation::Simulation(const Simulation& other)
    : ICloneable()
    , m_sample_provider(other.m_sample_provider)
    , m_options(other.m_options)
    , m_distribution_handler(other.m_distribution_handler)
    , m_progress(other.m_progress)
    , m_instrument(other.m_instrument)
{
    if (other.mP_background)
        setBackground(*other.mP_background);
    initialize();
}

Simulation::~Simulation() {}

//! Initializes a progress monitor that prints to stdout.
void Simulation::setTerminalProgressMonitor()
{
    m_progress.subscribe( [] (size_t percentage_done) -> bool {
            if (percentage_done<100)
                std::cout << std::setprecision(2)
                          << "\r... " << percentage_done << "%" << std::flush;
            else // wipe out
                std::cout << "\r... 100%\n";
            return true;
    } );
}

void Simulation::setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function)
{
    m_instrument.setDetectorResolutionFunction(resolution_function);
}

void Simulation::removeDetectorResolutionFunction()
{
    m_instrument.removeDetectorResolution();
}

//! Sets the polarization analyzer characteristics of the detector
void Simulation::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                       double total_transmission)
{
    m_instrument.setAnalyzerProperties(direction, efficiency, total_transmission);
}

void Simulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

double Simulation::getBeamIntensity() const
{
    return m_instrument.getBeamIntensity();
}

//! Sets the beam polarization according to the given Bloch vector
void Simulation::setBeamPolarization(const kvector_t bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

void Simulation::prepareSimulation()
{
    updateSample();
    if (!m_sample_provider.sample()->containsCompatibleMaterials())
        throw std::runtime_error("Error in Simulation::prepareSimulation(): non-default materials of "
                                 "several types are used in the sample provided");
    gsl_set_error_handler_off();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    prepareSimulation();

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    m_progress.reset();
    size_t prefactor = ( sample()->totalNofLayouts()>0 ? 1 : 0 )
        + ( sample()->hasRoughness() ? 1 : 0 );
    m_progress.setExpectedNTicks(prefactor*param_combinations*numberOfSimulationElements());

    // no averaging needed:
    if (param_combinations == 1) {
        std::unique_ptr<ParameterPool> P_param_pool(createParameterTree());
        m_distribution_handler.setParameterValues(P_param_pool.get(), 0);
        runSingleSimulation();
        transferResultsToIntensityMap();
        return;
    }

    // average over parameter distributions:
    std::unique_ptr<ParameterPool> P_param_pool(createParameterTree());
    const bool use_storage = true;
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(P_param_pool.get(), index);
        runSingleSimulation(use_storage, weight);
    }
    moveDataFromStorage();
    transferResultsToIntensityMap();
}

/* currently unused
void Simulation::runOMPISimulation()
{
    OMPISimulation ompi;
    ompi.runSimulation(this);
}
*/

void Simulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMap();
}

//! The MultiLayer object will not be owned by the Simulation object
void Simulation::setSample(const MultiLayer& sample)
{
    m_sample_provider.setSample(sample);
}

const MultiLayer* Simulation::sample() const
{
    return m_sample_provider.sample();
}

void Simulation::setSampleBuilder(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder)
{
    m_sample_provider.setSampleBuilder(p_sample_builder);
}

void Simulation::setBackground(const IBackground& bg)
{
    mP_background.reset(bg.clone());
    registerChild(mP_background.get());
}

std::vector<const INode*> Simulation::getChildren() const
{
    std::vector<const INode*> result;
    result.push_back(&m_instrument);
    result << m_sample_provider.getChildren();
    if (mP_background)
        result.push_back(mP_background.get());
    return result;
}

void Simulation::addParameterDistribution(const std::string& param_name,
                                          const IDistribution1D& distribution, size_t nbr_samples,
                                          double sigma_factor, const RealLimits& limits)
{
    m_distribution_handler.addParameterDistribution(
        param_name, distribution, nbr_samples, sigma_factor, limits);
}

void Simulation::addParameterDistribution(const ParameterDistribution& par_distr)
{
    m_distribution_handler.addParameterDistribution(par_distr);
}

void Simulation::updateSample()
{
    m_sample_provider.updateSample();
}

//! Runs a single simulation with fixed parameter values.
//! If desired, the simulation is run in several threads.
void Simulation::runSingleSimulation(bool use_storage, double weight)
{
    prepareSimulation();
    initSimulationElementVector(use_storage && !isStorageInited());

    // restrict calculation to current batch
    const size_t n_batches = m_options.getNumberOfBatches();
    const size_t current_batch = m_options.getCurrentBatch();
    const size_t total_size = numberOfSimulationElements();

    const size_t batch_start = getStartIndex(n_batches, current_batch, total_size);
    const size_t batch_size = getElementNumber(n_batches, current_batch, total_size);
    if (batch_size == 0)
        return;

    const size_t n_threads = m_options.getNumberOfThreads();

    if (n_threads == 1) {
        // Single thread.
        auto P_computation = generateSingleThreadedComputation(batch_start, batch_size);
        P_computation->run(); // the work is done here
        if (!P_computation->isCompleted()) {
            std::string message = P_computation->errorMessage();
            throw Exceptions::RuntimeErrorException("Simulation::runSimulation() -> Simulation has "
                                                    "terminated unexpectedly with following error "
                                                    "message.\n" + message);
        }
    } else {
        // Multithreading.
        std::vector<std::unique_ptr<std::thread>> threads;
        std::vector<std::unique_ptr<IComputation>> computations;

        // Distribute computations on the threads.
        for (size_t i_thread = 0; i_thread < n_threads; ++i_thread) {
            const size_t thread_start = batch_start + getStartIndex(n_threads, i_thread, batch_size);
            const size_t thread_size = getElementNumber(n_threads, i_thread, batch_size);
            if (thread_size == 0)
                break;
            computations.push_back(generateSingleThreadedComputation(thread_start, thread_size));
        }

        // Run simulations in n threads.
        for (auto& comp: computations)
            threads.emplace_back(new std::thread([&comp]() {comp->run();}));

        // Wait for threads to complete.
        for (auto& thread: threads) {
            thread->join();
        }

        // Check successful completion.
        std::vector<std::string> failure_messages;
        for (auto& comp: computations) {
            if (!comp->isCompleted())
                failure_messages.push_back(comp->errorMessage());
        }
        if (failure_messages.size())
            throw Exceptions::RuntimeErrorException(
                "Simulation::runSingleSimulation() -> "
                "At least one simulation thread has terminated unexpectedly.\n"
                "Messages: " + StringUtils::join(failure_messages, " --- "));
    }
    normalize(batch_start, batch_size);
    addBackGroundIntensity(batch_start, batch_size);
    if (use_storage)
        addDataToStorage(weight);
}

void Simulation::normalize(size_t start_ind, size_t n_elements)
{
    const double beam_intensity = getBeamIntensity();
    if (beam_intensity == 0.0)
        return; // no normalization when beam intensity is zero
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i)
        normalizeIntensity(i, beam_intensity);
}

void Simulation::initialize()
{
    registerChild(&m_instrument);
    registerChild(&m_sample_provider);
}

namespace {
size_t getIndexStep(size_t total_size, size_t n_handlers)
{
    assert(total_size > 0);
    assert(n_handlers > 0);
    size_t result = total_size / n_handlers;
    return total_size % n_handlers ? ++result : result;
}

size_t getStartIndex(size_t n_handlers, size_t current_handler, size_t n_elements)
{
    const size_t handler_size = getIndexStep(n_elements, static_cast<size_t>(n_handlers));
    const size_t start_index = current_handler * handler_size;
    if (start_index >= n_elements)
        return n_elements;
    return start_index;
}

size_t getElementNumber(size_t n_handlers, size_t current_handler, size_t n_elements)
{
    const size_t handler_size = getIndexStep(n_elements, static_cast<size_t>(n_handlers));
    const size_t start_index = current_handler * handler_size;
    if (start_index >= n_elements)
        return 0;
    return std::min(handler_size, n_elements - start_index);
}
}
