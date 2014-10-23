#include "subjecttablemodel.h"

using Romeo::Model::QtModel::SubjectTableModel;
using Romeo::Model::Util::DAO::SubjectDAO;

SubjectTableModel::SubjectTableModel(QObject *parent) :
    TableModel(parent)
{
    loadModelData();
}

void SubjectTableModel::loadModelData() {
    SubjectDAO db;
    subjects = db.getAllSubjects();
}

int SubjectTableModel::rowCount(const QModelIndex & parent) const
 {
    return subjects.size();
 }

int SubjectTableModel::columnCount(const QModelIndex & parent) const
{
     return 4;
}

QVariant SubjectTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
                return QString(subjects.at(index.row())->getName());
                break;

            case 1:
                 return QString(subjects.at(index.row())->getType());
                 break;

            case 2:
                 if(subjects.at(index.row())->hasMask())return QString("Yes");
                 return QString("No");
                 break;

            case 3:
                return QString(subjects.at(index.row())->getCreationDate().toString(Utils::DATETIME_FORMAT));
                break;
         }
     }
     return QVariant();
 }

QVariant SubjectTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Name");
                break;
            case 1:
                return QString("Type");
                break;
            case 2:
                return QString("Mask");
                break;
            case 3:
                return QString("Creation Date");
                break;
            }
        }
        else if (orientation == Qt::Vertical) {
            return section+1;
        }
    }
    return QVariant();
}


SubjectTableModel::~SubjectTableModel()
{
    QVector<ASubject*>::const_iterator it = subjects.constBegin();
    for(; it != subjects.constEnd() ; ++it) {
        //obtain the subject pointed by the iterator
        ASubject *subject = *it;
        //remove the subject from the heap
        delete subject;
    }

}
