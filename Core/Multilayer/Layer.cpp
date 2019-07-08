// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Layer.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "ILayout.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include "MaterialUtils.h"

#include <set>

//! Constructor of a layer with thickness and material
//! @param material: material the layer is made of
//! @param thickness: thickness of a layer in nanometers
Layer::Layer(Material material, double thickness)
    : m_material(std::move(material))
    , m_thickness(thickness)
{
    setName(BornAgain::LayerType);
    registerThickness();
}

Layer::~Layer()
{}

Layer* Layer::clone() const
{
    Layer* p_result = shallowClone();
    p_result->m_n_slices = m_n_slices;
    for (auto p_layout : layouts())
        p_result->addLayout(*p_layout);
    return p_result;
}

Layer* Layer::cloneInvertB() const
{
    Layer* p_result = shallowClone();
    p_result->m_B_field = -m_B_field;
    return p_result;
}

//! Sets layer thickness in nanometers.
void Layer::setThickness(double thickness)
{
    if (thickness < 0.)
        throw Exceptions::DomainErrorException("Layer thickness cannot be negative");
    m_thickness = thickness;
}

void Layer::setMaterial(Material material)
{
    m_material = std::move(material);
}

void Layer::addLayout(const ILayout& layout)
{
    ILayout* clone = layout.clone();
    m_layouts.push_back(clone);
    registerChild(clone);
}

std::vector<const ILayout*> Layer::layouts() const
{
    std::vector<const ILayout*> result;
    for (auto p_layout : m_layouts)
        result.push_back(p_layout);
    return result;
}

std::vector<const INode*> Layer::getChildren() const
{
    std::vector<const INode*> result;
    for(auto layout : m_layouts)
        result.push_back(layout);
    return result;
}

void Layer::registerThickness(bool make_registered)
{
    if(make_registered) {
        if(!parameter(BornAgain::Thickness))
            registerParameter(BornAgain::Thickness, &m_thickness).setUnit(BornAgain::UnitsNm)
                .setNonnegative();
    } else {
        removeParameter(BornAgain::Thickness);
    }
}

complex_t Layer::scalarReducedPotential(kvector_t k, double n_ref) const
{
    complex_t n = m_material.refractiveIndex(2.0 * M_PI / k.mag());
    return MaterialUtils::ScalarReducedPotential(n, k, n_ref);
}

Eigen::Matrix2cd Layer::polarizedReducedPotential(kvector_t k, double n_ref) const
{
    complex_t n = m_material.refractiveIndex(2.0 * M_PI / k.mag());
    kvector_t b_field = bField();
    return MaterialUtils::PolarizedReducedPotential(n, b_field, k, n_ref);
}

void Layer::initBField(kvector_t h_field, double b_z)
{
    m_B_field = Magnetic_Permeability*(h_field + m_material.magnetization());
    m_B_field.setZ(b_z);
}

Layer* Layer::shallowClone() const
{
    Layer* p_result = new Layer(m_material, m_thickness);
    p_result->setName(getName());
    p_result->m_B_field = m_B_field;
    return p_result;
}

kvector_t Layer::bField() const
{
    return m_B_field;
}
