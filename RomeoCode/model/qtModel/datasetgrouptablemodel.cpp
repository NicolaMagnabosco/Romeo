#include "datasetgrouptablemodel.h"

using Romeo::Model::QtModel::DatasetGroupTableModel;
using Romeo::Model::Util::DAO::GroupDAO;

DatasetGroupTableModel::DatasetGroupTableModel(QObject *parent) :
    TableModel(parent)
{
    loadModelData();
}

void DatasetGroupTableModel::loadModelData() {
    GroupDAO *db = new GroupDAO();
    groups = db->getAllGroup();
}

void DatasetGroupTableModel::resetDatasetModel() {
    beginResetModel();
    loadModelData();
    endResetModel();
}

int DatasetGroupTableModel::rowCount(const QModelIndex & parent) const
 {
    return groups.size();
 }

int DatasetGroupTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant DatasetGroupTableModel::data(const QModelIndex &index, int role) const
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
         }
     }
     return QVariant();
 }

QVariant DatasetGroupTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            }
        }
        else if (orientation == Qt::Vertical) {
            return section+1;
        }
    }
    return QVariant();
}
