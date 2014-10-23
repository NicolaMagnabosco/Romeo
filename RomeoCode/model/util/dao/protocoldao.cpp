#include "protocoldao.h"

using Romeo::Model::Util::DAO::ProtocolDAO;
using Romeo::Model::Core::Protocol;
using Romeo::Model::Util::DAO::FeatureDAO;
using Romeo::Model::Util::DAO::AlgorithmDAO;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::Dataset;
using Romeo::Model::Util::DAO::DatasetDAO;

ProtocolDAO::ProtocolDAO()
{
}

bool ProtocolDAO::existProtocolWithName(const QString &name)
{
    QString queryString = "SELECT * FROM Protocol WHERE ProtocolName='"+name+"'";
    QSqlQuery query(queryString,*getConnection());
    int numRows=0;
    while (query.next()) {
        numRows++;
    }

    if (numRows>0)
        return true;
    else
        return false;
}

QVector<Protocol*> ProtocolDAO::getAllProtocol()
{
    QVector<Protocol*> protocols;
    QString queryString = "SELECT * FROM Protocol";
    QSqlQuery query;
    query.exec(queryString);

    while(query.next()) {
        QString protocolName = query.value(0).toString();
        QString imageType = query.value(1).toString();

        QDateTime dateTime = QDateTime::fromString(query.value(3).toString(), Utils::DATETIME_FORMAT_COMPLETE);

        protocols.append(new Protocol(protocolName, imageType, dateTime));
    }

    FeatureDAO featuredao;
    AlgorithmDAO algorithmdao;
    for(int i=0; i<protocols.size(); ++i) {

        QVector<AFeature*> features = featuredao.getAllFeatureOfProtocol(protocols.at(i)->getName());
        for(int j=0; j<features.size(); j++)
            protocols.at(i)->addFeature(features.at(j));

        AAlgorithm* algorithm = algorithmdao.getAlgorithmOfProtocol(protocols.at(i)->getName());
        if(algorithm) protocols.at(i)->setAlgorithm(algorithm);
    }

    return protocols;
}

Protocol* ProtocolDAO::getProtocolByName(const QString &name)
{
    Protocol* protocol;

    QString queryString = "SELECT * FROM Protocol WHERE ProtocolName='"+name+"'";
    QSqlQuery queryz;
    queryz.exec(queryString);
    queryz.next();

    QString protocolName = queryz.value(0).toString();
    QString type = queryz.value(1).toString();
    QDateTime dateTime = QDateTime::fromString(queryz.value(3).toString(), Utils::DATETIME_FORMAT_COMPLETE);

    FeatureDAO *featuredao = new FeatureDAO();
    QVector<AFeature*> features = featuredao->getAllFeatureOfProtocol(protocolName);

    AlgorithmDAO *algorithmdao = new AlgorithmDAO();
    AAlgorithm* algorithm = algorithmdao->getAlgorithmOfProtocol(protocolName);

    protocol=new Protocol(protocolName, type, features, algorithm, dateTime);

    return protocol;
}

bool ProtocolDAO::createProtocol(const Protocol& protocol)
{
    QString protocolName = protocol.getName();
    if (!existProtocolWithName(protocolName)) {        
        QString type = protocol.getType();
        AAlgorithm* algorithm = protocol.getAlgorithm();
        bool algInsert = true;
        int lastAlgorithmID = -1;
        QVector<AFeature*> features = protocol.getFeatures();

        if(algorithm) {
            //insert algorithm in database
            AlgorithmDAO algorithmdao;
            lastAlgorithmID = algorithmdao.addAlgorithm(*algorithm);
            //get the id of the last algorithm
            QString queryAlgorithm = "SELECT MAX(ID_Algorithm) FROM ClusterAlgorithm";
            QSqlQuery query;
            algInsert = query.exec(queryAlgorithm);
        }

        //insert the protocol in database
        QString dateTime=QDateTime::currentDateTime().toString(Utils::DATETIME_FORMAT_COMPLETE);
        QString queryProtocol;
        if(algInsert){
            if(!algorithm && lastAlgorithmID == -1){
                queryProtocol = "INSERT INTO Protocol(ProtocolName, ImageType, CreationDate) VALUES ('"+protocolName+"', '"+type+"', '"+dateTime+"')";
            }
            else{
                queryProtocol = "INSERT INTO Protocol(ProtocolName, ImageType, ID_Algorithm, CreationDate) VALUES ('"+protocolName+"', '"+type+"', '"+QString::number(lastAlgorithmID)+"', '"+dateTime+"')";
            }
            QSqlQuery insertProtocol;
            if(insertProtocol.exec(queryProtocol)) {
                //insert the feature of protocol in database
                FeatureDAO featuredao;
                QVector<AFeature*>::const_iterator it = features.constBegin();
                for (; it!=features.constEnd(); ++it) {
                    if(!featuredao.createFeature(**it, protocol)) return false;
                }

                return true;
            }
        }
    }
    
    return false;
}

bool ProtocolDAO::updateProtocol(const Protocol& newProtocol, const Protocol& oldProtocol, QVector<int> featuresToRemove)
{
    QString protocolName = newProtocol.getName();
    if (existProtocolWithName(protocolName)) {
        AAlgorithm* newAlgorithm = newProtocol.getAlgorithm();
        AAlgorithm* oldAlg = oldProtocol.getAlgorithm();
        QVector<AFeature*> newFeatures = newProtocol.getFeatures();

        FeatureDAO featuredao;
        AlgorithmDAO algorithmdao;

        for (int i=0; i<featuresToRemove.size(); ++i) {
            featuredao.removeFeature(featuresToRemove.at(i));
        }

        for (int i=0; i<newFeatures.size(); ++i) {
            if(!featuredao.updateFeature(*(newFeatures.at(i)), newProtocol)) return false;
        }

        int lastId = algorithmdao.updateAlgorithm(newAlgorithm, oldAlg);
        if(lastId > 0){
            QString queryStr = "UPDATE Protocol SET ID_Algorithm='"+QString::number(lastId)+"' WHERE ProtocolName='"+protocolName+"'";
            QSqlQuery queryUp;
            queryUp.exec(queryStr);
        }
        else if(lastId == 0) {
            QString queryStr = "UPDATE Protocol SET ID_Algorithm='' WHERE ProtocolName='"+protocolName+"'";
            QSqlQuery queryUp;
            queryUp.exec(queryStr);
        }

        return true;
    }

    return false;
}

bool ProtocolDAO::deleteProtocol(const Protocol& protocol)
{
    QString protocolName = protocol.getName();
    if (existProtocolWithName(protocolName)) {
        QVector<QString> datasets = getDatasetOfProtocol(protocolName);

        QString deleteProtocol = "DELETE FROM Protocol WHERE ProtocolName='"+protocolName+"'";
        QSqlQuery queryDelete;
        if(queryDelete.exec(deleteProtocol)) {
            DatasetDAO ddao;
            AlgorithmDAO adao;

            if(protocol.getAlgorithm()){
                adao.deleteAlgorithm(protocol.getAlgorithm()->getId());
            }

            if(datasets.size()>0)
                for(int i=0; i<datasets.size(); ++i)
                    ddao.deleteDataset(datasets.at(i));

            return true;
        }
    }

    return false;
}

bool ProtocolDAO::deleteProtocol(const QString& name) {
    return deleteProtocol(*getProtocolByName(name));
}

QVector<QString> ProtocolDAO::getAllProtocolName()
{
    QVector<QString> protocols;
    QString queryString = "SELECT ProtocolName FROM Protocol";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString protocolName = query.value(0).toString();
        protocols.append(protocolName);
    }
    return protocols;
}

QVector<Protocol*> ProtocolDAO::getAllProtocolOfDataset(const QString &datasetName)
{

    return QVector<Protocol*>();
}

QVector<QString> ProtocolDAO::getDatasetOfProtocol(const QString &protocol)
{
    QVector<QString> ret;

    QString queryString = "SELECT * FROM Dataset_Protocol WHERE ProtocolName='"+protocol+"'";

    QSqlQuery query;
    query.exec(queryString);

    while (query.next()) {
        ret.append(query.value(0).toString());
    }

    return  ret;
}

QVector<Protocol*> ProtocolDAO::getProtocolsOfType(const QString& type)
{
    QVector<Protocol*> protocols;
    QString queryString = "SELECT * FROM Protocol WHERE ImageType='"+type+"'";
    QSqlQuery query;
    query.exec(queryString);

    while(query.next()) {
        QString protocolName = query.value(0).toString();
        QString imageType = query.value(1).toString();

        QDateTime dateTime = QDateTime::fromString(query.value(3).toString(), Utils::DATETIME_FORMAT_COMPLETE);

        protocols.append(new Protocol(protocolName, imageType, dateTime));
    }

    return protocols;
}
