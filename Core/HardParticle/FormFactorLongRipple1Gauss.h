// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongRipple1Gauss.h
//! @brief     Defines class FormFactorLongRipple1Gauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLONGRIPPLE1GAUSS_H
#define FORMFACTORLONGRIPPLE1GAUSS_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

//! @class FormFactorLongRipple1Gauss
//! @ingroup formfactors
//! @brief The formfactor for a cosine ripple.

class BA_CORE_API_ FormFactorLongRipple1Gauss : public IFormFactorBorn
{
public:
    //! @brief Ripple1 constructor
    //! @param length of Ripple1
    //! @param width of cosine cross section
    //! @param height of cosine cross section
    FormFactorLongRipple1Gauss(double length, double width, double height);
    virtual ~FormFactorLongRipple1Gauss() {}

    FormFactorLongRipple1Gauss* clone() const {
        return new FormFactorLongRipple1Gauss(m_length, m_width, m_height); }
    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getLength() const { return m_length; }

    double getRadialExtension() const final;

    complex_t evaluate_for_q(const cvector_t q) const final;

protected:
    virtual bool check_initialization() const;

private:
    complex_t Integrand(double Z) const;

    double m_length;
    double m_width;
    double m_height;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorLongRipple1Gauss>> mP_integrator;
#endif
};

#endif // FORMFACTORLONGRIPPLE1GAUSS_H
