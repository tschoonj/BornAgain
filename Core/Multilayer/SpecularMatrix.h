// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.h
//! @brief     Declares class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARMATRIX_H
#define SPECULARMATRIX_H

#include "ISimulation.h" // inheriting from
#include "ScalarRTCoefficients.h"
#include "Vectors3D.h"
#include <vector>

//! @class SpecularMatrix
//! @ingroup algorithms_internal
//! @brief Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer

class BA_CORE_API_ SpecularMatrix : public ISimulation
{
public:
    //! Layer coefficients describing refraction and transmission/reflection.
    typedef std::vector<ScalarRTCoefficients> MultiLayerCoeff_t;

    //! Computes refraction angles and transmission/reflection coefficients
    //! for given coherent wave propagation in a multilayer.
    static void execute(
        const class MultiLayer& sample, const kvector_t k, MultiLayerCoeff_t& coeff);
};

#endif // SPECULARMATRIX_H