// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorHemiEllipsoid.cpp
//! @brief     Implements class FormFactorHemiEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorHemiEllipsoid.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "TruncatedEllipsoid.h"
#include <limits>

//! Constructor of horizontally oriented ellipsoid, truncated at the central plane.
//! @param radius_x: radius of the ellipse base in the x-direction, in nanometers
//! @param radius_y: radius of the ellipse base in the y-direction, in nanometers
//! @param height: height of the hemi ellipsoid in nanometers
FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(double radius_x, double radius_y, double height)
    : m_radius_x(radius_x), m_radius_y(radius_y), m_height(height)
{
    setName(BornAgain::FFHemiEllipsoidType);
    registerParameter(BornAgain::RadiusX, &m_radius_x).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::RadiusY, & m_radius_y).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    mP_integrator = make_integrator_complex(this, &FormFactorHemiEllipsoid::Integrand);
    onChange();
}

double FormFactorHemiEllipsoid::radialExtension() const
{
    return ( m_radius_x + m_radius_y ) / 2.0;
}

//! Integrand for complex formfactor.
complex_t FormFactorHemiEllipsoid::Integrand(double Z) const
{
    double R = m_radius_x;
    double W = m_radius_y;
    double H = m_height;

    double Rz = R * std::sqrt(1.0 - Z*Z/(H*H));
    double Wz = W * std::sqrt(1.0 - Z*Z/(H*H));

    complex_t qxRz = m_q.x()*Rz;
    complex_t qyWz = m_q.y()*Wz;

    complex_t gamma = std::sqrt(qxRz*qxRz + qyWz*qyWz);
    complex_t J1_gamma_div_gamma = MathFunctions::Bessel_J1c(gamma);

    return Rz * Wz * J1_gamma_div_gamma * exp_I(m_q.z()*Z);
}

complex_t FormFactorHemiEllipsoid::evaluate_for_q(cvector_t q) const
{
     m_q = q;
     double R = m_radius_x;
     double W = m_radius_y;
     double H = m_height;

     if (std::abs(m_q.mag()) <= std::numeric_limits<double>::epsilon())
         return M_TWOPI*R*W*H/3.;
     return M_TWOPI*mP_integrator->integrate(0.,H );
}

void FormFactorHemiEllipsoid::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_radius_x, m_radius_x, m_height, m_height, 0.0));
}
