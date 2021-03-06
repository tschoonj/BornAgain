// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ChiSquaredModule.h
//! @brief     Defines class ChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CHISQUAREDMODULE_H
#define CHISQUAREDMODULE_H

#include "IChiSquaredModule.h"

//! Calculation of chi2 between two data sets.
//! @ingroup fitting

class BA_CORE_API_ ChiSquaredModule : public IChiSquaredModule
{
public:
    ChiSquaredModule() {}
    ChiSquaredModule(const ChiSquaredModule& other)
        : IChiSquaredModule(other) {}
    virtual ~ChiSquaredModule() {}

    virtual ChiSquaredModule *clone() const { return new ChiSquaredModule(*this); }

    virtual void processFitElements(std::vector<FitElement>::iterator first,
                                    std::vector<FitElement>::iterator last);
};

#endif // CHISQUAREDMODULE_H
