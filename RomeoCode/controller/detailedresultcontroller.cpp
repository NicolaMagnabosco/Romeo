#include "detailedresultcontroller.h"

using Romeo::Controller::DetailedResultController;
using Romeo::Controller::MainWindowController;
using Romeo::Model::Util::DAO::AnalysisDAO;
using Romeo::View::Dialog::Dialog;

DetailedResultController::DetailedResultController(int id, const QString& title, DetailedResult *view, QObject *parent) : AController(view, parent), idResult(id)
{
    createConnections();   

    setPathTree();
    setPageTitle(title);
}

void DetailedResultController::createConnections() const {
    DetailedResult *viewR = qobject_cast<DetailedResult*>(view);

    connect(viewR, SIGNAL(treeClicked(QModelIndex)), this, SLOT(slotTreeClicked(QModelIndex)));
    connect(viewR, SIGNAL(ImageDoubleClicked(QString)), this, SLOT(SlotImageDoubleClicked(QString)));
    connect(viewR, SIGNAL(exportSignal()), this, SLOT(slotExport()));
}

void DetailedResultController::slotBack() {
    MainWindowController::getMainWindowController()->slotAnalysisResults(3);
}

void DetailedResultController::setPathTree()
{
    DetailedResult *viewR = qobject_cast<DetailedResult*>(view);

    AnalysisDAO dao;
    viewR->setTreePath(Utils::SAVING_ANALYSIS_PATH+"/D_"+QString::number(idResult)+"_"+dao.getDatasetname(idResult));
}

void DetailedResultController::slotTreeClicked(const QModelIndex& item)
{
    DetailedResult *viewR = qobject_cast<DetailedResult*>(view);

    QString name = item.data().toString();
    if(name.startsWith("P_")) {
        viewR->generateImages(viewR->getModelTree()->filePath(item));
    }
}

void DetailedResultController::setPageTitle(const QString& txt) const
{
    DetailedResult *viewR = qobject_cast<DetailedResult*>(view);

    viewR->setpageTitle(txt);
}

void DetailedResultController::SlotImageDoubleClicked(const QString& path)
{
    QDir dir;
    if(dir.exists(path))
        QDesktopServices::openUrl(QUrl("file:///" + path));
    else Dialog::dialogCritical("IMAGE ERROR!", "Image not found!");
}

void DetailedResultController::slotExport()
{
    QString resultsFolder = QFileDialog::getExistingDirectory(view, tr("Select a directory"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!resultsFolder.isNull()) {
        AnalysisDAO dao;
        QString path = Utils::SAVING_ANALYSIS_PATH+"/D_"+QString::number(idResult)+"_"+dao.getDatasetname(idResult);

        if(copyDir(path, resultsFolder, true))
            Dialog::dialogInfo("EXPORT", "Export Done!");
        else
            Dialog::dialogCritical("EXPORT ERROR!", "Error in the export of analysis results!");
    }
}
