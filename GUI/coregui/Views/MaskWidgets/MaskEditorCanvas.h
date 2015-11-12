// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorCanvas.h
//! @brief     Defines class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORCANVAS_H
#define MASKEDITORCANVAS_H

#include "MaskEditorActivity.h"
#include <QWidget>

class MaskGraphicsScene;
class MaskGraphicsView;
class MaskGraphicsProxy;
class SessionModel;
class QItemSelectionModel;
class QModelIndex;

//! Painting widget for MaskEditor

class MaskEditorCanvas : public QWidget
{
    Q_OBJECT
public:
    MaskEditorCanvas(QWidget *parent = 0);

    void setModel(SessionModel *model, const QModelIndex &rootIndex);
    void setSelectionModel(QItemSelectionModel *model);

signals:
    void changeActivityRequest(MaskEditorActivity::Flags);

public slots:
    void onActivityModeChanged(MaskEditorActivity::Flags value);

private:
    MaskGraphicsScene *m_scene;
    MaskGraphicsView *m_view;
};


#endif
