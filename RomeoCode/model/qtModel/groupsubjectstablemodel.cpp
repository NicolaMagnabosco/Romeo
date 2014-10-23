#include "groupsubjectstablemodel.h"

using Romeo::Model::QtModel::GroupSubjectsTableModel;

GroupSubjectsTableModel::GroupSubjectsTableModel(QObject *parent) :
    TableModel(parent)
{
}

int GroupSubjectsTableModel::rowCount(const QModelIndex & parent) const
 {
    return subjects.size();
 }

int GroupSubjectsTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant GroupSubjectsTableModel::data(const QModelIndex &index, int role) const
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

QVariant GroupSubjectsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void GroupSubjectsTableModel::resetListModel() {
    this->beginResetModel();
    subjects.clear();
    this->endResetModel();
}

void GroupSubjectsTableModel::resetListModel(QVector<ASubject*> subjectsV) {
    this->beginResetModel();
    subjects.clear();
    subjects=subjectsV;
    this->endResetModel();
}
