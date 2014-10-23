#include "datasetscontroller.h"

using Romeo::Controller::DatasetsController;
using Romeo::Model::Util::DAO::DatasetDAO;
using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::View::Dialog::Dialog;
using Romeo::Model::QtModel::DatasetsTableModel;
using Romeo::Controller::MainWindowController;

DatasetsController::DatasetsController(DatasetsView *view, QObject *parent): AController(view, parent)
{
    createConnections();
}

void DatasetsController::createConnections() const
{
    DatasetsView *datasetView = qobject_cast<DatasetsView*>(view);

    connect(datasetView, SIGNAL(itemSelected(QModelIndex)), this, SLOT(slotItemSelected(QModelIndex)));
    connect(datasetView, SIGNAL(deleteObject()), this, SLOT(slotDeleteDataset()));
}

void DatasetsController::slotItemSelected(const QModelIndex &index)
{
    DatasetsView *datasetView = qobject_cast<DatasetsView*>(view);

    item = datasetView->getDatasetTable()->model()->index(index.row(), 0 ,index).data().toString();

    DatasetDAO dao1;
    GroupOfSubject *group = dao1.getGroupOfDataset(item);

    QString txtGroup = "Group: ";
    txtGroup.append(group->getName()+"\n\n");
    txtGroup.append("Subjects:\n");

    QVector<ASubject*> subjects = group->getAllSubjects();

    for(int i=0; i<subjects.size(); ++i){
        txtGroup.append(subjects.at(i)->getName()+"\n");
    }

    datasetView->setGroupInfo(txtGroup);

    DatasetDAO dao2;
    QVector<Protocol*> protocols = dao2.getProtocolsOfDataset(item);

    QString txtProtocols = "";

    for(int i=0; i<protocols.size(); ++i) {
        if(i>0) txtProtocols.append("\n");

        txtProtocols.append("Protocol "+QString::number(i+1)+": "+protocols.at(i)->getName()+" ("+protocols.at(i)->getType()+")");

        QVector<AFeature*> feats = protocols.at(i)->getFeatures();
        AAlgorithm* alg = protocols.at(i)->getAlgorithm();

        txtProtocols.append("\n\t-Algorithm:");
        algorithmInfo(alg, txtProtocols);

        txtProtocols.append("\n\n\t-Features:");
        featuresInfo(feats, txtProtocols);

        txtProtocols.append(QString("\n"));
        txtProtocols.append("--------------------------------------------------------------------------------");
        txtProtocols.append(QString("\n"));
    }

    datasetView->setProtocolsInfo(txtProtocols);
}

void DatasetsController::featuresInfo(QVector<AFeature*> feats, QString &txtProtocols) const
{
    if(feats.size() > 0){
        for(int j=0; j<feats.size(); ++j) {
            QStringList params = feats.at(j)->getParameters();
            txtProtocols.append("\n\t\t"+feats.at(j)->getName());

            if(feats.at(j)->getType()==Utils::FEATURE_FIRST_ORDER) {
                txtProtocols+=" ("+Utils::FEATURE_WINDOW_SIZE+": "+params.at(0)+")";
            }
            else if(feats.at(j)->getType()==Utils::FEATURE_SECOND_ORDER) {
                txtProtocols+=" ("+Utils::FEATURE_WINDOW_SIZE+": "+params.at(0)+", ";
                txtProtocols+=Utils::FEATURE_GLCM+": "+params.at(1)+")";
            }
            else if(feats.at(j)->getType()==Utils::FEATURE_DYNAMIC) {
                txtProtocols+=" ("+Utils::FEATURE_INITIAL_FRAME+": "+params.at(0)+", ";
                txtProtocols+=Utils::FEATURE_FINAL_FRAME+": "+params.at(1)+")";
            }
        }
    }
    else txtProtocols.append("\n\tNo Features");
}

void DatasetsController::algorithmInfo(AAlgorithm* alg, QString &txtProtocols) const
{
    if(alg!=0) {
        QStringList params = alg->getParameters();
        txtProtocols.append("\n\t\t"+alg->getName());

        QMap<QString, QList<int> > list = alg->getParametersTypeList();
        QMapIterator<QString, QList<int> > it(list);
        int itChoice = 0;

        txtProtocols.append("(");
        for(int i=0; i<params.size(); ++i){
            it.next();
            txtProtocols.append(it.key()+": ");
            if(it.value().at(0) == Utils::_INT) {
                txtProtocols.append(params.at(i));
            }
            else if(it.value().at(0) == Utils::_CHOICE){
                txtProtocols.append(alg->getValueComboBox(itChoice, params.at(i)));
                txtProtocols.append(" ["+params.at(i)+"]");
                itChoice++;
            }

            if(i < (list.size()-1))
                txtProtocols.append(",\n\t\t\t");
        }
        txtProtocols.append(")");
    }
    else txtProtocols.append("\n\tNo algorithm");
}

void DatasetsController::slotDeleteDataset()
{
    DatasetsView *datasetView = qobject_cast<DatasetsView*>(view);

    datasetView->removeResultMessageWidget();

    if(item.isEmpty()) datasetView->addResultMessageWidget("You must select a Dataset", false);
    else {
        int response = Dialog::dialogQuestion("Delete Dataset?", "Are you sure you want to delete the Dataset \""+item+"\"?", "If you delete the Dataset will be deleted all the Analysis Results associated");
        if(response == QMessageBox::Yes) {
            QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(datasetView->getDatasetTable()->model());
            DatasetsTableModel *model = qobject_cast<DatasetsTableModel*>(proxyModel->sourceModel());

            DatasetDAO db;
            if(db.deleteDataset(item)){
                MainWindow::getMainWindow()->writeStatusBar("Dataset "+item+" deleted", 10000);
                datasetView->addResultMessageWidget("Dataset "+item+" deleted", true);
            }
            else Dialog::dialogCritical("Delete Error", "Dataset does not exist in the database");
            item.clear();

            datasetView->resetDatasetInfo();
            model->refreshModelData();
        }
    }
}
