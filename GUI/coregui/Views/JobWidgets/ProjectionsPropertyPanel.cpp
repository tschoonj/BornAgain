// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsPropertyPanel.cpp
//! @brief     Implements class ProjectionsPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsPropertyPanel.h"
#include "ComponentEditor.h"
#include <QVBoxLayout>

ProjectionsPropertyPanel::ProjectionsPropertyPanel(QWidget* parent)
    : SessionItemWidget(parent)
    , m_componentEditor(new ComponentEditor)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_componentEditor);
    setLayout(mainLayout);
}

QSize ProjectionsPropertyPanel::sizeHint() const
{
    return QSize(230, 256);
}

QSize ProjectionsPropertyPanel::minimumSizeHint() const
{
    return QSize(230, 64);
}

void ProjectionsPropertyPanel::subscribeToItem()
{
    m_componentEditor->setItem(currentItem());
}

void ProjectionsPropertyPanel::unsubscribeFromItem()
{
    m_componentEditor->setItem(nullptr);
}
