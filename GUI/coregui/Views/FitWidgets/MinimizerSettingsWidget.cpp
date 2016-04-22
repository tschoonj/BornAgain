// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/MinimizerSettingsWidget.cpp
//! @brief     Implements class MinimizerSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MinimizerSettingsWidget.h"
#include "ObsoleteFitModel.h"
#include "ComponentEditor.h"
#include "FitParameterItems.h"
#include <QHBoxLayout>
#include <QSplitter>

MinimizerSettingsWidget::MinimizerSettingsWidget(ObsoleteFitModel *fitModel, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    ComponentEditor *editor = new ComponentEditor;
    editor->setItem(fitModel->getMinimizerSettings());
    layout->addWidget(editor);
    setLayout(layout);
}
