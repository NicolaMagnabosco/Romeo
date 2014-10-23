#include "grouptablemodel.h"

using Romeo::Model::QtModel::GroupTableModel;
using Romeo::Model::Util::DAO::GroupDAO;

GroupTableModel::GroupTableModel(QObject *parent) :
    TableModel(parent)
{
    loadModelData();
}

void GroupTableModel::loadModelData() {
    GroupDAO *db = new GroupDAO();
    groups = db->getAllGroup();
}

void GroupTableModel::refreshModelData() {
    beginResetModel();
    loadModelData();
    endResetModel();
}

int GroupTableModel::rowCount(const QModelIndex & parent) const
 {
    return groups.size();
 }

int GroupTableModel::columnCount(const QModelIndex & parent) const
{
     return 4;
}

QVariant GroupTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
             return QString(groups.at(index.row())->getName());
             break;

            case 1:
             return QString(groups.at(index.row())->getImageType());
             break;

             case 2:
              return QString::number(groups.at(index.row())->subjectsCount());
              break;

             case 3:
              return QString(groups.at(index.row())->getCreationDate().toString(Utils::DATETIME_FORMAT));
              break;
         }
     }
     return QVariant();
 }

QVariant GroupTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Subjects");
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
