#include "protocoltablemodel.h"

using Romeo::Model::QtModel::ProtocolTableModel;
using Romeo::Model::Util::DAO::ProtocolDAO;

ProtocolTableModel::ProtocolTableModel(QObject *parent) :
    TableModel(parent)
{
    loadModelData();
}

void ProtocolTableModel::loadModelData() {
    ProtocolDAO *db = new ProtocolDAO();
    protocols = db->getAllProtocol();
}

void ProtocolTableModel::refreshModelData() {
    beginResetModel();
    loadModelData();
    endResetModel();
}

int ProtocolTableModel::rowCount(const QModelIndex & parent) const
 {
    return protocols.size();
 }

int ProtocolTableModel::columnCount(const QModelIndex & parent) const
{
     return 3;
}

QVariant ProtocolTableModel::data(const QModelIndex &index, int role) const
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

            case 2:
                 return QString(protocols.at(index.row())->getCreationDate().toString(Utils::DATETIME_FORMAT));
                 break;
         }
     }
     return QVariant();
 }

QVariant ProtocolTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
