// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitManager.h
//! @brief     Implements class RunFitManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef RUNFITMANAGER_H
#define RUNFITMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <atomic>
#include <memory>

class FitSuite;

class BA_CORE_API_ RunFitManager : public QObject
{
    Q_OBJECT

public:
    RunFitManager(QObject *parent);

    void setFitSuite(std::shared_ptr<FitSuite> suite);

    void runFitting();

    int getDuration();

public slots:
    void interruptFitting();

signals:
    void finishedFitting();
    void startedFitting();
    void fittingError(const QString &message);

// only used by manager for communication with FittingWorker
private slots:
    void intern_workerFinished(int duration);

    void intern_workerStarted();

    void intern_error(const QString &mesg);

signals:
    void intern_interruptFittingWorker();

private:
    std::shared_ptr<FitSuite> m_fitSuite;
    std::atomic<bool> m_is_fit_running;
    int m_duration;
};

#endif // RUNFITMANAGER_H
