#include "subjectdao.h"

using Romeo::Model::Util::DAO::SubjectDAO;
using Romeo::Model::Core::ProxySubject;

SubjectDAO::SubjectDAO()
{
}

bool SubjectDAO::existSubjecWithName(const QString &name) const
{

    //represent if exists alredy a subject with the given name or not.
    bool result = false;
    QString queryString = "SELECT COUNT(*) FROM Subject WHERE SubjectName='"+name+"'";    
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

ASubject *SubjectDAO::getSubjectByName(const QString &name) const
{
    //represent the subject result of the method.
    ASubject *subject = 0;
    //check if exists a subject with the given name
    if (existSubjecWithName(name)) {

        QString queryString= "SELECT * FROM Subject WHERE SubjectName='"+name+"'";
        QSqlQuery query(queryString, *getConnection());
        query.next();
        QString subjectName=query.value(0).toString();
        QString subjectImage=Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(1).toString();
        QString subjectMask=(query.value(2).toString().isEmpty() ? "" : Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(2).toString());
        QString subjectType=query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(4).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        subject=new ProxySubject(subjectName, subjectImage, subjectType, subjectMask, dateTime);
    }

    return subject;
}

QVector<ASubject*> SubjectDAO::getAllSubjects() const
{

    QVector<ASubject*> subjects;
    QString queryString = "SELECT * FROM Subject";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString subjectName=query.value(0).toString();
        QString subjectImage=Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(1).toString();
        QString subjectMask=(query.value(2).toString().isEmpty() ? "" : Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(2).toString());
        QString subjectType=query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(4).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        //create the subject object with the data obtained
        ASubject *subject = new ProxySubject(subjectName, subjectImage, subjectType, subjectMask, dateTime);
        //append the subject to the list of subject
        subjects.append(subject);
    }
    return subjects;
}

bool SubjectDAO::createSubject(const ASubject &subject)
{

    QString subjectName = subject.getName();
    if (!existSubjecWithName(subjectName)) {
        QString subjectImage = subject.getImage();
        QString subjectMask = subject.getMask();
        QString subjectType = subject.getType();
        QString dateTime=QDateTime::currentDateTime().toString(Utils::DATETIME_FORMAT_COMPLETE);
        QString queryString("INSERT INTO Subject (SubjectName, Image, Mask, ImageType, CreationDate) VALUES ('"+subjectName+"','"+subjectImage+ "','"+subjectMask+"','"+subjectType+"','"+dateTime+"')");
        QSqlQuery query;
        if(query.exec(queryString))
            return true;
    }

    return false;
}

QVector<QString> SubjectDAO::getAllSubjectsName() const
{

    QVector<QString> subjects;
    QString queryString = "SELECT SubjectName FROM Subject";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString subjectName=query.value(0).toString();
        subjects.append(subjectName);
    }
    return subjects;
}

QVector<ASubject*> SubjectDAO::getSubjectsByType(const QString& type) const
{

    QVector<ASubject*> subjects;
    QString queryString = "SELECT * FROM Subject WHERE ImageType='"+type+"'";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString subjectName=query.value(0).toString();
        QString subjectImage=Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(1).toString();
        QString subjectMask=(query.value(2).toString().isEmpty() ? "" : Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(2).toString());
        QString subjectType=query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(4).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        ProxySubject *subject = new ProxySubject(subjectName, subjectImage, subjectType, subjectMask, dateTime);
        subjects.append(subject);
    }
    return subjects;
}

QVector<ASubject*> SubjectDAO::subjectsOfGroup(const QString& group) const
{
    QVector<ASubject*> subjects;

    QString queryString = "SELECT Subject.* ";
    queryString.append("FROM Subject JOIN Subject_Group ON Subject.SubjectName=Subject_Group.SubjectName ");
    queryString.append("WHERE Subject_Group.GroupName='"+group+"'");
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString name = query.value(0).toString();
        QString image = Utils::SAVING_SUBJECT_PATH+"/"+name+"/"+query.value(1).toString();
        QString mask = (query.value(2).toString().isEmpty() ? "" : Utils::SAVING_SUBJECT_PATH+"/"+name+"/"+query.value(2).toString());
        QString type=query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(4).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        subjects.append(new ProxySubject(name, image, type, mask, dateTime));
    }

    return subjects;
}


QVector<QString> SubjectDAO::getGroupsOfSubject(const QString& subject) const
{
    QVector<QString> groups;
    QString queryString = "SELECT GroupName FROM Subject_Group WHERE SubjectName='"+subject+"'";

    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        groups.append(query.value(0).toString());
    }
    return groups;
}

QVector<ASubject*> SubjectDAO::getSubjectsOfDataset(const QString& dataset) const
{
    QVector<ASubject*> subjects;
    QString queryString = "SELECT s.* FROM Subject_Group g JOIN Dataset d ON d.GroupName=g.GroupName JOIN Subject s ON s.SubjectName=g.SubjectName WHERE d.DatasetName='"+dataset+"';";
    QSqlQuery query(queryString, *getConnection());

    while (query.next()) {
        QString subjectName=query.value(0).toString();
        QString subjectImage = Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(1).toString();
        QString subjectMask = (query.value(2).toString().isEmpty() ? "" : Utils::SAVING_SUBJECT_PATH+"/"+subjectName+"/"+query.value(2).toString());
        QString subjectType=query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(4).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        subjects.append(new ProxySubject(subjectName, subjectImage, subjectType, subjectMask, dateTime));
    }

    return subjects;
}
