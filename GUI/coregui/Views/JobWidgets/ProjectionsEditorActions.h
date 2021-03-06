// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.h
//! @brief     Defines class ProjectionsEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSEDITORACTIONS_H
#define PROJECTIONSEDITORACTIONS_H

#include "WinDllMacros.h"
#include <QObject>
#include <QList>
#include <QModelIndex>

class SessionModel;
class QItemSelectionModel;
class QAction;

//! Provides various actions for ProjectionsEditor.

class BA_CORE_API_ ProjectionsEditorActions : public QObject
{
    Q_OBJECT

public:
    ProjectionsEditorActions(QWidget* parent = 0);

    void setModel(SessionModel* maskModel, const QModelIndex& rootIndex);
    void setSelectionModel(QItemSelectionModel* selectionModel);

    QList<QAction*> topToolBarActions();

public slots:
    void onDeleteAction();

signals:
    void resetViewRequest();
    void propertyPanelRequest();

private:
    QAction* m_resetViewAction;
    QAction* m_togglePanelAction;
    QAction* m_deleteAction;
    SessionModel *m_model;
    QModelIndex m_rootIndex; //! Index in the model corresponding to IntensityDataItem
    QItemSelectionModel *m_selectionModel;
};

#endif // PROJECTIONSEDITORACTIONS_H
