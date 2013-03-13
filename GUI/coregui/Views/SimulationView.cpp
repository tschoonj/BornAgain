#include "SimulationView.h"

#include "SimulationDataModel.h"
#include "Simulation.h"
#include "JobModel.h"
#include "mainwindow.h"
#include "PythonScriptSampleBuilder.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
#include <QFuture>
#include <QFutureWatcher>
#include <QtCore>

#if QT_VERSION >= 0x050000
#include <QtConcurrent/QtConcurrentRun>
#endif


SimulationView::SimulationView(SimulationDataModel *p_simulation_data_model, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
{
    // selection of input parameters
    QGroupBox *inputDataGroup = new QGroupBox(tr("Data selection"));
      // instrument selection
    QLabel *instrumentSelectionLabel = new QLabel(tr("Select Instrument:"));
    instrumentSelectionBox = new QComboBox;
      // sample selection
    QLabel *sampleSelectionLabel = new QLabel(tr("Select Sample:"));
    sampleSelectionBox = new QComboBox;
      // layout
    QGridLayout *dataSelectionLayout = new QGridLayout;
    dataSelectionLayout->addWidget(instrumentSelectionLabel, 0, 0);
    dataSelectionLayout->addWidget(instrumentSelectionBox, 0, 1);
    dataSelectionLayout->addWidget(sampleSelectionLabel, 1, 0);
    dataSelectionLayout->addWidget(sampleSelectionBox, 1, 1);
    inputDataGroup->setLayout(dataSelectionLayout);
    updateViewElements();

    // selection of simulation parameters
    QGroupBox *simulationParametersGroup = new QGroupBox(tr("Simulation Parameters"));
       // framework (DWBA - BA)
    QLabel *frameworkLabel = new QLabel(tr("Framework:"));
    QComboBox *frameworkSelectionBox = new QComboBox;
    frameworkSelectionBox->addItem(tr("DWBA"));
    frameworkSelectionBox->addItem(tr("BA"));
      // interference function (DA - LMA - SSCA - ISGISAXSMOR)
    QLabel *interferenceLabel = new QLabel(tr("Interference Function Approximation:"));
    QComboBox *interferenceFunctionSelectionBox = new QComboBox;
    interferenceFunctionSelectionBox->addItem(tr("DA"));
    interferenceFunctionSelectionBox->addItem(tr("LMA"));
    interferenceFunctionSelectionBox->addItem(tr("SSCA"));
      // lattice type (None - Lattice - Para1D - Para1DFinite)
    QLabel *latticeTypeLabel = new QLabel(tr("Lattice Type:"));
    QComboBox *latticeTypeSelectionBox = new QComboBox;
    latticeTypeSelectionBox->addItem(tr("None"));
    latticeTypeSelectionBox->addItem(tr("Lattice"));
    latticeTypeSelectionBox->addItem(tr("Para1D"));
    latticeTypeSelectionBox->addItem(tr("Para1DFinite"));
      // layout
    QGridLayout *simulationParametersLayout = new QGridLayout;
    simulationParametersLayout->addWidget(frameworkLabel, 0, 0);
    simulationParametersLayout->addWidget(frameworkSelectionBox, 0, 1);
    simulationParametersLayout->addWidget(interferenceLabel, 1, 0);
    simulationParametersLayout->addWidget(interferenceFunctionSelectionBox, 1, 1);
    simulationParametersLayout->addWidget(latticeTypeLabel, 2, 0);
    simulationParametersLayout->addWidget(latticeTypeSelectionBox, 2, 1);
    simulationParametersGroup->setLayout(simulationParametersLayout);

    // run simulation button
    runSimulationButton = new QPushButton(tr("Run Simulation"));

    // run simulation with python script sample builder
    runPyScriptSimulation = new QPushButton(tr("And now for something completely different..."));

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputDataGroup);
    mainLayout->addWidget(simulationParametersGroup);
    mainLayout->addWidget(runSimulationButton);
    mainLayout->addWidget(runPyScriptSimulation);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // signal and slots
    connect(runSimulationButton, SIGNAL(clicked()), this, SLOT(onRunSimulation()));
    connect(runPyScriptSimulation, SIGNAL(clicked()), this, SLOT(onPythonJobLaunched()));
}

void SimulationView::updateViewElements()
{
    instrumentSelectionBox->clear();
    instrumentSelectionBox->addItems(mp_simulation_data_model->getInstrumentList().keys());
    sampleSelectionBox->clear();
    sampleSelectionBox->addItems(mp_simulation_data_model->getSampleList().keys());
}

void SimulationView::onRunSimulation()
{
    Instrument *p_instrument = mp_simulation_data_model->getInstrumentList().value(
                instrumentSelectionBox->currentText(), 0);
    if (!p_instrument) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }
    ISample *p_sample = mp_simulation_data_model->getSampleList().value(
                sampleSelectionBox->currentText(), 0);
    if (!p_sample) {
        QMessageBox::warning(this, tr("No Sample Selected"),
                             tr("You must select a sample first."));
        return;
    }
    Simulation *p_sim = new Simulation;
    p_sim->setSample(*p_sample);
    p_sim->setInstrument(*p_instrument);
    JobModel *p_new_job = new JobModel(p_sim);
    mp_simulation_data_model->addJob(p_new_job->getName(), p_new_job);
    QFuture<void> job_future = QtConcurrent::run(p_new_job, &JobModel::run);
    p_new_job->getJobWatcher()->setFuture(job_future);
    // initialize a Simulation object and run it
//    QMessageBox::information(this, tr("Simulation Started"),
//                             tr("The simulation is now calculating."));
}

void SimulationView::onPythonJobLaunched()
{
    Instrument *p_instrument = mp_simulation_data_model->getInstrumentList().value(
                instrumentSelectionBox->currentText(), 0);
    if (!p_instrument) {
        QMessageBox::warning(this, tr("No Instrument Selected"),
                             tr("You must select an instrument first."));
        return;
    }
//    QString file_name = QFileDialog::getOpenFileName(this, tr("Select Python Script"),
//                                                     QDir::homePath(), tr("Python scripts (*.py)"));
    QString file_name("/Users/herck/Development/git/BornAgain/GUI/test_sample_builder");
    PythonScriptSampleBuilder builder(file_name);
    ISample *p_sample = builder.buildSample();
    Simulation *p_sim = new Simulation;
    p_sim->setSample(*p_sample);
    p_sim->setInstrument(*p_instrument);
    JobModel *p_new_job = new JobModel(p_sim);
    mp_simulation_data_model->addJob(p_new_job->getName(), p_new_job);
    QFuture<void> job_future = QtConcurrent::run(p_new_job, &JobModel::run);
    p_new_job->getJobWatcher()->setFuture(job_future);
    // initialize a Simulation object and run it
    QMessageBox::information(this, tr("Simulation Started"),
                             tr("The simulation is now calculating."));
}

void SimulationView::onJobFinished()
{
    QMessageBox::information(this, tr("Simulation Job Finished"),
                             tr("A simulation job has finished."));
}

