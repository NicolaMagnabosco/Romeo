#include "analysissubjectstablemodel.h"

using Romeo::Model::QtModel::AnalysisSubjectsTableModel;
using Romeo::Model::Util::DAO::DatasetDAO;

AnalysisSubjectsTableModel::AnalysisSubjectsTableModel(QObject *parent) :
    TableModel(parent)
{
}

void AnalysisSubjectsTableModel::loadModelData(const QString& dataset) {
    this->beginResetModel();
    DatasetDAO *db = new DatasetDAO();
    subjects.clear();
    subjects = db->getAllSubjectsOfDataset(dataset);
    this->endResetModel();
}

void AnalysisSubjectsTableModel::resetModelData() {
    beginResetModel();
    subjects.clear();
    endResetModel();
}

int AnalysisSubjectsTableModel::rowCount(const QModelIndex & parent) const
 {
    return subjects.size();
 }

int AnalysisSubjectsTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant AnalysisSubjectsTableModel::data(const QModelIndex &index, int role) const {
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

QVariant AnalysisSubjectsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
