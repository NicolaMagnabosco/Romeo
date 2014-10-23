#include "datasetprotocoltablemodel.h"

using Romeo::Model::QtModel::DatasetProtocolTableModel;
using Romeo::Model::Util::DAO::ProtocolDAO;

DatasetProtocolTableModel::DatasetProtocolTableModel(QObject *parent) :
    TableModel(parent)
{
}

void DatasetProtocolTableModel::loadModelData(const QString& type) {
    beginResetModel();
    ProtocolDAO * dao = new ProtocolDAO();
    protocols = dao->getProtocolsOfType(type);
    endResetModel();
}

void DatasetProtocolTableModel::resetDatasetModel() {
    beginResetModel();
    protocols.clear();
    endResetModel();
}

int DatasetProtocolTableModel::rowCount(const QModelIndex & parent) const
 {
    return protocols.size();
 }

int DatasetProtocolTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant DatasetProtocolTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
                return QString(protocols.at(index.row())->getName());
                break;

            case 1:
                 return QString(protocols.at(index.row())->getType());
                 break;
         }
     }
     return QVariant();
 }

QVariant DatasetProtocolTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
