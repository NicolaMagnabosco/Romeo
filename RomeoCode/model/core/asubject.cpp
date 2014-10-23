#include "asubject.h"

using Romeo::Model::Core::ASubject;



ASubject::ASubject(const QString& stringName, const QString& stringImage, const QString& stringType, const QString& stringMask, const QDateTime& dateTime): name(stringName), image(stringImage), type(stringType), mask(stringMask), creationDate(dateTime) {

}

QString ASubject::getName() const
{

    return name;
}

QString ASubject::getImage() const
{

    return image;
}

QString ASubject::getMask() const
{

    return mask;
}

QDateTime ASubject::getCreationDate() const {
    return creationDate;
}

bool ASubject::hasMask() const
{
    return !mask.isEmpty();
}

QString ASubject::getType() const
{
    return type;
}
