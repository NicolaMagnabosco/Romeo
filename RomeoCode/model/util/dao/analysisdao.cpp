#include "analysisdao.h"

using Romeo::Model::Util::DAO::AnalysisDAO;
using Romeo::Model::Util::DAO::DatasetDAO;
using Romeo::Model::Util::DAO::SubjectDAO;
using Romeo::Model::Core::Dataset;

AnalysisDAO::AnalysisDAO()
{
}

bool AnalysisDAO::existAnalysis(int id) const
{
    bool result = false;
    if(id != -1){
        QString queryString = "SELECT COUNT(*) FROM Analysis WHERE ID_Analysis='"+QString::number(id)+"'";
        QSqlQuery query(queryString,*getConnection());
        query.next();
        int numRows = query.value(0).toInt();
        if (numRows>0)
            result = true;
    }
    return result;
}

QVector<QString> AnalysisDAO::createAnalysis(const Analysis &analysis)
{
    QVector<QString> ret(2, QString::number(-1));
    if(!existAnalysis(analysis.getID())) {
        QDateTime timestamp = QDateTime::currentDateTime();
        ret.replace(1, timestamp.toString());
        QString dateTime=timestamp.toString(Utils::DATETIME_FORMAT_COMPLETE);
        QString dataset = analysis.getDataset()->getName();
        QVector<QString> selectedSubject = analysis.getSelectedSubject();
        QMap<int, bool> featuresShow = analysis.getFeaturesShow();
        QMapIterator<int, bool> it1(featuresShow);
        QMap<int, bool> featuresSave = analysis.getFeaturesSave();
        QMapIterator<int, bool> it2(featuresSave);

        QString queryString("INSERT INTO Analysis (CreationDate, DatasetName) VALUES ('"+dateTime+"', '"+dataset+"')");
        QSqlQuery query;
        if(query.exec(queryString)) {
            QString lastID = query.lastInsertId().toString();
            ret.replace(0, lastID);

            QString queryStringSubject("INSERT INTO Analysis_Subject (ID_Analysis, SubjectName) VALUES ");
            QSqlQuery querySubject;
            for(int i=0; i<selectedSubject.size(); ++i){
                queryStringSubject.append("('"+lastID+"', '"+selectedSubject.at(i)+"')");
                if(i<selectedSubject.size()-1) queryStringSubject.append(", ");
            }
            querySubject.exec(queryStringSubject);

            QString queryStringFeatures("INSERT INTO Analysis_Features_Save_Show (ID_Analysis, ID_Feature, Save, Show) VALUES ");
            QSqlQuery queryFeatures;
            for(int i=0; i<featuresShow.size(); ++i) {
                it1.next();
                it2.next();
                QString save = (it2.value() ? QString::number(1) : QString::number(0));
                QString show = (it1.value() ? QString::number(1) : QString::number(0));
                queryStringFeatures.append("('"+lastID+"', '"+QString::number(it1.key())+"', '"+save+"', '"+show+"')");
                if(i<featuresShow.size()-1) queryStringFeatures.append(", ");
            }
            queryFeatures.exec(queryStringFeatures);
        }
    }

    return ret;
}

bool AnalysisDAO::setComplete(int id)
{
    QString queryString("UPDATE Analysis SET Complete='1' WHERE ID_Analysis='"+QString::number(id)+"'");
    QSqlQuery query;
    return query.exec(queryString);
}

QVector<ASubject*> AnalysisDAO::getSelectedSubject(int id) const
{
    QVector<ASubject*> ret;
    SubjectDAO dao;

    QString queryString("SELECT SubjectName FROM Analysis_Subject WHERE ID_Analysis='"+QString::number(id)+"'");
    QSqlQuery query;
    if(query.exec(queryString))
        while (query.next())
            ret.append(dao.getSubjectByName(query.value(0).toString()));

    return ret;
}

QVector<QString> AnalysisDAO::getSelectedSubjectString(int id) const
{
    QVector<QString> ret;

    QVector<ASubject*> subs = getSelectedSubject(id);
    for(int i=0; i<subs.size(); ++i) {
        ret.append(subs.at(i)->getName());
    }

    return ret;
}

QMap<int, bool> AnalysisDAO::getFeatShow(int id) const
{
    QMap<int, bool> ret;

    QString queryString("SELECT ID_Feature,Show FROM Analysis_Features_Save_Show WHERE ID_Analysis='"+QString::number(id)+"'");
    QSqlQuery query;
    if(query.exec(queryString))
        while (query.next()) {
            ret.insert(query.value(0).toInt(), query.value(1).toBool());
        }

    return ret;
}

QMap<int, bool> AnalysisDAO::getFeatSave(int id) const
{
    QMap<int, bool> ret;

    QString queryString("SELECT ID_Feature,Save FROM Analysis_Features_Save_Show WHERE ID_Analysis='"+QString::number(id)+"'");
    QSqlQuery query;
    if(query.exec(queryString))
        while (query.next()) {
            ret.insert(query.value(0).toInt(), query.value(1).toBool());
        }

    return ret;
}

QVector<Analysis*> AnalysisDAO::getAllAnalysis() const
{
    QVector<Analysis*> ret;

    QString queryString("SELECT * FROM Analysis ORDER BY ID_Analysis DESC");
    QSqlQuery query;
    if(query.exec(queryString)) {
        while (query.next()) {
            int id = query.value(0).toInt();
            DatasetDAO daoDataset;
            Dataset *dataset = daoDataset.getDatasetByName(query.value(3).toString());
            QVector<QString> subjects = getSelectedSubjectString(id);
            QMap<int, bool> featShow = getFeatShow(id);
            QMap<int, bool> featSave = getFeatSave(id);
            QDir directory = QDir();
            QDateTime dateTime = QDateTime::fromString(query.value(2).toString(), Utils::DATETIME_FORMAT_COMPLETE);

            Analysis *analysis = new Analysis(dataset, subjects, featShow, featSave, directory, id, dateTime);
            analysis->setComplete(query.value(1).toBool());

            ret.append(analysis);
        }
    }

    return ret;
}

Analysis *AnalysisDAO::getAnalysis(int id) const
{
    Analysis *ret = 0;

    QString queryString("SELECT * FROM Analysis WHERE ID_Analysis='"+QString::number(id)+"'");
    QSqlQuery query;
    if(query.exec(queryString)) {
        query.next();
        int id = query.value(0).toInt();
        DatasetDAO daoDataset;
        Dataset *dataset = daoDataset.getDatasetByName(query.value(3).toString());
        QVector<QString> subjects = getSelectedSubjectString(id);
        QMap<int, bool> featShow = getFeatShow(id);
        QMap<int, bool> featSave = getFeatSave(id);
        QDir directory = QDir();
        QDateTime dateTime = QDateTime::fromString(query.value(2).toString(), Utils::DATETIME_FORMAT_COMPLETE);

        ret = new Analysis(dataset, subjects, featShow, featSave, directory, id, dateTime);
        ret->setComplete(query.value(1).toBool());
    }

    return ret;
}

QString AnalysisDAO::getDatasetname(int id)
{
    Analysis *an = getAnalysis(id);
    QString ret = an->getDataset()->getName();
    delete an;

    return ret;
}
