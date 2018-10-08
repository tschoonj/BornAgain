// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleViewActions.h
//! @brief     Implements class SampleViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleViewActions.h"

SampleViewActions::SampleViewActions(SampleModel* model, QObject* parent)
    : QObject(parent)
    , m_model(model)
    , m_selection_model(nullptr)
{

}

void SampleViewActions::setSelectionModel(QItemSelectionModel* selection_model)
{
    m_selection_model = selection_model;
}
