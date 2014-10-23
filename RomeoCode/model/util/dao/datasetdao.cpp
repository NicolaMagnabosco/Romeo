#include "datasetdao.h"

using Romeo::Model::Util::DAO::DatasetDAO;
using Romeo::Model::Core::Dataset;
using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Util::DAO::SubjectDAO;
using Romeo::Model::Util::DAO::ProtocolDAO;

DatasetDAO::DatasetDAO() {

}

bool DatasetDAO::existDatasetWithName(const QString &name)
{

    QString queryString = "SELECT * FROM Dataset WHERE DatasetName='"+name+"'";
    QSqlQuery query(queryString, *getConnection());
    int numRows=0;
    while (query.next()) {
        numRows++;
    }
    if (numRows>0)
        return true;
    else
        return false;
}

QVector<Dataset*> DatasetDAO::getAllDataset()
{

    QVector<Dataset*> datasets;
    QVector<Protocol*> protocols;
    QString queryString = "SELECT * FROM Dataset";
    QSqlQuery query(queryString, *getConnection());
    GroupDAO groupdao;
    ProtocolDAO protocoldao;
    while (query.next()) {
        QString name = query.value(0).toString();
        QString groupName = query.value(1).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(2).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        GroupOfSubject* group = groupdao.getGroupByName(groupName);
        QString findProtocols = "SELECT ProtocolName FROM Dataset_Protocol WHERE DatasetName='"+name+"'";
        QSqlQuery queryFind(findProtocols, *getConnection());
        while (queryFind.next()) {
            QString protocolName = queryFind.value(0).toString();
            protocols.append(protocoldao.getProtocolByName(protocolName));
        }
        datasets.append(new Dataset(name, group, protocols, dateTime));
    }
    return datasets;

}

QVector<QString> DatasetDAO::getAllDatasetName()
{
    QVector<QString> datasets;
    QString queryString = "SELECT DatasetName FROM Dataset";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString name = query.value(0).toString();
        datasets.append(name);
    }
    return datasets;
}

GroupOfSubject* DatasetDAO::getGroupOfDataset(const Dataset& dataset)
{
    return getGroupOfDataset(dataset.getName());
}

GroupOfSubject* DatasetDAO::getGroupOfDataset(const QString& dataset)
{
    GroupOfSubject* group=0;

    if (existDatasetWithName(dataset)) {

        QString queryString = "SELECT GroupName FROM Dataset WHERE DatasetName='"+dataset+"'";
        QSqlQuery query(queryString, *getConnection());
        query.next();
        GroupDAO groupdao;
        group = groupdao.getGroupByName(query.value(0).toString());

    }
    return group;

}

QVector<Protocol*> DatasetDAO::getProtocolsOfDataset(const Dataset &dataset)
{
    return getProtocolsOfDataset(dataset.getName());
}

QVector<Protocol*> DatasetDAO::getProtocolsOfDataset(const QString &dataset)
{

    QVector<Protocol*> protocols;
    if(existDatasetWithName(dataset)) {
        QString findProtocol = "SELECT * FROM Dataset_Protocol WHERE DatasetName='"+dataset+"'";
        QSqlQuery query;
        query.exec(findProtocol);
        ProtocolDAO protocoldao;
        while(query.next()) {
            QString protocolName = query.value(1).toString();
            protocols.append(protocoldao.getProtocolByName(protocolName));
        }
    }

    return protocols;
}

bool DatasetDAO::createDataset(const QString& name, const QString& group, const QVector<QString>& protocolVector)
{
    if (existDatasetWithName(name))
        return false;

    QString dateTime=QDateTime::currentDateTime().toString(Utils::DATETIME_FORMAT_COMPLETE);
    QString insertDataset = "INSERT INTO Dataset (DatasetName, GroupName, CreationDate) VALUES ('"+name+"','"+group+"','"+dateTime+"')";
    QSqlQuery query;
    if(query.exec(insertDataset)) {
        for(int i=0; i<protocolVector.size(); ++i){
            QString queryStringDP = "INSERT INTO Dataset_Protocol (DatasetName, ProtocolName) VALUES ('"+name+"','"+protocolVector.at(i)+"')";
            QSqlQuery queryDP(queryStringDP, *getConnection());
        }
        return true;
    }

    return false;
}

QVector<ASubject*> DatasetDAO::getAllSubjectsOfDataset(const QString& dataset)
{
    SubjectDAO dao;

    QVector<ASubject*> subjects = dao.getSubjectsOfDataset(dataset);

    return subjects;
}

bool DatasetDAO::deleteDataset(const QString& dataset) {

    if (existDatasetWithName(dataset)) {
        QString deleteDataset = "DELETE FROM Dataset WHERE DatasetName='"+dataset+"'";
        QSqlQuery queryDelete;
        return queryDelete.exec(deleteDataset);
    }

    return false;
}

Dataset *DatasetDAO::getDatasetByName(const QString& name)
{
    Dataset *ret = 0;


    QString queryString = "SELECT * FROM Dataset WHERE DatasetName='"+name+"'";
    QSqlQuery query;
    query.exec(queryString);
    query.next();

    GroupOfSubject *group = getGroupOfDataset(name);
    QVector<Protocol*> protocols = getProtocolsOfDataset(name);
    QDateTime dateTime = QDateTime::fromString(query.value(2).toString(), Utils::DATETIME_FORMAT_COMPLETE);

    ret = new Dataset(name, group, protocols, dateTime);

    return ret;
}
