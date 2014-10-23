#include "featuredao.h"

using Romeo::Model::Util::DAO::FeatureDAO;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::Protocol;
using Romeo::Model::Core::FeatCreator;

FeatureDAO::FeatureDAO(): ADatabase()
{
}

bool FeatureDAO::existFeature(const int id) const
{

    //represent if exists alredy a subject with the given name or not.
    bool result = false;
    QString queryString = "SELECT COUNT(*) FROM Feature WHERE ID_Feature='"+QString::number(id)+"'";
    QSqlQuery query(queryString,*getConnection());
    query.next();
    //numRows contains the number of subject with the given name
    int numRows = query.value(0).toInt();
    //if exists at least a subject with the given name, set the result variable to true
    if (numRows>0)
        result = true;
    //return the result
    return result;
}

bool FeatureDAO::createFeature(const AFeature &feature, const Protocol &protocol)
{

    QString featureName = feature.getName();
    QStringList featParamsList = feature.getParameters();
    QString featureParameters = featParamsList.join(";");
    QString protocolName = protocol.getName();
    QString queryString = "INSERT INTO Feature (FeatureName, ParamValue, ProtocolName) VALUES ('"+featureName+"','"+featureParameters+"','"+protocolName+"')";
    QSqlQuery query;
    return query.exec(queryString);

}

bool FeatureDAO::updateFeature(const AFeature &feature, const Protocol &protocol)
{
    if(existFeature(feature.getId())){
        return true;
    }
    else{
        return createFeature(feature, protocol);
    }
}

bool FeatureDAO::removeFeature(const QString& protocol)
{
    QString queryString = "DELETE FROM Feature WHERE ProtocolName='"+protocol+"'";
    QSqlQuery query;

    return query.exec(queryString);
}

bool FeatureDAO::removeFeature(const int id)
{
    QString queryString = "DELETE FROM Feature WHERE ID_Feature='"+QString::number(id)+"'";
    QSqlQuery query;

    return query.exec(queryString);
}

QVector<AFeature*> FeatureDAO::getAllFeatureOfProtocol(Protocol* protocol)
{
    QVector<AFeature*> features;
    QString protocolName = protocol->getName();
    QString queryString = "SELECT FeatureName, ParamValue, ID_Feature FROM Feature WHERE ProtocolName='"+protocolName+"'";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString featureName = query.value(0).toString();
        QString parametersValue = query.value(1).toString();
        int id = query.value(2).toInt();
        QStringList paramsList = parametersValue.split(";");
        FeatCreator* creator = FeatCreator::getFeatCreator();
        features.append(creator->buildFeature(featureName, paramsList, id));
    }
    return features;
}

AFeature* FeatureDAO::getFeatureOfProtocol(QString& featureName, Protocol* protocol)
{
    AFeature* feature;
    QString protocolName = protocol->getName();
    QString queryString = "SELECT FeatureName, ParamValue, ID_Feature FROM Feature WHERE FeatureName='"+featureName+"' and ProtocolName='"+protocolName+"'";
    QSqlQuery query(queryString, *getConnection());
    query.next();
    QString fName = query.value(0).toString();
    QString paramValue = query.value(1).toString();
    int id = query.value(2).toInt();
    QStringList paramsList = paramValue.split(";");
    feature = FeatCreator::getFeatCreator()->buildFeature(fName, paramsList, id);
    return feature;
}

QVector<AFeature*> FeatureDAO::getAllFeatureOfProtocol(const QString& protocolName)
{
    QVector<AFeature*> features;
    QString queryString = "SELECT * FROM Feature WHERE ProtocolName='"+protocolName+"'";
    QSqlQuery query;
    query.exec(queryString);
    while (query.next()) {
        int id = query.value(0).toInt();
        QString featureName = query.value(1).toString();
        QString parametersValue = query.value(2).toString();
        QStringList paramsList = parametersValue.split(";");
        FeatCreator* creator = FeatCreator::getFeatCreator();
        features.append(creator->buildFeature(featureName, paramsList, id));
    }
    return features;
}
