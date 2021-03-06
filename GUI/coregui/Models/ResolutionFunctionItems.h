// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ResolutionFunctionItems.h
//! @brief     Defines family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef RESOLUTIONFUNCTIONITEMS_H
#define RESOLUTIONFUNCTIONITEMS_H

#include "SessionItem.h"
#include <memory>

class IResolutionFunction2D;

class BA_CORE_API_ ResolutionFunctionItem : public SessionItem
{

public:
    explicit ResolutionFunctionItem(const QString& name);
    virtual ~ResolutionFunctionItem() {}

    virtual std::unique_ptr<IResolutionFunction2D>
        createResolutionFunction(double scale = 1.0) const = 0;
};

class BA_CORE_API_ ResolutionFunctionNoneItem : public ResolutionFunctionItem
{

public:
    ResolutionFunctionNoneItem();
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction(double scale = 1.0) const;
};

class BA_CORE_API_ ResolutionFunction2DGaussianItem : public ResolutionFunctionItem
{

public:
    static const QString P_SIGMA_X;
    static const QString P_SIGMA_Y;
    ResolutionFunction2DGaussianItem();
    std::unique_ptr<IResolutionFunction2D> createResolutionFunction(double scale = 1.0) const;
};

#endif // RESOLUTIONFUNCTIONITEMS_H

