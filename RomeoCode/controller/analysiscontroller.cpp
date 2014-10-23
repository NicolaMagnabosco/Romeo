#include "analysiscontroller.h"
#include <QDir>
#include <QString>
#include "view/dialog/analysisdialog.h"
#include "model/core/analysis.h"
#include <QFileDialog>
#include <QDateTime>

using Romeo::Controller::AnalysisController;
using Romeo::Model::QtModel::AnalysisSubjectsTableModel;
using Romeo::Model::QtModel::AnalysisProtocolsTableModel;
using Romeo::Model::Util::DAO::ProtocolDAO;
using Romeo::Model::Util::DAO::DatasetDAO;
using Romeo::View::Dialog::AnalysisDialog;
using Romeo::Model::Core::Analysis;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Util::DAO::AnalysisDAO;
using Romeo::Controller::MainWindowController;

AnalysisController::AnalysisController(AnalysisView *view, QObject *parent): AController(view, parent), dialog(0), analysis(0), lastCreateID(-1), restart(false)
{
    createConnections();
}

AnalysisController::AnalysisController(AnalysisView *view, int id, QObject *parent): AController(view, parent), dialog(0), analysis(0), lastCreateID(-1), restart(true)
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);

    createConnections();

    AnalysisDAO dao;
    analysisView->setRestartData(dao.getAnalysis(id));
}

void AnalysisController::createConnections() const
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);

    connect(analysisView, SIGNAL(datasetSelected(QString)), this, SLOT(slotDatasetSelected(QString)));
    connect(analysisView, SIGNAL(startAnalysis()), this, SLOT(slotStartAnalysis()));
    connect(analysisView, SIGNAL(selectDestinationDirectory()), this, SLOT(slotSelectResultsFolder()));
    connect(analysisView, SIGNAL(selectAll()), this, SLOT(slotSelAllSubjects()));
    connect(analysisView, SIGNAL(deselectAll()), this, SLOT(slotDeselAllSubjects()));
    connect(analysisView, SIGNAL(featureSelected(QModelIndex)), this, SLOT(slotFeatureSelected(QModelIndex)));
    connect(analysisView, SIGNAL(saveAllSignal()), this, SLOT(slotSaveAll()));
    connect(analysisView, SIGNAL(showAllSignal()), this, SLOT(slotShowAll()));
}

void AnalysisController::slotDatasetSelected(const QString& datasetS)
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    analysisView->removeResultMessageWidget();
    QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(analysisView->getSubjectsTable()->model());
    AnalysisSubjectsTableModel *model = qobject_cast<AnalysisSubjectsTableModel*>(proxyModel->sourceModel());

    //QSortFilterProxyModel *proxyModelP = qobject_cast<QSortFilterProxyModel*>(analysisView->getProtocolsTable()->model());
    AnalysisProtocolsTableModel *protocolModel = qobject_cast<AnalysisProtocolsTableModel*>(analysisView->getProtocolsTable()->model());

    if(datasetS != Utils::ROMEO_SELECT_DATASET) {
        clearData();

        dataset = datasetS;

        model->loadModelData(dataset);

        DatasetDAO pDao;
        protocolOfDataset = pDao.getProtocolsOfDataset(dataset);
        protocolModel->loadModelData(protocolOfDataset);
    }
    else {
        clearData();
        model->resetModelData();
        protocolModel->resetModelData();
    }
}

void AnalysisController::clearData()
{
    dataset.clear();
    protocolOfDataset.clear();
}


void AnalysisController::slotStartAnalysis()
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    analysisView->removeResultMessageWidget();
    if(dataset.isEmpty()) {
        analysisView->addResultMessageWidget("You must select a Dataset", false);
        return;
    }
    QModelIndexList subjectsSel = analysisView->getSubjectsSelected();
    if(subjectsSel.size()<1) {
        analysisView->addResultMessageWidget("You must select at least a Subject", false);
        return;
    }

    AnalysisProtocolsTableModel *protocolModel = qobject_cast<AnalysisProtocolsTableModel*>(analysisView->getProtocolsTable()->model());
    QVector<QString> saveVec = protocolModel->getFeaturesToSave();

    DatasetDAO dao;
    //dataset selected
    Dataset * datasetObj = dao.getDatasetByName(dataset);
    int nAlg = datasetObj->getNumberOfAlgAssociated();
    int toSave = saveVec.indexOf(Utils::ROMEO_YES);

    QString folder = analysisView->getDestinationFolder();
    if(folder.isEmpty() && (nAlg>0 || toSave>-1)) {
        analysisView->addResultMessageWidget("You must select the Destination folder", false);
        return;
    }

    //export directory
    QDir exportFolder(folder);
    //subjects list
    QVector<QString> subjectsVector;
    for(int i=0; i<subjectsSel.size(); ++i)
        subjectsVector.append(analysisView->getSubjectsTable()->model()->index(subjectsSel.at(i).row(), 0 ,subjectsSel.at(i)).data().toString());

    QVector<AFeature*> features = protocolModel->getFeatures();
    QVector<QString> showVec = protocolModel->getFeaturesToShow();
    int size = showVec.size();
    //vector of features to show
    QMap<int, bool> featShow;
    //vector of features to save
    QMap<int, bool> featSave;
    for(int i=0; i<size; ++i) {
        if(showVec.at(i) == Utils::ROMEO_YES) featShow.insert(features.at(i)->getId(), true);
        else featShow.insert(features.at(i)->getId(), false);
        if(saveVec.at(i) == Utils::ROMEO_YES) featSave.insert(features.at(i)->getId(), true);
        else featSave.insert(features.at(i)->getId(), false);
    }
    int step = subjectsVector.size() * (datasetObj->getNumberOfFeaturesAssociated() + datasetObj->getNumberOfAlgAssociated());
    dialog = new AnalysisDialog(step, subjectsVector.size(), analysisView);
    analysis= new Analysis(datasetObj, subjectsVector, featShow, featSave, exportFolder,-1, QDateTime());
    AnalysisDAO daoA;
    lastCreateID = -1;
    QVector<QString> result = daoA.createAnalysis(*analysis);
    lastCreateID = result.at(0).toInt();
    analysis->setCreationDate(result.at(1));
    if(lastCreateID == -1) {
        analysisView->addResultMessageWidget("Analysis creation error", false);
        return;
    }
    analysis->setID(lastCreateID);
    dialog->show();
    createDialogConnections();
    analysis->start();
}

void AnalysisController::createDialogConnections()
{
    connect(analysis, SIGNAL(resultUpdate(QString)), this, SLOT(slotUpdateDialog(QString)));
    connect(analysis, SIGNAL(resultReady()), this, SLOT(slotFinishAnalysis()));
    connect(dialog, SIGNAL(cancelAnalysis()), dialog, SLOT(close()));
    connect(dialog, SIGNAL(realClose()), this, SLOT(slotRealClose()));
    connect(dialog, SIGNAL(closeOnFinish()), this, SLOT(slotResetView()));
    connect(analysis, SIGNAL(beginSubject()), this, SLOT(slotIncrementSubject()));
    connect(analysis, SIGNAL(imageReady(QImage*, const QString &)), this, SLOT(slotShowNewImage(QImage*, const QString &)));
    connect(dialog, SIGNAL(nextImage()), this, SLOT(slotShowNextImage()));
    connect(dialog, SIGNAL(previousImage()), this, SLOT(slotShowPreviousImage()));
}

void AnalysisController::slotRealClose()
{
    dialog = 0;
    analysis = 0;
}

void AnalysisController::slotUpdateDialog(const QString &description)
{
    if(dialog)
        dialog->setBarValue(description);
}

void AnalysisController::slotSelectResultsFolder()
{
    QDir dir = QDir::home();
    //obtain the output directory from the user
    QString resultsFolder = QFileDialog::getExistingDirectory(view, tr("Select a directory"),dir.absolutePath() , QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!resultsFolder.isNull()) {
        //cast the view
        AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
        //update the resultsFolder
        analysisView->setDestinationFolder(resultsFolder);
    }

}

void AnalysisController::slotSelAllSubjects()
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    analysisView->getSubjectsTable()->selectAll();
    analysisView->getSubjectsTable()->setFocus();
}

void AnalysisController::slotDeselAllSubjects()
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    analysisView->getSubjectsTable()->clearSelection();
    analysisView->getSubjectsTable()->setFocus();
}

void AnalysisController::slotFeatureSelected(const QModelIndex & index)
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);

    AnalysisProtocolsTableModel *protocolModel = qobject_cast<AnalysisProtocolsTableModel*>(analysisView->getProtocolsTable()->model());

    if(index.column() == 2)
        protocolModel->setShowProtocol(index);
    if(index.column() == 3)
        protocolModel->setSaveProtocol(index);
}

void AnalysisController::slotSaveAll()
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    AnalysisProtocolsTableModel *protocolModel = qobject_cast<AnalysisProtocolsTableModel*>(analysisView->getProtocolsTable()->model());
    protocolModel->saveAll();
}

void AnalysisController::slotShowAll()
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    AnalysisProtocolsTableModel *protocolModel = qobject_cast<AnalysisProtocolsTableModel*>(analysisView->getProtocolsTable()->model());
    protocolModel->showAll();
}

void AnalysisController::slotFinishAnalysis()
{
    AnalysisDAO daoA;
    if(dialog && lastCreateID != -1 && daoA.setComplete(lastCreateID)){
        dialog->analysisFinish();
    }
}

void AnalysisController::slotResetView()
{
    AnalysisView *analysisView = qobject_cast<AnalysisView*>(view);
    restart = false;
    analysisView->resetView();
}

void AnalysisController::slotShowNewImage(QImage *image, const QString &description)
{
    if(image && dialog)
        dialog->addImage(image, description);
}

void AnalysisController::slotShowNextImage()
{
    if(dialog)
        dialog->showNextImage();
}

void AnalysisController::slotShowPreviousImage()
{
    if(dialog)
        dialog->showPreviousImage();
}

void AnalysisController::slotBack()
{
    if(restart) MainWindowController::getMainWindowController()->slotAnalysisResults(2);
    else AController::slotBack();
}

void AnalysisController::slotIncrementSubject()
{
    dialog->incrementCurrentSubject();
}
