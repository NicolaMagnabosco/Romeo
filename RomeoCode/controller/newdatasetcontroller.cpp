#include "newdatasetcontroller.h"

using Romeo::Controller::NewDatasetController;
using Romeo::Model::QtModel::DatasetProtocolTableModel;
using Romeo::Model::QtModel::DatasetGroupTableModel;
using Romeo::Model::Util::DAO::GroupDAO;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Util::DAO::FeatureDAO;
using Romeo::Model::Util::DAO::AlgorithmDAO;
using Romeo::View::Dialog::Dialog;
using Romeo::Model::Util::DAO::DatasetDAO;
using Romeo::Controller::MainWindowController;

NewDatasetController::NewDatasetController(NewDatasetView *view, QObject *parent) : AController(view,parent), edit(false), idEdit("")
{
    createConnections();
}

NewDatasetController::NewDatasetController(NewDatasetView *view, const QString& dataset, QObject *parent) : AController(view,parent), edit(true), idEdit(dataset)
{
    createConnections();
}

void NewDatasetController::createConnections() const
{
    NewDatasetView *newDatasetView = qobject_cast<NewDatasetView*>(view);

    connect(newDatasetView, SIGNAL(groupSelected(QModelIndex)), this, SLOT(slotGroupSelected(QModelIndex)));
    connect(newDatasetView, SIGNAL(protocolSelected(QModelIndex)), this, SLOT(slotProtocolSelected(QModelIndex)));
    connect(newDatasetView, SIGNAL(saveObject()), this, SLOT(slotSaveDataset()));
}

void NewDatasetController::slotGroupSelected(const QModelIndex &index)
{
    NewDatasetView *newDatasetView = qobject_cast<NewDatasetView*>(view);

    if(group.isEmpty() || group!=newDatasetView->getGroupsTable()->model()->index(index.row(), 0 ,index).data().toString()) {
        newDatasetView->resetInfo();

        group = newDatasetView->getGroupsTable()->model()->index(index.row(), 0 ,index).data().toString();
        QString type = newDatasetView->getGroupsTable()->model()->index(index.row(), 1 ,index).data().toString();

        GroupDAO *db = new GroupDAO();
        GroupOfSubject* groupItem = db->getGroupByName(group);
        QVector<ASubject*> subjects = groupItem->getAllSubjects();
        QString txt = "Subjects in the Group "+group+" ("+QString::number(subjects.size())+"):\n";
        for(int i=0; i<subjects.size(); ++i) {
            txt.append(subjects.at(i)->getName()+"\n");
        }
        newDatasetView->setGroupInfo(txt);

        QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(newDatasetView->getProtocolsTable()->model());
        DatasetProtocolTableModel *model = qobject_cast<DatasetProtocolTableModel*>(proxyModel->sourceModel());
        model->loadModelData(type);
    }
}

void NewDatasetController::slotProtocolSelected(const QModelIndex &index)
{
    NewDatasetView *newDatasetView = qobject_cast<NewDatasetView*>(view);
    protocol = newDatasetView->getProtocolsTable()->model()->index(index.row(), 0 ,index).data().toString();
    FeatureDAO *fDao = new FeatureDAO();
    QVector<AFeature*> features = fDao->getAllFeatureOfProtocol(protocol);
    AlgorithmDAO *aDao = new AlgorithmDAO();
    AAlgorithm* algorithm = aDao->getAlgorithmOfProtocol(protocol);

    QString txt = "Features in the Protocol "+protocol+" ("+QString::number(features.size())+"):\n";
    if(features.size()==0) txt += "There are no Features\n";
    else
        featuresInfo(features, txt);

    txt += "\nAlgorithm in the Protocol "+protocol+":\n";
    if(!algorithm) txt += "There are no Algorithms";
    else
        algorithmInfo(algorithm, txt);

    newDatasetView->setProtocolInfo(txt);
}

void NewDatasetController::featuresInfo(QVector<AFeature*> features, QString &txt) const
{
    for(int i=0; i<features.size(); ++i) {
        QStringList params = features.at(i)->getParameters();
        txt.append(features.at(i)->getName());

        if(features.at(i)->getType()==Utils::FEATURE_FIRST_ORDER)
            txt+=" ("+Utils::FEATURE_WINDOW_SIZE+": "+params.at(0)+")";
        else if(features.at(i)->getType()==Utils::FEATURE_SECOND_ORDER) {
            txt+=" ("+Utils::FEATURE_WINDOW_SIZE+": "+params.at(0)+", ";
            txt+=Utils::FEATURE_GLCM+": "+params.at(1)+")";
        }
        else if(features.at(i)->getType()==Utils::FEATURE_DYNAMIC) {
            txt+=" ("+Utils::FEATURE_INITIAL_FRAME+": "+params.at(0)+", ";
            txt+=Utils::FEATURE_FINAL_FRAME+": "+params.at(1)+")";
        }
        txt.append(QString("\n"));
    }
}

void NewDatasetController::algorithmInfo(AAlgorithm* algorithm, QString &txt) const
{
    txt.append(algorithm->getName()+"\n");
    QStringList params = algorithm->getParameters();
    QMap<QString, QList<int> > list = algorithm->getParametersTypeList();
    QMapIterator<QString, QList<int> > it(list);
    int itChoice = 0;

    txt.append("(");
    for(int i=0; i<params.size(); ++i){
        it.next();
        txt.append(it.key()+": ");
        if(it.value().at(0) == Utils::_INT) {
            txt.append(params.at(i));
        }
        else if(it.value().at(0) == Utils::_CHOICE){
            txt.append(algorithm->getValueComboBox(itChoice, params.at(i)));
            txt.append(" ["+params.at(i)+"]");
            itChoice++;
        }
        if(i < (list.size()-1))
            txt.append(",\n\t");
    }
    txt.append(")");
}

void NewDatasetController::slotSaveDataset()
{
    int maxChar = 200;
    NewDatasetView *newDatasetView = qobject_cast<NewDatasetView*>(view);
    newDatasetView->removeResultMessageWidget();
    QString name = newDatasetView->getName();
    QModelIndexList protocolsSel = newDatasetView->getProtocolsSelected();
    QVector<QString> protocolVector;
    for(int i=0; i<protocolsSel.size(); ++i)
        protocolVector.append(newDatasetView->getProtocolsTable()->model()->index(protocolsSel.at(i).row(), 0 ,protocolsSel.at(i)).data().toString());

    if(name.isEmpty() || group.isEmpty() || protocolsSel.size()==0)        
        newDatasetView->addResultMessageWidget("Name, Group of Subjects and at least one Protocol are Required", false);
    else {
        if(name.size()>maxChar) {
         newDatasetView->addResultMessageWidget("The name of the Dataset must not exceed "+QString::number(maxChar)+" characters.", false);
         return;
        }

        DatasetDAO *db = new DatasetDAO();
        if(db->createDataset(name, group, protocolVector)) {
            newDatasetView->resetFields();
            group.clear();
            protocol.clear();
            MainWindow::getMainWindow()->writeStatusBar("Dataset "+name+" inserted", 10000);
            newDatasetView->addResultMessageWidget("Dataset "+name+" inserted", true);
        }
        else newDatasetView->addResultMessageWidget("Dataset name already exists", false);
    }
}

void NewDatasetController::setEditFields(const QString &datasetE)
{
    NewDatasetView *newDatasetView = qobject_cast<NewDatasetView*>(view);

    DatasetDAO dao;
    Dataset *dataset = dao.getDatasetByName(datasetE);

    newDatasetView->setEditFields(dataset);
}

void NewDatasetController::slotBack()
{
    if(edit) MainWindowController::getMainWindowController()->slotShowDatasets(idEdit);
    else AController::slotBack();
}
