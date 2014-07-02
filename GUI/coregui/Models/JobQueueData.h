#ifndef JOBQUEUEDATA_H
#define JOBQUEUEDATA_H

#include "JobItem.h"
#include <QObject>
#include <QString>
#include <QMap>

class JobItem;
class JobQueueItem;
class Simulation;
class JobRunner;
class QThread;


//! Holds correspondance of job identifiers and JobItem, QThread, JobRunner
//! and Simulation objects. Contains all run/cancel/progress logic for job.
class JobQueueData : public QObject
{
    Q_OBJECT
public:

    JobQueueItem *createJobQueueItem(QString jobName = QString(), Simulation *simulation = 0, JobItem::RunPolicy run_policy = JobItem::SubmitOnly);

    const JobItem *getJobItem(QString identifier) const;
    JobItem *getJobItem(QString identifier);

    QThread *getThread(QString identifier);
    JobRunner *getRunner(QString identifier);
    Simulation *getSimulation(QString identifier);

    QString getIdentifierForJobItem(const JobItem *);

signals:
    void globalProgress(int);
    void focusRequest(JobItem *item);

public slots:
    void onStartedJob();
    void onProgressUpdate();
    void onFinishedJob();
    void onFinishedThread();
    void onCancelAllJobs();

    void runJob(QString identifier);
    void cancelJob(QString identifier);
    void removeJob(QString identifier);

private:
    void assignForDeletion(QThread *thread);
    void assignForDeletion(JobRunner *runner);
    void updateGlobalProgress();

    QString generateJobName();
    QString generateJobIdentifier();

    QMap<QString, JobItem *> m_job_items; //!< correspondance of JobIdentifier and JobItem's
    QMap<QString, QThread *> m_threads; //! correspondance of JobIdentifier and running threads
    QMap<QString, JobRunner *> m_runners; //! correspondance of JobIdentifier and JobRunner's
    QMap<QString, Simulation *> m_simulations; //! correspondance of JobIdentifier and simulation

    static int m_job_index;
};


#endif