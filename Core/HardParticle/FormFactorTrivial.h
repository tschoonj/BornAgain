// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTrivial.h
//! @brief     Defines class FormFactorTrivial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRIVIAL_H
#define FORMFACTORTRIVIAL_H

#include "IFormFactorBorn.h"

//! @class FormFactorTrivial
//! @ingroup formfactors
//! @brief A uniform formfactor F(q)=1, for development purposes.

class BA_CORE_API_ FormFactorTrivial : public IFormFactorBorn
{
public:
    FormFactorTrivial();

    FormFactorTrivial* clone() const { return new FormFactorTrivial(); }

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    double getRadialExtension() const final { return 0; }

    complex_t evaluate_for_q(const cvector_t) const final { return 1; }
};

#endif // FORMFACTORTRIVIAL_H
