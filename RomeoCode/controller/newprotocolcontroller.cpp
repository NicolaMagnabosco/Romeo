#include "newprotocolcontroller.h"

using Romeo::Controller::NewProtocolController;
using Romeo::Model::Core::FeatCreator;
using Romeo::View::Dialog::Dialog;
using Romeo::Model::Util::DAO::ProtocolDAO;
using Romeo::Model::Core::Protocol;
using Romeo::Controller::MainWindowController;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::AlgCreator;
using Romeo::Model::Core::Algorithm::AAlgorithm;

NewProtocolController::NewProtocolController(NewProtocolView *view, QObject *parent) : AController(view,parent), edit(false), idEdit(""), dialogFeature(0) 
{
    createConnections();
}

NewProtocolController::NewProtocolController(NewProtocolView *view, const QString &protocol, QObject *parent) : AController(view,parent), edit(true), idEdit(protocol), dialogFeature(0) 
{
    createConnections();
}

void NewProtocolController::createConnections() const 
{

    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);

    connect(newProtocolView, SIGNAL(addFeatureClicked()), this, SLOT(slotAddFeatureClicked()));
    connect(newProtocolView, SIGNAL(typeChange(QString)), this, SLOT(slotTypeChanged(QString)));
    connect(newProtocolView, SIGNAL(saveObject()), this, SLOT(slotSaveProtocol()));
    connect(newProtocolView, SIGNAL(featureRemove()), this, SLOT(slotFeatureRemove()));
    connect(newProtocolView, SIGNAL(featureSelect(QModelIndex)), this, SLOT(slotFeatureSelect(QModelIndex)));
    connect(newProtocolView, SIGNAL(algorithmSelect(QString)), this, SLOT(slotAlgorithmSelect(QString)));
}

void NewProtocolController::slotAddFeatureClicked() 
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);
    newProtocolView->removeResultMessageWidget();
    dialogFeature = 0;
    FeatCreator *featCreator = FeatCreator::getFeatCreator();

    QString type = newProtocolView->getTypeSelected();
    if(type == Utils::ROMEO_IMAGE_TYPE_2D || type == Utils::ROMEO_IMAGE_TYPE_2Dt || type == Utils::ROMEO_IMAGE_TYPE_3D || type == Utils::ROMEO_IMAGE_TYPE_3Dt) {
        QVector<AFeature*> features;
        if(type == Utils::ROMEO_IMAGE_TYPE_2D) {
            features = featCreator->getAllFeaturesFirstOrder();
            features += featCreator->getAllFeaturesSecondOrder();
            if(features.size()>0)
                dialogFeature = new FeatureParams(features, newProtocolView);
            else
                newProtocolView->addResultMessageWidget("There are no Features for this type", false);
        }
        else if(type == Utils::ROMEO_IMAGE_TYPE_2Dt) {
            features = featCreator->getAllFeaturesDynamic();
            if(features.size()>0)
                dialogFeature = new FeatureParams(features, newProtocolView);
            else
                newProtocolView->addResultMessageWidget("There are no Features for this type", false);
        }
        else if(type == Utils::ROMEO_IMAGE_TYPE_3D) {
            features = featCreator->getAllFeaturesFirstOrder();
            features += featCreator->getAllFeaturesSecondOrder();
            if(features.size()>0)
                dialogFeature = new FeatureParams(features, newProtocolView);
            else
                newProtocolView->addResultMessageWidget("There are no Features for this type", false);
        }
        else if(type == Utils::ROMEO_IMAGE_TYPE_3Dt) {
            features = featCreator->getAllFeaturesDynamic();
            if(features.size()>0)
                dialogFeature = new FeatureParams(features, newProtocolView);
            else
                newProtocolView->addResultMessageWidget("There are no Features for this type", false);
        }
        if(dialogFeature) {
            connect(dialogFeature, SIGNAL(featureSelected(QString)), this, SLOT(slotFeatureSelected(QString)));
            connect(dialogFeature, SIGNAL(ok(QStringList)), this, SLOT(slotOk(QStringList)));
            dialogFeature->exec();
        }
    }
    else newProtocolView->addResultMessageWidget("Type is required", false);
}

void NewProtocolController::slotFeatureSelected(const QString &featureS) 
{
    if(featureS != Utils::ROMEO_SELECT_FEATURE) {
        FeatCreator *featCreator = FeatCreator::getFeatCreator();
        AFeature  *feature = featCreator->buildFeature(featureS);
        dialogFeature->setFeature(feature);

        if(feature->getType() == Utils::FEATURE_FIRST_ORDER) {
            dialogFeature->visibleBox(Utils::FEATURE_FIRST_ORDER);
        }
        else if(feature->getType() == Utils::FEATURE_SECOND_ORDER) {
            dialogFeature->visibleBox(Utils::FEATURE_SECOND_ORDER);
        }
        else if(feature->getType() == Utils::FEATURE_DYNAMIC) {
            dialogFeature->visibleBox(Utils::FEATURE_DYNAMIC);
        }
    }
    else dialogFeature->resetBox();
}

void NewProtocolController::slotOk(const QStringList &paramsS) 
{

    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);
    NewProtocolFeatureTableModel *model = qobject_cast<NewProtocolFeatureTableModel*>(newProtocolView->getFeaturesTable()->model());

    AFeature *feature = dialogFeature->getFeature();
    dialogFeature->close();
    feature->setParemeters(paramsS);

    model->addFeature(feature);
}

void NewProtocolController::slotTypeChanged(const QString &selection) 
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);
    NewProtocolFeatureTableModel *model = qobject_cast<NewProtocolFeatureTableModel*>(newProtocolView->getFeaturesTable()->model());

    model->resetModel();
}

void NewProtocolController::slotSaveProtocol() 
{
    int maxChar = 200;
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);
    NewProtocolFeatureTableModel *model = qobject_cast<NewProtocolFeatureTableModel*>(newProtocolView->getFeaturesTable()->model());

    newProtocolView->removeResultMessageWidget();

    QString name = newProtocolView->getProtocolName();
    QString type = newProtocolView->getTypeSelected();
    QVector<AFeature*> features = model->getFeatures();   

    QString algName = newProtocolView->getAlgorithmSelected();

    if(name.isEmpty() || type == Utils::ROMEO_SELECT_TYPE)
        newProtocolView->addResultMessageWidget("Name and type is required", false);
    else if(features.size()==0 && algName==Utils::ROMEO_SELECT_ALGORITHM){
        newProtocolView->addResultMessageWidget("Must be selected at least one Feature or Algorithm", false);
    }
    else {
        if(name.size()>maxChar) {
         newProtocolView->addResultMessageWidget("The name of the Protocol must not exceed "+QString::number(maxChar)+" characters.", false);
         return;
        }
        AlgCreator *ac = AlgCreator::getAlgCreator();
        AAlgorithm *alg = 0;
        if(algName!=Utils::ROMEO_SELECT_ALGORITHM) {
            alg = ac->buildAlgorithm(algName);
            QStringList params = newProtocolView->getAlgorithmParameters(alg);
            QStringList errors = alg->testParameters(params);
            if(errors.size()>0) {
                QString txt = "";
                for(int i=0; i<errors.size(); ++i)
                    txt += errors.at(i)+"\n";
                newProtocolView->addResultMessageWidget(txt, false);
                return;
            }
            alg->setParameters(params);
        }
        Protocol *protocol = new Protocol(name, type, features, alg);
        create_Update(protocol, name);
    }
}

void NewProtocolController::create_Update(Protocol *protocol, QString &name)
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);
    ProtocolDAO dao;

    if(edit) {
        Protocol *oldProtocol = dao.getProtocolByName(name);
        if(dao.updateProtocol(*protocol, *oldProtocol, featuresToRemove)) {
            newProtocolView->resetFields();
            MainWindow::getMainWindow()->writeStatusBar("Protocol "+name+" updated", 10000);
            newProtocolView->addResultMessageWidget("Protocol "+name+" updated", true);
            edit=false;
            idEdit.clear();
            featuresToRemove.clear();
        }
        else
            newProtocolView->addResultMessageWidget("Protocol name already exists", false);
    }
    else {
        if(dao.createProtocol(*protocol)) {
            newProtocolView->resetFields();
            MainWindow::getMainWindow()->writeStatusBar("Protocol "+name+" inserted", 10000);
            newProtocolView->addResultMessageWidget("Protocol "+name+" inserted", true);
        }
        else
            newProtocolView->addResultMessageWidget("Protocol name already exists", false);
    }
}

void NewProtocolController::setEditFields(const QString &protocolS) 
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);

    ProtocolDAO dao;
    Protocol *protocol = dao.getProtocolByName(protocolS);

    newProtocolView->setEditFields(protocol);
}

void NewProtocolController::slotBack() 
{
    if(edit) MainWindowController::getMainWindowController()->slotShowProtocols(idEdit);
    else AController::slotBack();
}

void NewProtocolController::slotFeatureRemove() 
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);
    NewProtocolFeatureTableModel *model = qobject_cast<NewProtocolFeatureTableModel*>(newProtocolView->getFeaturesTable()->model());

    QModelIndexList list = newProtocolView->getSelectedFeatures();

    if(list.size()>0) {
        int response = Dialog::dialogQuestion("Delete Features?", "Are you sure you want to delete the selected Features?");
        if(response == QMessageBox::Yes) {
            for(int i=0; i<list.size(); ++i){
                featuresToRemove.append(model->getFeatureId(list.at(i).row()));
            }

            model->removeFeatures(list);
        }
    }
}

void NewProtocolController::slotFeatureSelect(const QModelIndex &index)
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);

    QModelIndexList list = newProtocolView->getSelectedFeatures();
    if(list.size()>0)
        newProtocolView->enableRemoveFeatureButton(true);
    else
        newProtocolView->enableRemoveFeatureButton(false);
}

void NewProtocolController::slotAlgorithmSelect(const QString &selection) 
{
    NewProtocolView *newProtocolView = qobject_cast<NewProtocolView*>(view);

    newProtocolView->removeAlgorithmFields();

    if(selection!=Utils::ROMEO_SELECT_ALGORITHM) {
        AlgCreator *ac = AlgCreator::getAlgCreator();
        AAlgorithm *alg = ac->buildAlgorithm(selection);

        newProtocolView->setAlgorithmFields(alg);
    }
}
