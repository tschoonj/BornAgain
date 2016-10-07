// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerStrategyBuilder.cpp
//! @brief     Implements class LayerStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerStrategyBuilder.h"
#include "Exceptions.h"
#include "FormFactorInfo.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "ILayout.h"
#include "IParticle.h"
#include "InterferenceFunctionNone.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "DecouplingApproximationStrategy.h"
#include "SizeSpacingCorrelationApproximationStrategy.h"

LayerStrategyBuilder::LayerStrategyBuilder(
    const Layer& decorated_layer, const MultiLayer& sample,
    const SimulationOptions& sim_params, size_t layout_index)
    : m_sim_params{sim_params}, mP_specular_info{nullptr}, m_layout_index{layout_index}
{
    mP_layer.reset(decorated_layer.clone());
    mP_sample.reset(sample.clone());
    assert(mP_layer->getNumberOfLayouts() > 0);
}

LayerStrategyBuilder::~LayerStrategyBuilder() {}

void LayerStrategyBuilder::setRTInfo(const LayerSpecularInfo& specular_info)
{
    mP_specular_info.reset(specular_info.clone());
}

IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy()
{
    collectFormFactorInfos();
    collectInterferenceFunction();
    IInterferenceFunctionStrategy* p_result(nullptr);
    switch (mP_layer->getLayout(m_layout_index)->getApproximation())
    {
    case ILayout::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params);
        break;
    case ILayout::SSCA:
    {
        if (!mP_interference_function)
            throw Exceptions::ClassInitializationException(
                    "SSCA requires an interference function");
        double kappa = mP_interference_function->getKappa();
        if (kappa<=0.0)
            throw Exceptions::ClassInitializationException(
                    "SSCA requires a strictly positive coupling value");
        p_result = new SizeSpacingCorrelationApproximationStrategy(m_sim_params, kappa);
        break;
    }
    default:
        throw Exceptions::ClassInitializationException(
            "Unknown interference function approximation");
    }
    if (!p_result)
        throw Exceptions::ClassInitializationException(
            "Could not create appropriate strategy");
    p_result->init(m_ff_infos, *mP_interference_function);
    p_result->setSpecularInfo(*mP_specular_info);
    return p_result;
}

bool LayerStrategyBuilder::requiresMatrixFFs() const
{
    return mP_sample->containsMagneticMaterial();
}

void LayerStrategyBuilder::collectFormFactorInfos()
{
    assert(mP_layer->getNumberOfLayouts()>0);
    m_ff_infos.clear();
    const ILayout* p_layout = mP_layer->getLayout(m_layout_index);
    const IMaterial* p_layer_material = mP_layer->getMaterial();
    double total_abundance = mP_layer->getTotalAbundance();
    if (total_abundance<=0.0)
        total_abundance = 1.0;
    for (const IParticle* particle: p_layout->getParticles()) {
        FormFactorInfo* p_ff_info;
        p_ff_info = createFormFactorInfo(particle, p_layer_material);
        p_ff_info->m_abundance /= total_abundance;
        m_ff_infos.push_back(p_ff_info);
    }
    return;
}

void LayerStrategyBuilder::collectInterferenceFunction()
{
    assert(mP_layer->getNumberOfLayouts()>0);
    const IInterferenceFunction* p_iff =
        mP_layer->getLayout(m_layout_index)->getInterferenceFunction();
    if (p_iff)
        mP_interference_function.reset(p_iff->clone());
    else
        mP_interference_function.reset( new InterferenceFunctionNone() );
}

FormFactorInfo* LayerStrategyBuilder::createFormFactorInfo(
    const IParticle* particle, const IMaterial* p_ambient_material) const
{
    const std::unique_ptr<IParticle> P_particle_clone(particle->clone());
    P_particle_clone->setAmbientMaterial(*p_ambient_material);

    // formfactor
    const std::unique_ptr<IFormFactor> P_ff_particle(P_particle_clone->createFormFactor());
    IFormFactor* p_ff_framework;
    size_t n_layers = mP_layer->getNumberOfLayers();
    if (n_layers>1) {
        if (requiresMatrixFFs())
            p_ff_framework = new FormFactorDWBAPol(*P_ff_particle);
        else
            p_ff_framework = new FormFactorDWBA(*P_ff_particle);
    } else
        p_ff_framework = P_ff_particle->clone();

    return new FormFactorInfo(p_ff_framework, particle->getAbundance());
}