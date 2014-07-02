// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTruncatedSpheroid.cpp
//! @brief     Implements class FormFactorTruncatedSpheroid.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedSpheroid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(double radius, double height, double height_flattening)
{
    setName("FormFactorTruncatedSpheroid");
    m_radius = radius;
    m_height = height;
    m_height_flattening = height_flattening;
    assert(m_height <= 2.*m_radius*m_height_flattening);
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorTruncatedSpheroid>::mem_function p_mf =
       & FormFactorTruncatedSpheroid::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorTruncatedSpheroid>(p_mf, this);
 }

void FormFactorTruncatedSpheroid::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
    registerParameter("height_flattening", &m_height_flattening);
}

FormFactorTruncatedSpheroid* FormFactorTruncatedSpheroid::clone() const
{
   FormFactorTruncatedSpheroid* result =
       new FormFactorTruncatedSpheroid(m_radius, m_height, m_height_flattening);
   result->setName(getName());
   return result;
}

//! Integrand for complex formfactor.
complex_t FormFactorTruncatedSpheroid::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    double R = m_radius;
    double fp = m_height_flattening;

    double Rz  = std::sqrt(R*R-Z*Z/(fp*fp));
    complex_t qrRz = m_q.magxy()*Rz;
    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_C1(qrRz);

    return Rz * Rz * J1_qrRz_div_qrRz * std::exp(complex_t(0.0,1.0)*m_q.z()*Z);
}

complex_t FormFactorTruncatedSpheroid::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double R = m_radius;
    double fp = m_height_flattening;
    m_q = q;

    if (std::abs(m_q.mag()) <= Numeric::double_epsilon) {

        return M_PI*R*H*H/fp*(1.-H/(3.*fp*R));

    } else {

        complex_t z_part    =  std::exp(complex_t(0.0, 1.0)*m_q.z()*(H-fp*R));

        return 2.0* M_PI * z_part *m_integrator->integrate(fp*R-H,fp*R );
    }
}




