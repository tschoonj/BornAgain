// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TestView.h"
#include "AccordionWidget.h"
#include "JobModel.h"
#include "MaskEditor.h"
#include "MaterialEditor.h"
#include "MinimizerItem.h"
#include "MinimizerSettingsWidget.h"
#include "mainwindow.h"

#ifdef BORNAGAIN_OPENGL
#include "RealSpaceWidget.h"
#endif

#include <QCheckBox>
#include <QLineEdit>

TestView::TestView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
{
//    test_MaterialEditor();
//    test_MinimizerSettings();
//    test_AccordionWidget();
//    test_RunFitWidget();
    test_ba3d();
}


void TestView::test_MaterialEditor()
{
    MaterialEditor *materialEditor = new MaterialEditor(m_mainWindow->materialModel());
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(materialEditor);
    setLayout(layout);
}

void TestView::test_MinimizerSettings()
{
    MinimizerSettingsWidget *widget = new MinimizerSettingsWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(widget);
    setLayout(layout);

    SessionModel* model = new SessionModel("TempModel", this);
    MinimizerContainerItem *minimizerItem = dynamic_cast<MinimizerContainerItem *>(
                model->insertNewItem(Constants::MinimizerContainerType));
    widget->setItem(minimizerItem);

}

void TestView::test_AccordionWidget()
{
    AccordionWidget *myAccordion = new AccordionWidget();
    myAccordion->setMultiActive(true);
    // add the Accordion to your layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myAccordion);
    setLayout(layout);

    // add a content pane with a header
    int firstPaneIndex = myAccordion->addContentPane("My first content pane");
    // make sure our content pane was added
    if (firstPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(firstPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        contentFrame->layout()->addWidget(new QLabel("Hello Cute World!!!"));
    }

    // add a content pane with a header
    int secondPaneIndex = myAccordion->addContentPane("Basic settings");
    // make sure our content pane was added
    if (secondPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(secondPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QLineEdit *led = new QLineEdit();
        QLineEdit *led2 = new QLineEdit();
        contentFrame->layout()->addWidget(new QLabel("Name:"));
        contentFrame->layout()->addWidget(led);
        contentFrame->layout()->addWidget(new QLabel("Living place:"));
        contentFrame->layout()->addWidget(led2);
    }

    // add a content pane with a header
    int third = myAccordion->addContentPane("Advanced");
    // make sure our content pane was added
    if (third != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        myAccordion->getContentPane(third)->setMaximumHeight(500);
        QFrame *contentFrame = myAccordion->getContentPane(third)->getContentFrame();
        contentFrame->setMaximumHeight(500);
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QCheckBox *cb = new QCheckBox();
        cb->setText("Option 1");
        QCheckBox *cb2 = new QCheckBox();
        cb2->setText("Option 2");
        QCheckBox *cb3 = new QCheckBox();
        cb3->setText("Option 3");
        QCheckBox *cb4 = new QCheckBox();
        cb4->setText("Option 4");
        QCheckBox *cb5 = new QCheckBox();
        cb5->setText("Option 5");
        QCheckBox *cb6 = new QCheckBox();
        cb6->setText("Option 6");
        QCheckBox *cb7 = new QCheckBox();
        cb7->setText("Option 7");
        contentFrame->layout()->addWidget(cb);
        contentFrame->layout()->addWidget(cb2);
        contentFrame->layout()->addWidget(cb3);
        contentFrame->layout()->addWidget(cb4);
        contentFrame->layout()->addWidget(cb5);
        contentFrame->layout()->addWidget(cb6);
        contentFrame->layout()->addWidget(cb7);

    }
}

void TestView::test_ba3d()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
#ifdef BORNAGAIN_OPENGL
    RealSpaceWidget* widget = new RealSpaceWidget;
    widget->setModel(m_mainWindow->sampleModel());
    layout->addWidget(widget);
#endif
    setLayout(layout);

}
