// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataModel.cpp
//! @brief     Implements class RealDataModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataModel.h"
#include "ImportDataAssistant.h"
#include "RealDataItem.h"

RealDataModel::RealDataModel(QObject *parent)
    : SessionModel(SessionXML::RealDataModelTag, parent)
{
    setObjectName(SessionXML::RealDataModelTag);
}

//Qt::ItemFlags RealDataModel::flags(const QModelIndex &index) const
//{
//    Qt::ItemFlags result_flags =  SessionModel::flags(index);
//    result_flags |= Qt::ItemIsEditable;
//    return result_flags;
//}


QVector<SessionItem *> RealDataModel::nonXMLData() const
{
    QVector<SessionItem *> result;

    for (auto realData : topItems(Constants::RealDataType)) {
        if (auto intensityItem = realData->getItem(RealDataItem::T_INTENSITY_DATA))
            result.push_back(intensityItem);
    }

    return result;
}
