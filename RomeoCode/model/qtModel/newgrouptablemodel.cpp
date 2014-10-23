#include "newgrouptablemodel.h"

using Romeo::Model::QtModel::NewGroupTableModel;
using Romeo::Model::Util::DAO::SubjectDAO;

NewGroupTableModel::NewGroupTableModel(QObject *parent) :
    TableModel(parent)
{
}

int NewGroupTableModel::rowCount(const QModelIndex & parent) const
 {
    return subjects.size();
 }

int NewGroupTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant NewGroupTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
             return QString(subjects.at(index.row())->getName());
             break;

            case 1:
             if(subjects.at(index.row())->hasMask())return QString("Yes");
             return QString("No");
             break;
         }
     }
     return QVariant();
 }

QVariant NewGroupTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Mask");
                break;
            }
        }
        else if (orientation == Qt::Vertical) {
            return section+1;
        }
    }
    return QVariant();
}

void NewGroupTableModel::filterSubjectsForType(const QString& type) {
    this->beginResetModel();
    SubjectDAO *db = new SubjectDAO();
    subjects.clear();
    subjects = db->getSubjectsByType(type);

    this->endResetModel();
}

void NewGroupTableModel::resetListModel() {
    this->beginResetModel();
    subjects.clear();
    this->endResetModel();
}

NewGroupTableModel * NewGroupTableModel::getRefreshModelForType(const QString& type) {
    filterSubjectsForType(type);
    return this;
}
