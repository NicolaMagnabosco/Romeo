#include "groupofsubject.h"

using Romeo::Model::Core::GroupOfSubject;

GroupOfSubject::GroupOfSubject(const QString& nameGroup, const QString& type, QVector<ASubject*> subjectsV, const QDateTime& dateTime): imageType(type), name(nameGroup), subjects(subjectsV), creationDate(dateTime)
{
}

QString GroupOfSubject::getName() const
{
    return name;
}

QString GroupOfSubject::getImageType() const
{
    return imageType;
}

QDateTime GroupOfSubject::getCreationDate() const
{
    return creationDate;
}

bool GroupOfSubject::addSubject(const ASubject &subject)
{
    //find indicates if the subject was been found
    bool find = false;
    QVector<ASubject*>::const_iterator it = subjects.constBegin();
    //search if exists already a subject with the same name of the given subject
    for(; it != subjects.constEnd(); ++it) {

        ASubject *iSubject = *it;
        if(iSubject->getName() == subject.getName())
            find = true;
    }
    //if not exist any subject with the same name the subject is added to the subjects vector
    if(!find) {

        //cast the subject
        ASubject *cSubject = const_cast<ASubject*>(&subject);
        //add the subject to the vector
        subjects.append(cSubject);
    }
    //return the result of the operation
    return !find;
}

bool GroupOfSubject::containSubject(const ASubject &subject) const
{
    //find indicates if the subject was been found.
    bool find = false;
    QVector<ASubject*>::const_iterator it = subjects.constBegin();
    for(; !find && it != subjects.constEnd(); ++it) {

        //obtain the current subject
        ASubject *iSubject = *it;
        if(subject.getName() == (*iSubject).getName())
            find = true;
    }

    return find;
}

ASubject *GroupOfSubject::getSubjectWithName(const QString &name) const
{
    ASubject *result = 0;
    //find indicates if the subject was been found
    bool find = false;
    QVector<ASubject*>::const_iterator it = subjects.constBegin();
    //search if the given subject is contained in the subject
    for(; !find && it != subjects.constEnd(); ++it) {

        //obtain the subject pointed from iterator
        ASubject *subject = *it;
        //obtain the subjectname
        QString subjectName = subject->getName();
        if(name==subjectName) {

            result = subject;
            //for exit the for
            find = true;
        }
    }
    return result;
}

bool GroupOfSubject::removeSubject(const ASubject &subject)
{

    //find indicates if the subject was been found
    bool find = false;
    QVector<ASubject*>::iterator it = subjects.begin();
    //search if the given subject is contained in the subject.
    for(; it != subjects.end(); ++it) {

        //obtain the subject
        ASubject *iSubject = *it;
        if(iSubject == &subject) {

            //remove the subject from the vector
            subjects.erase(it);
            //for exit the for
            find = true;
        }
    }
    return find;
}

QVector<ASubject*> GroupOfSubject::getAllSubjects() const
{

    return subjects;
}

int GroupOfSubject::subjectsCount() const
{

    return subjects.size();
}


GroupOfSubject::~GroupOfSubject()
{
    for(QVector<ASubject*>::const_iterator it = subjects.constBegin(); it != subjects.constEnd(); ++it) {
        //obtain the controller object
        ASubject *subject = *it;
        //deallocate the object
        delete subject;
    }
}
