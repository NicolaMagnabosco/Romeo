#include "datasetstablemodel.h"

using Romeo::Model::QtModel::DatasetsTableModel;
using Romeo::Model::Util::DAO::DatasetDAO;

DatasetsTableModel::DatasetsTableModel(QObject *parent) :
    TableModel(parent)
{
    loadModelData();
}

void DatasetsTableModel::loadModelData() {
    beginResetModel();
    DatasetDAO dao;
    datasets = dao.getAllDataset();
    endResetModel();
}

void DatasetsTableModel::refreshModelData() {
    beginResetModel();
    loadModelData();
    endResetModel();
}

int DatasetsTableModel::rowCount(const QModelIndex & parent) const
 {
    return datasets.size();
 }

int DatasetsTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant DatasetsTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
                return QString(datasets.at(index.row())->getName());
                break;

            case 1:
                 return QString(datasets.at(index.row())->getCreationDate().toString(Utils::DATETIME_FORMAT));
                 break;
         }
     }
     return QVariant();
 }

QVariant DatasetsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
