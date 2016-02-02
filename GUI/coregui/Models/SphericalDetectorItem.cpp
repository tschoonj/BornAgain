// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SphericalDetectorItem.cpp
//! @brief     Implements class SphericalDetectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SphericalDetectorItem.h"
#include "AxesItems.h"
#include "VectorItem.h"
#include "GUIHelpers.h"
#include "SphericalDetector.h"
#include "ResolutionFunctionItems.h"

const QString SphericalDetectorItem::P_PHI_AXIS = "Phi axis";
const QString SphericalDetectorItem::P_ALPHA_AXIS = "Alpha axis";
const QString SphericalDetectorItem::P_RESOLUTION_FUNCTION = "Type";

SphericalDetectorItem::SphericalDetectorItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::SphericalDetectorType, parent)
{
    registerGroupProperty(P_PHI_AXIS, Constants::BasicAxisType);
    getSubItems()[P_PHI_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_PHI_AXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, -1.0);
    getSubItems()[P_PHI_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 1.0);

    registerGroupProperty(P_ALPHA_AXIS, Constants::BasicAxisType);
    getSubItems()[P_ALPHA_AXIS]->getPropertyAttribute(BasicAxisItem::P_TITLE).setHidden();
    getSubItems()[P_ALPHA_AXIS]->setRegisteredProperty(BasicAxisItem::P_MIN, 0.0);
    getSubItems()[P_ALPHA_AXIS]->setRegisteredProperty(BasicAxisItem::P_MAX, 2.0);

    registerGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionGroup);
    setGroupProperty(P_RESOLUTION_FUNCTION, Constants::ResolutionFunctionNoneType);
}

std::unique_ptr<IDetector2D> SphericalDetectorItem::createDetector() const
{

//    return GUIHelpers::make_unique<SphericalDetector>();
//    std::unique_ptr<SphericalDetector> result = GUIHelpers::make_unique<SphericalDetector>();
    std::unique_ptr<SphericalDetector> result(new SphericalDetector());

    auto x_axis = dynamic_cast<BasicAxisItem *>(
        getSubItems()[SphericalDetectorItem::P_PHI_AXIS]);
    Q_ASSERT(x_axis);
    int n_x = x_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
    double x_min
        = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
    double x_max
        = Units::deg2rad(x_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

    auto y_axis = dynamic_cast<BasicAxisItem *>(
        getSubItems()[SphericalDetectorItem::P_ALPHA_AXIS]);
    Q_ASSERT(y_axis);
    int n_y = y_axis->getRegisteredProperty(BasicAxisItem::P_NBINS).toInt();
    double y_min
        = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MIN).toDouble());
    double y_max
        = Units::deg2rad(y_axis->getRegisteredProperty(BasicAxisItem::P_MAX).toDouble());

    result->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);

    return std::move(result);
}

std::unique_ptr<IResolutionFunction2D> SphericalDetectorItem::createResolutionFunction()
{
    // setting up resolution function
    auto resfuncItem = dynamic_cast<ResolutionFunctionItem *>(
        getSubItems()[P_RESOLUTION_FUNCTION]);
    Q_ASSERT(resfuncItem);

    std::unique_ptr<IResolutionFunction2D> result(resfuncItem->createResolutionFunction(Units::degree));

    return std::move(result);
}






