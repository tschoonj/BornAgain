// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobOutputDataWidget.h
//! @brief     Defines class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include "ItemStackPresenter.h"
#include <QMap>

class ObsoleteIntensityDataWidget;
class JobResultsPresenter;
class JobModel;
class JobItem;

//! The JobOutputDataWidget class is a central widget of JobView, shows results of the simulation.

class BA_CORE_API_ JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    JobOutputDataWidget(JobModel *jobModel, QWidget *parent = 0);

public slots:
    void setItem(JobItem *jobItem);
    void onActivityChanged(int);

protected:
    virtual bool isValidJobItem(JobItem *item);

private:
    ItemStackPresenter<JobResultsPresenter> *m_stackedWidget;
};

#endif // JOBOUTPUTDATAWIDGET_H
