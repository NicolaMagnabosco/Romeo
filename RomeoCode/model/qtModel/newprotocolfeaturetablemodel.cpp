#include "newprotocolfeaturetablemodel.h"

using Romeo::Model::QtModel::NewProtocolFeatureTableModel;

NewProtocolFeatureTableModel::NewProtocolFeatureTableModel(QObject *parent) :
    TableModel(parent)
{
}

int NewProtocolFeatureTableModel::rowCount(const QModelIndex & parent) const
 {
    return features.size();
 }

int NewProtocolFeatureTableModel::columnCount(const QModelIndex & parent) const
{
     return 2;
}

QVariant NewProtocolFeatureTableModel::data(const QModelIndex &index, int role) const
 {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
             return QString(features.at(index.row())->getName());
             break;

            case 1:
                {
                     QString featTxt;
                     if(features.at(index.row())->getType()==Utils::FEATURE_FIRST_ORDER) {
                         featTxt += Utils::FEATURE_WINDOW_SIZE+": "+features.at(index.row())->getParameters().at(0);
                     }
                     else if(features.at(index.row())->getType()==Utils::FEATURE_SECOND_ORDER) {
                         featTxt += Utils::FEATURE_WINDOW_SIZE+": "+features.at(index.row())->getParameters().at(0);
                         featTxt += "\n";
                         featTxt += Utils::FEATURE_GLCM+": "+features.at(index.row())->getParameters().at(1);
                     }
                     else if(features.at(index.row())->getType()==Utils::FEATURE_DYNAMIC) {
                         featTxt += Utils::FEATURE_INITIAL_FRAME+": "+features.at(index.row())->getParameters().at(0);
                         featTxt += "\n";
                         featTxt += Utils::FEATURE_FINAL_FRAME+": "+features.at(index.row())->getParameters().at(1);
                     }
                     return featTxt;
                     break;
                 }
         }
     }
     return QVariant();
 }

QVariant NewProtocolFeatureTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Parameters");
                break;
            }
        }
        else if (orientation == Qt::Vertical) {
            return section+1;
        }
    }
    return QVariant();
}

void NewProtocolFeatureTableModel::addFeature(AFeature* feat) {
    this->beginResetModel();
    features.append(feat);
    this->endResetModel();
}

void NewProtocolFeatureTableModel::resetModel() {
    this->beginResetModel();
    features.clear();
    this->endResetModel();
}

QVector<AFeature*> NewProtocolFeatureTableModel::getFeatures() const {
    return features;
}

void NewProtocolFeatureTableModel::removeFeatures(QModelIndexList indexes)
{
    this->beginResetModel();
    for(int i=0; i<indexes.size(); ++i){        
        int n = indexes.at(i).row();
        AFeature *del = features.at(n);
        features.removeAt(n);
        delete del;
    }    
    this->endResetModel();
}

int NewProtocolFeatureTableModel::getFeatureId(int index) const {
    return features.at(index)->getId();
}
