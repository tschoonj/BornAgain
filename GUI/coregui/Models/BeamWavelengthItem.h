// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamWavelengthItem.h
//! @brief     Defines class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BEAMWAVELENGTHITEM_H
#define BEAMWAVELENGTHITEM_H

#include "BeamDistributionItem.h"

class BA_CORE_API_ BeamWavelengthItem : public BeamDistributionItem
{
public:
    BeamWavelengthItem();

    double wavelength() const;
};

#endif // BEAMWAVELENGTHITEM_H
