// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.cpp
//! @brief     Implements class FitComparisonWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitComparisonWidget.h"
#include "AxesItems.h"
#include "ColorMapCanvas.h"
#include "ColorMapLabel.h"
#include "FitFlowWidget.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include <QAction>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

namespace {
const double relative_diff_min = 1e-05;
const double relative_diff_max = 1;
}

FitComparisonWidget::FitComparisonWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_realDataPlot(new ColorMapCanvas)
    , m_simulatedDataPlot(new ColorMapCanvas)
    , m_relativeDiffPlot(new ColorMapCanvas)
    , m_fitFlowWidget(new FitFlowWidget)
    , m_statusLabel(new ColorMapLabel(0, this))
//    , m_currentJobItem(0)
//    , m_realDataItem(0)
//    , m_simulatedDataItem(0)
    , m_relativeDiffItem(0)
    , m_resetViewAction(0)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel"))
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    setStyleSheet("background-color:white;");

    gridLayout->addWidget(m_realDataPlot, 0, 0);
    gridLayout->addWidget(m_simulatedDataPlot, 0, 1);
    gridLayout->addWidget(m_relativeDiffPlot, 1, 0);
    gridLayout->addWidget(m_fitFlowWidget, 1, 1);

    vlayout->addLayout(gridLayout);
    vlayout->addWidget(m_statusLabel);
    setLayout(vlayout);

    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset View");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(triggered()), this, SLOT(onResetViewAction()));

    m_relativeDiffItem = createRelativeDifferenceItem();
    m_relativeDiffPlot->setItem(m_relativeDiffItem);
}

FitComparisonWidget::~FitComparisonWidget()
{
    // FIXME unclear corrupter memory on aplication exist (comment lines below to reproduce)
    m_relativeDiffPlot->setItem(0);
    delete m_tempIntensityDataModel;
}

QList<QAction *> FitComparisonWidget::actionList()
{
    return QList<QAction *>() << m_resetViewAction;
}

void FitComparisonWidget::subscribeToItem()
{
    if(!jobItem()->isValidForFitting())
        return;

    jobItem()->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        if(name == JobItem::P_STATUS) {
            if(jobItem()->isCompleted())
                onResetViewAction();
        }
    }, this);

    if(auto simItem = simulatedDataItem()) {
        simItem->mapper()->setOnValueChange(
            [this]()
        {
            calculateRelativeDifference();
        }, this);
    }

    calculateRelativeDifference();

    m_realDataPlot->setItem(realDataItem());
    m_simulatedDataPlot->setItem(simulatedDataItem());
    m_fitFlowWidget->setItem(jobItem()->fitSuiteItem());

    m_statusLabel->reset();
    m_statusLabel->addColorMap(m_realDataPlot);
    m_statusLabel->addColorMap(m_simulatedDataPlot);
    m_statusLabel->addColorMap(m_relativeDiffPlot);
}

void FitComparisonWidget::unsubscribeFromItem()
{
    if(!currentItem())
        return;

    if(simulatedDataItem())
        simulatedDataItem()->mapper()->unsubscribe(this);
}

void FitComparisonWidget::onResetViewAction()
{
    if(auto item = realDataItem())
        item->resetView();

    if(auto item = simulatedDataItem())
        item->resetView();

    if(m_relativeDiffItem) {
        m_relativeDiffItem->resetView();
        m_relativeDiffItem->setLowerAndUpperZ(relative_diff_min, relative_diff_max);
    }
}

//! Creates an IntensityDataItem which will hold relative difference map between simulation
//! and real data.

IntensityDataItem *FitComparisonWidget::createRelativeDifferenceItem()
{
    m_tempIntensityDataModel->clear();

    IntensityDataItem *result = dynamic_cast<IntensityDataItem *>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));

    return result;
}

void FitComparisonWidget::calculateRelativeDifference()
{
    if(!simulatedDataItem()->getOutputData()) // job failed
        return;

    Q_ASSERT(realDataItem());
    Q_ASSERT(simulatedDataItem());
    Q_ASSERT(m_relativeDiffItem);

    m_relativeDiffItem->setOutputData(
        IntensityDataFunctions::createRelativeDifferenceData(*simulatedDataItem()->getOutputData(),
                *realDataItem()->getOutputData()));

    m_relativeDiffItem->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, QString());
    m_relativeDiffItem->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, QString());
    m_relativeDiffItem->setLowerAndUpperZ(relative_diff_min, relative_diff_max);

}

//! Restores item labels from the backup (FIXME currently unused. Do we need to hide labels?).

void FitComparisonWidget::restoreLabels(IntensityDataItem *intensityItem)
{
    if(!intensityItem)
        return;

    intensityItem->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE, true);
    intensityItem->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE, true);
}

//! Removes axes label from item. This is because they occupy too much space on this dense widget.

void FitComparisonWidget::removeLabels(IntensityDataItem *intensityItem)
{
    if(!intensityItem)
        return;

    intensityItem->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE, false);
    intensityItem->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE_IS_VISIBLE, false);
}

JobItem* FitComparisonWidget::jobItem()
{
    JobItem *jobItem = dynamic_cast<JobItem *>(currentItem());
    Q_ASSERT(jobItem);
    return jobItem;
}

IntensityDataItem* FitComparisonWidget::realDataItem()
{
    return jobItem()->realDataItem()->intensityDataItem();
}

IntensityDataItem* FitComparisonWidget::simulatedDataItem()
{
    return jobItem()->intensityDataItem();
}
