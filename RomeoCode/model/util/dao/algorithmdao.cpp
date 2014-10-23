#include "algorithmdao.h"

using Romeo::Model::Util::DAO::AlgorithmDAO;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::AlgCreator;
using Romeo::Model::Core::Protocol;

AlgorithmDAO::AlgorithmDAO()
{

}

AAlgorithm* AlgorithmDAO::getAlgorithmById(int id)
{

    AAlgorithm* algorithm;
    QString queryString = "SELECT AlgorithmName, ParamValue FROM ClusterAlgorithm WHERE id="+id;
    QSqlQuery query(queryString, *getConnection());
    query.next();

    QString algorithmName = query.value(1).toString();
    QString algorithmParameters = query.value(2).toString();
    QStringList paramsList = algorithmParameters.split(";");
    algorithm = AlgCreator::getAlgCreator()->buildAlgorithm(algorithmName, paramsList);
    return algorithm;
}

int AlgorithmDAO::addAlgorithm(const AAlgorithm& algorithm)
{

    QString name = algorithm.getName();
    QStringList parametersList = algorithm.getParameters();
    QString parameters = parametersList.join(";");
    QString queryString = "INSERT INTO ClusterAlgorithm (AlgorithmName, ParamValue) VALUES ('"+name+"','"+parameters+"')";
    QSqlQuery query(queryString, *getConnection());

    return query.lastInsertId().toInt();
}

bool AlgorithmDAO::deleteAlgorithm(const QString &name, const QString &param)
{

    QString queryString = "DELETE FROM ClusterAlgorithm WHERE AlgorithmName='"+name+"' and ParamValue='"+param+"'";
    QSqlQuery query;
    return query.exec(queryString);
}

bool AlgorithmDAO::deleteAlgorithm(const int id)
{
    QString queryString = "DELETE FROM ClusterAlgorithm WHERE ID_Algorithm='"+QString::number(id)+"'";
    QSqlQuery query;
    return query.exec(queryString);
}

bool AlgorithmDAO::deleteAlgorithm(const AAlgorithm &algorithm)
{
    return deleteAlgorithm(algorithm.getId());
}

QVector<AAlgorithm*> AlgorithmDAO::getAllAlgorithm()
{

    QVector<AAlgorithm*> algorithms;
    QString queryString = "SELECT AlgorithmName, ParamValue FROM ClusterAlgorithm";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString algorithmName = query.value(1).toString();
        QString algorithmParameters = query.value(2).toString();
        QStringList paramsList = algorithmParameters.split(";");
        algorithms.append(AlgCreator::getAlgCreator()->buildAlgorithm(algorithmName, paramsList));
    }
    return algorithms;
}

AAlgorithm* AlgorithmDAO::getAlgorithmOfProtocol(const Protocol &protocol)
{
    return getAlgorithmOfProtocol(protocol.getName());
}

AAlgorithm* AlgorithmDAO::getAlgorithmOfProtocol(const QString& protocolName)
{
    AAlgorithm* algorithm = 0;
    QString queryString = "SELECT ClusterAlgorithm.ID_Algorithm, ClusterAlgorithm.AlgorithmName, ClusterAlgorithm.ParamValue FROM ClusterAlgorithm JOIN Protocol on ClusterAlgorithm.ID_Algorithm=Protocol.ID_Algorithm WHERE Protocol.ProtocolName='"+protocolName+"'";
    QSqlQuery query(queryString, *getConnection());

    if(query.next()) {
        int algId = query.value(0).toInt();
        QString algorithmName = query.value(1).toString();
        QString algorithmParamters = query.value(2).toString();
        QStringList paramsList = algorithmParamters.split(";");
        algorithm = AlgCreator::getAlgCreator()->buildAlgorithm(algorithmName, paramsList, algId);
    }

    return algorithm;
}

int AlgorithmDAO::updateAlgorithm(const AAlgorithm *newAlg, const AAlgorithm *oldAlg)
{
    int ret = -1;
    if(newAlg && oldAlg){
        if(newAlg->getName()!=oldAlg->getName()){
            deleteAlgorithm(*oldAlg);
            ret = addAlgorithm(*newAlg);
        }
        else{
            QStringList parametersList = newAlg->getParameters();
            QString parameters = parametersList.join(";");
            QString queryString = "UPDATE ClusterAlgorithm SET AlgorithmName='"+newAlg->getName()+"', ParamValue='"+parameters+"' WHERE ID_Algorithm='"+QString::number(oldAlg->getId())+"'";
            QSqlQuery query;
            query.exec(queryString);
            ret = oldAlg->getId();
        }
    }
    else if(!newAlg && oldAlg) {
        deleteAlgorithm(*oldAlg);
        ret = 0;
    }
    else if(newAlg && !oldAlg){
        ret = addAlgorithm(*newAlg);
    }

    return ret;
}
