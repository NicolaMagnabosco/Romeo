#include "protocolscontroller.h"

using Romeo::Controller::ProtocolsController;
using Romeo::Model::Util::DAO::FeatureDAO;
using Romeo::Model::Util::DAO::AlgorithmDAO;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::View::Dialog::Dialog;
using Romeo::Model::Util::DAO::ProtocolDAO;
using Romeo::Model::QtModel::ProtocolTableModel;
using Romeo::Controller::MainWindowController;

ProtocolsController::ProtocolsController(ProtocolsView *view, QObject *parent): AController(view, parent)
{
    createConnections();
}

void ProtocolsController::createConnections() const
{
    ProtocolsView *protocolsView = qobject_cast<ProtocolsView*>(view);

    connect(protocolsView, SIGNAL(protocolSelected(QModelIndex)), this, SLOT(slotProtocolSelected(QModelIndex)));
    connect(protocolsView, SIGNAL(deleteObject()), this, SLOT(slotDeleteProtocol()));
    connect(protocolsView, SIGNAL(editObject()), this, SLOT(slotEditProtocol()));
}

void ProtocolsController::slotProtocolSelected(const QModelIndex &index)
{
    ProtocolsView *protocolsView = qobject_cast<ProtocolsView*>(view);

    item = protocolsView->getProtocolsTable()->model()->index(index.row(), 0 ,index).data().toString();

    FeatureDAO featuredao;
    QVector<AFeature*> features = featuredao.getAllFeatureOfProtocol(item);

    featuresInfo(features);

    AlgorithmDAO algorithmdao;
    AAlgorithm* algorithm = algorithmdao.getAlgorithmOfProtocol(item);
    algorithmInfo(algorithm);
}

void ProtocolsController::featuresInfo(QVector<AFeature*> features) const
{
    ProtocolsView *protocolsView = qobject_cast<ProtocolsView*>(view);

    if(features.size()>0) {
        QString txt = "";

        for(int i=0; i<features.size(); ++i) {
            QStringList params = features.at(i)->getParameters();
            txt.append(features.at(i)->getName());

            if(features.at(i)->getType()==Utils::FEATURE_FIRST_ORDER) {
                txt+=" ("+Utils::FEATURE_WINDOW_SIZE+": "+params.at(0)+")";
            }
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
        protocolsView->getFeatureLabel()->setText(txt);
        protocolsView->getFeatureBox()->setVisible(true);
    }
    else {
        protocolsView->getFeatureBox()->setVisible(false);
    }
}

void ProtocolsController::algorithmInfo(AAlgorithm* algorithm) const
{
    ProtocolsView *protocolsView = qobject_cast<ProtocolsView*>(view);

    if(algorithm) {
        QString txt;
        txt.append(algorithm->getName());

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

        protocolsView->getAlgorithmLabel()->setText(txt);
        protocolsView->getAlgorithmBox()->setVisible(true);
    }
    else {
        protocolsView->getAlgorithmBox()->setVisible(false);
    }
}

void ProtocolsController::slotDeleteProtocol()
{
    ProtocolsView *protocolsView = qobject_cast<ProtocolsView*>(view);

    protocolsView->removeResultMessageWidget();

    if(item.isEmpty()) protocolsView->addResultMessageWidget("You must select a protocol", false);
    else {
        int response = Dialog::dialogQuestion("Delete Protocol?", "Are you sure you want to delete the Protocol \""+item+"\"?", "If you delete the Protocol will be deleted all the Datasets associated");
        if(response == QMessageBox::Yes) {            
            QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(protocolsView->getProtocolsTable()->model());
            ProtocolTableModel *model = qobject_cast<ProtocolTableModel*>(proxyModel->sourceModel());

            ProtocolDAO *db = new ProtocolDAO();
            if(db->deleteProtocol(item)){
                MainWindow::getMainWindow()->writeStatusBar("Protocol "+item+" deleted", 3000);
                protocolsView->addResultMessageWidget("Protocol "+item+" deleted", true);
            }
            else Dialog::dialogCritical("Delete Error", "Protocol does not exist in the database");
            item.clear();

            protocolsView->resetProtocolInfo();
            model->refreshModelData();
        }
    }
}

void ProtocolsController::slotEditProtocol()
{
    ProtocolsView *protocolsView = qobject_cast<ProtocolsView*>(view);

    protocolsView->removeResultMessageWidget();

    if(!item.isEmpty()) {
        MainWindowController::getMainWindowController()->slotEditProtocol(item);
    }
    else protocolsView->addResultMessageWidget("You must select a Protocol to edit it", false);
}
