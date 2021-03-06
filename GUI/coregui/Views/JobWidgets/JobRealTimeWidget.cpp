// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobRealTimeWidget.cpp
//! @brief     Implements class JobRealTimeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobRealTimeWidget.h"
#include "JobItem.h"
#include "JobModel.h"
#include "JobRealTimeToolBar.h"
#include "ParameterTuningWidget.h"
#include "mainwindow_constants.h"
#include <QVBoxLayout>

JobRealTimeWidget::JobRealTimeWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_toolBar(new JobRealTimeToolBar)
    , m_stackedWidget(new ItemStackPresenter<ParameterTuningWidget>)
{
    setWindowTitle(Constants::JobRealTimeWidgetName);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stackedWidget);

    setLayout(mainLayout);

    m_stackedWidget->setModel(jobModel);
    connect(m_toolBar, SIGNAL(resetParameters()), this, SLOT(onResetParameters()));
}

ParameterTuningWidget *JobRealTimeWidget::parameterTuningWidget(JobItem *jobItem)
{
    return m_stackedWidget->itemWidget(jobItem);
}

QSize JobRealTimeWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, 480);
}

QSize JobRealTimeWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

void JobRealTimeWidget::setItem(JobItem * jobItem)
{
    if(!isValidJobItem(jobItem)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    bool isNew(false);
    m_stackedWidget->setItem(jobItem, &isNew);

    if(isNew) {
        ParameterTuningWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(jobItem);
    }
}

void JobRealTimeWidget::onResetParameters()
{
    if(auto widget = currentParameterTuningWidget())
        widget->restoreModelsOfCurrentJobItem();
}

ParameterTuningWidget *JobRealTimeWidget::currentParameterTuningWidget()
{
    return m_stackedWidget->currentWidget();
}

//! Returns true if JobItem is valid for real time simulation.

bool JobRealTimeWidget::isValidJobItem(JobItem *item)
{
    if(!item) return false;
    if(item->isCompleted() || item->isCanceled() || item->isFailed()) return true;
    return false;
}
