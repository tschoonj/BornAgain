// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorToolBar.h
//! @brief     Defines class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKEDITORTOOLBAR_H
#define MASKEDITORTOOLBAR_H

#include "MaskEditorFlags.h"
#include "WinDllMacros.h"
#include <QToolBar>

class MaskEditorActions;
class QButtonGroup;

//! Main class to draw masks on top of intensity data map

class BA_CORE_API_ MaskEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaskEditorToolBar(MaskEditorActions *editorActions, QWidget *parent = 0);

signals:
    void activityModeChanged(MaskEditorFlags::Activity);
    void presentationTypeRequest(MaskEditorFlags::PresentationType);
    void maskValueChanged(MaskEditorFlags::MaskValue);

public slots:
    void onChangeActivityRequest(MaskEditorFlags::Activity value);

private slots:
    void onActivityGroupChange(int value);
    void onMaskValueGroupChange(int value);
    void onPresentationTypePressed();
    void onPresentationTypeReleased();

private:
    void setup_selection_group();
    void setup_maskvalue_group();
    void setup_shapes_group();
    void setup_maskmodify_group();
    void setup_extratools_group();
    void add_separator();

    MaskEditorFlags::Activity currentActivity() const;
    void setCurrentActivity(MaskEditorFlags::Activity value);

    MaskEditorActions *m_editorActions;
    QButtonGroup *m_activityButtonGroup;
    QButtonGroup *m_maskValueGroup;
    MaskEditorFlags::Activity m_previousActivity;
};


#endif // MASKEDITORTOOLBAR_H
