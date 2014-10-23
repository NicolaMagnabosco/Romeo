#include "protocol.h"

using Romeo::Model::Core::Protocol;

using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::Feature::AFeature;


Protocol::Protocol(const QString& pName, const QString& pType, QVector<AFeature*> feats, AAlgorithm *alg, const QDateTime& dateTime): name(pName), type(pType), features(feats), algorithm(alg), creationDate(dateTime)
{

}

Protocol::Protocol(const QString& pName, const QString& pType, const QDateTime& dateTime): name(pName), type(pType), features(QVector<AFeature*>()), algorithm(0), creationDate(dateTime)
{

}

bool Protocol::hasAlgorithm() const
{
    return algorithm;
}


QVector<AFeature*> Protocol::getFeatures() const
{
    return features;
}

AAlgorithm* Protocol::getAlgorithm() const
{
    return algorithm;
}


void Protocol::addFeature(AFeature *newFeature)
{
    features.append(newFeature);
}

void Protocol::setAlgorithm(AAlgorithm* newAlgorithm)
{
    algorithm=newAlgorithm;
}

QString Protocol::getName() const
{
    return name;
}

QString Protocol::getType() const
{
    return type;
}

QDateTime Protocol::getCreationDate() const
{
    return creationDate;
}

int Protocol::getNumberOfFeatures() const
{
    return features.size();
}

Protocol::~Protocol()
{
    for(QVector<AFeature*>::const_iterator it = features.constBegin(); it != features.constEnd(); ++it) {
        //obtain the feature pointed by it
        AFeature *feature = *it;
        //deallocate the feature from the heap
        delete feature;
    }
    delete algorithm;
}
