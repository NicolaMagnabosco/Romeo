#include "groupdao.h"

using Romeo::Model::Util::DAO::GroupDAO;
using Romeo::Model::Core::ASubject;
using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Core::ProxySubject;
using Romeo::Model::Util::DAO::SubjectDAO;

GroupDAO::GroupDAO() {

}

bool GroupDAO::existGroupWithName(const QString& name)
{

    QString queryString = "SELECT * FROM GroupOfSubject WHERE GroupName='"+name+"'";
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

bool GroupDAO::existGroupWithName(const QString& newName, const QString& oldName)
{
    QString queryString = "SELECT * FROM GroupOfSubject WHERE GroupName<>'"+oldName+"' AND GroupName='"+newName+"'";
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

QVector<GroupOfSubject*> GroupDAO::getAllGroup()
{

    QVector<GroupOfSubject*> groups;
    QString queryString = "SELECT * FROM GroupOfSubject";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        QString name = query.value(0).toString();
        QString imageType = query.value(1).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(2).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        QVector<ASubject*> subjects = getSubjectsOfGroup(name);

        groups.append(new GroupOfSubject(name, imageType, subjects, dateTime));
    }
    return groups;
}

QVector<QString> GroupDAO::getAllGroupName()
{

    QVector<QString> groups;
    QString queryString = "SELECT GroupName FROM GroupOfSubject";
    QSqlQuery query(queryString, *getConnection());
    while (query.next()) {
        groups.append(query.value(0).toString());
    }
    return groups;
}

GroupOfSubject* GroupDAO::getGroupByName(const QString &name)
{

    GroupOfSubject* group = 0;
    if (existGroupWithName(name)) {

        QString queryString = "SELECT * FROM GroupOfSubject WHERE GroupName='"+name+"'";
        QSqlQuery query(queryString, *getConnection());
        query.next();
        QString groupName = query.value(0).toString();
        QString imageType = query.value(1).toString();
        QDateTime dateTime = QDateTime::fromString(query.value(2).toString(), Utils::DATETIME_FORMAT_COMPLETE);
        QVector<ASubject*> subjects = getSubjectsOfGroup(groupName);

        group = new GroupOfSubject(groupName, imageType, subjects, dateTime);
    }

    return group;
}

bool GroupDAO::createGroup(const GroupOfSubject& group)
{

    if (!existGroupWithName(group.getName())) {
        QString name=group.getName();
        QString imageType = group.getImageType();
        QString dateTime=QDateTime::currentDateTime().toString(Utils::DATETIME_FORMAT_COMPLETE);
        QString queryString = "INSERT INTO GroupOfSubject (GroupName, ImageType, CreationDate) VALUES ('"+name+"','"+imageType+"','"+dateTime+"')";
        QSqlQuery query;

        if(query.exec(queryString)){
            QVector<ASubject*> subjects = group.getAllSubjects();
            bool ok = true;
            for (int i=0; i<subjects.size() && ok; ++i) {
                ok = addSubjectToGroup(subjects.at(i), group);
            }

            return ok;
        }

        return false;
    }

    return false;
}

bool GroupDAO::deleteGroup(const QString& group)
{

    if(!existGroupWithName(group)) return false;

    QString queryString = "DELETE FROM GroupOfSubject WHERE GroupName='"+group+"'";
    QSqlQuery query;
    return query.exec(queryString);
}

bool GroupDAO::addSubjectToGroup(const ASubject* subject, const GroupOfSubject& group) {

    QString queryString("INSERT INTO Subject_Group (SubjectName, GroupName) VALUES ('"+subject->getName()+"','"+group.getName()+ "')");
    QSqlQuery query;
    return query.exec(queryString);
}

bool GroupDAO::removeSubjectFromGroup(const ASubject& subject, const GroupOfSubject& group)
{

    if (existGroupWithName(group.getName())) {
        QString subjectName = subject.getName();
        QString groupName = group.getName();
        QString queryString("DELETE FROM Subject_Group WHERE SubjectName='"+subjectName+"' and GroupName='"+groupName+ "'");
        QSqlQuery query;

        return query.exec(queryString);
    }

    return false;

}

QVector<ASubject*> GroupDAO::getSubjectsOfGroup(const QString& group)
{

    QVector<ASubject*> subjects;
    if (existGroupWithName(group)) {
        SubjectDAO dao;
        subjects = dao.subjectsOfGroup(group);
    }

    return subjects;

}

bool GroupDAO::updateGroupOfSubject(const GroupOfSubject& group)
{
    if(existGroupWithName(group.getName())) {
        QString groupName = group.getName();
        QVector<ASubject*> oldSubjects = getSubjectsOfGroup(groupName);
        QVector<ASubject*> subjects = group.getAllSubjects();

        bool ok = true;
        for(int i=0; i<oldSubjects.size() && ok; ++i)
            ok = removeSubjectFromGroup(*oldSubjects.at(i), group);

        if(ok){
            for (int i=0; i<subjects.size() && ok; ++i) {
                ok = addSubjectToGroup(subjects.at(i), group);
            }
        }

        return ok;
    }

    return false;
}
