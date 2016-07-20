// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorFullSpheroid.h
//! @brief     Declares class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHEROID_H
#define FORMFACTORFULLSPHEROID_H

#include "IFormFactorBorn.h" // inheriting from
#include "IntegratorComplex.h"

//! @class FormFactorFullSpheroid
//! @ingroup formfactors
//! @brief The formfactor of a full spheroid.

class BA_CORE_API_ FormFactorFullSpheroid : public IFormFactorBorn
{
public:
    //! @brief Full Spheroid constructor
    //! @param radius of spheroid
    //! @param height of spheroid

    FormFactorFullSpheroid(double radius, double height);

    virtual ~FormFactorFullSpheroid();

    virtual FormFactorFullSpheroid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const { return m_height; }

    virtual double getRadius() const { return m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorFullSpheroid>> mP_integrator;
#endif
};

#endif // FORMFACTORFULLSPHEROID_H