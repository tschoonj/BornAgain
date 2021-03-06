// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsWidget.h
//! @brief     Defines class ProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSWIDGET_H
#define PROJECTIONSWIDGET_H

#include "SessionItemWidget.h"
#include "MaskEditorFlags.h"

class ProjectionsPlot;
class QTabWidget;

//! Holds tabs of vertical and horizontal projections, located at the bottom of ProjectionsEditor.

class BA_CORE_API_ ProjectionsWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    enum ETabId {HORIZONTAL, VERTICAL};

    ProjectionsWidget(QWidget* parent = 0);
    void setItem(SessionItem* intensityItem);

public slots:
    void onActivityModeChanged(MaskEditorFlags::Activity value);
    void onMarginsChanged(double left, double right);

private:
    ProjectionsPlot* m_xProjection;
    ProjectionsPlot* m_yProjection;
    QTabWidget* m_tabWidget;
};

#endif // PROJECTIONSWIDGET_H
