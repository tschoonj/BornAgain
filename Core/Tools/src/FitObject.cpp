#include "FitObject.h"
#include "Exceptions.h"


/* ************************************************************************* */
// FitObject c-tors
/* ************************************************************************* */
FitObject::FitObject(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module, double weight)
    : m_experiment(experiment.clone())
    , m_real_data(real_data.clone())
    , m_chi2_module(chi2_module.clone())
    , m_weight(weight)
{
    setName("FitObject");
    if( !m_real_data->hasSameShape(*m_experiment->getOutputData()) ) {
        std::cout << "FitObject::FitObject() -> Info. Real data and output data in the experiment have different shape. Adjusting experiment's detector." << std::endl;
    } else {
        std::cout << "FitObject::FitObject() -> Info. Real data and output data in the experiment have same shape. Ok." << std::endl;
    }
    m_experiment->setDetectorParameters(*m_real_data);
}

FitObject::~FitObject()
{
}


/* ************************************************************************* */
// set real data
/* ************************************************************************* */
void FitObject::setRealData(const OutputData<double > &real_data)
{
    delete m_real_data;
    m_real_data = real_data.clone();
    if( m_experiment) {
        if( !m_real_data->hasSameShape(*m_experiment->getOutputData()) ) {
            std::cout << "FitObject::setRealData() -> Real data and the detector have different shape. Adjusting detector..." << std::endl;
        } else {
            std::cout << "FitObject::setRealData() -> Real data and the detector have same shape. No need to adjust detector." << std::endl;
        }
        m_experiment->setDetectorParameters(*m_real_data);
    }
}


/* ************************************************************************* */
// calculate chi squared value
/* ************************************************************************* */
double FitObject::calculateChiSquared()
{
    m_chi2_module->setRealAndSimulatedData(*m_real_data, *m_experiment->getOutputData());
    return m_chi2_module->calculateChiSquared();
}


/* ************************************************************************* */
// add parameters from local pool to external pool
/* ************************************************************************* */
std::string FitObject::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the experiment
    if(m_experiment) m_experiment->addParametersToExternalPool(new_path, external_pool, -1);

    if(m_chi2_module) {
        const IOutputDataNormalizer *data_normalizer = m_chi2_module->getOutputDataNormalizer();
        if(data_normalizer) {
            data_normalizer->addParametersToExternalPool(new_path, external_pool, -1);
        }
    }

    return new_path;
}


void FitObject::init_parameters()
{

}
