#include "Layer.h"
#include <stdexcept>

/* ************************************************************************* */
Layer::Layer() : mp_material(0), m_thickness(0)
{
}


Layer::Layer(const Layer &other) : ISample(other)
{
    mp_material = other.mp_material;
    m_thickness = other.m_thickness;
}


Layer &Layer::operator=(const Layer &other)
{
    if( this != &other)
    {
        ISample::operator=(other);
        mp_material = other.mp_material;
        m_thickness = other.m_thickness;
    }
    return *this;
}


Layer::~Layer()
{

}


/* ************************************************************************* */
Layer *Layer::clone() const {
    return new Layer(*this);
}


/* ************************************************************************* */
void Layer::setThickness(double thickness)
{
    if (thickness>=0.0)
    {
        m_thickness = thickness;
        return;
    }
    throw new std::domain_error("Layer thickness cannot be negative");
}


void Layer::setMaterial(const IMaterial* p_material, double thickness)
{
    setMaterial(p_material);
    setThickness(thickness);
}
