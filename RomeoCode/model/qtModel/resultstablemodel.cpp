#include "resultstablemodel.h"

using Romeo::Model::QtModel::ResultsTableModel;
using Romeo::Model::Util::DAO::AnalysisDAO;

ResultsTableModel::ResultsTableModel(QObject *parent) :
    TableModel(parent)
{
    loadModelData();
}

void ResultsTableModel::loadModelData() {
    AnalysisDAO db;
    analysis = db.getAllAnalysis();
}

int ResultsTableModel::rowCount(const QModelIndex & parent) const
 {
    return analysis.size();
 }

int ResultsTableModel::columnCount(const QModelIndex & parent) const
{
     return 5;
}

QVariant ResultsTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
             case 0:
                  return QString::number(analysis.at(index.row())->getID());
                  break;

            case 1:{
                if(analysis.at(index.row())->getComplete())
                    return Utils::ROMEO_YES;
                else
                    return Utils::ROMEO_NO;

                break;
            }

            case 2:
                 return QString(analysis.at(index.row())->getDataset()->getName());
                 break;

            case 3:{
                return QString::number(analysis.at(index.row())->getSelectedSubjectCount())+"/"+QString::number(analysis.at(index.row())->getTotalSubjects());
                break;
            }

            case 4:
                return QString(analysis.at(index.row())->getCreationDate().toString(Utils::DATETIME_FORMAT));
                break;
         }
     }

     return QVariant();
 }

QVariant ResultsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("ID");
                break;
            case 1:
                return QString("Completed");
                break;
            case 2:
                return QString("Dataset");
                break;
            case 3:
                return QString("Subjects Selected");
                break;
            case 4:
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

ResultsTableModel::~ResultsTableModel()
{
    for(int i=0; i<analysis.size() ; ++i) {
        Analysis *analysisObj = analysis.at(i);
        delete analysisObj;
    }
}

QVector<int> ResultsTableModel::getIdAnalysis() const {
    QVector<int> ret;

    for(int i=0; i<analysis.size(); ++i) {
        ret.append(analysis.at(i)->getID());
    }

    return ret;
}
