#include "dataset.h"

using Romeo::Model::Core::Dataset;

Dataset::Dataset(const QString& datasetName, GroupOfSubject *groupOfSubject, QVector<Protocol *> vProtocols, const QDateTime& dateTime): name(datasetName), group(groupOfSubject), protocols(vProtocols), creationDate(dateTime) {

}

QString Dataset::getName() const {

    return name;
}

GroupOfSubject *Dataset::getGroup() const {

    return group;
}

QVector<Protocol*> Dataset::getProtocols() const
{
    return protocols;
}

QDateTime Dataset::getCreationDate() const {
    return creationDate;
}

int Dataset::getNumberOfProtocols() const
{
    return protocols.size();
}

int Dataset::getNumberOfFeaturesAssociated() const
{
    int number = 0;
    for(QVector<Protocol*>::const_iterator it = protocols.constBegin(); it != protocols.constEnd(); ++it) {
        Protocol * protocol = *it;
        number += protocol->getNumberOfFeatures();
    }

    return number;
}

int Dataset::getNumberOfAlgAssociated() const
{
    int number = 0;
    for(QVector<Protocol*>::const_iterator it = protocols.constBegin(); it != protocols.constEnd(); ++it) {
        Protocol *protocol = *it;
        if(protocol->hasAlgorithm())
            number++;
    }
    return number;
}

Dataset::~Dataset()
{
    //deallocate the group of subject from the heap
    delete group;
    //deallocate the protocols from the heap
    for(QVector<Protocol*>::const_iterator it = protocols.constBegin(); it != protocols.constEnd(); ++it) {
        //obtain the protocol
        Protocol *protocol = *it;
        delete protocol;
    }

}
