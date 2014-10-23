#include "analysisprotocolstablemodel.h"

using Romeo::Model::QtModel::AnalysisProtocolsTableModel;
using Romeo::Model::Util::DAO::FeatureDAO;

AnalysisProtocolsTableModel::AnalysisProtocolsTableModel(QObject *parent) :
    TableModel(parent)
{
}

void AnalysisProtocolsTableModel::loadModelData(const QVector<Protocol*>& protocolsV) {
    this->beginResetModel();
    protocolName.clear();
    features.clear();
    show.clear();
    save.clear();

    QVector<Protocol*> protocol = protocolsV;
    FeatureDAO dao;

    for(int i=0; i<protocol.size(); ++i){
        QString nameP = protocol.at(i)->getName();
        QVector<AFeature*> feature = dao.getAllFeatureOfProtocol(nameP);
        for(int j=0; j<feature.size(); ++j){
            protocolName.append(nameP);
            features.append(feature.at(j));
        }
    }

    show.fill(Utils::ROMEO_NO, features.size());
    save.fill(Utils::ROMEO_NO, features.size());

    this->endResetModel();
}

void AnalysisProtocolsTableModel::resetModelData() {
    beginResetModel();
    protocolName.clear();
    features.clear();
    show.clear();
    save.clear();
    endResetModel();
}

int AnalysisProtocolsTableModel::rowCount(const QModelIndex & parent) const
 {
    return features.size();
 }

int AnalysisProtocolsTableModel::columnCount(const QModelIndex & parent) const
{
     return 4;
}

QVariant AnalysisProtocolsTableModel::data(const QModelIndex &index, int role) const {
     if (role == Qt::DisplayRole)
     {
         switch (index.column()) {
            case 0:
                return QString(protocolName.at(index.row()));
                break;

            case 1:
                 return QString(features.at(index.row())->getName());
                 break;

            case 2:
                  return show.at(index.row());
                  break;

            case 3:
                  return save.at(index.row());
                  break;
         }
     }
     if(role == Qt::DecorationRole) {
         if(index.column() == 2) {
             if(show.at(index.row()) == Utils::ROMEO_NO)
                return QIcon(":/Romeo/checkboxNo.png");
             else
                return QIcon(":/Romeo/checkboxYes.png");
         }
         else if(index.column() == 3) {
             if(save.at(index.row()) == Utils::ROMEO_NO)
                return QIcon(":/Romeo/checkboxNo.png");
             else
                return QIcon(":/Romeo/checkboxYes.png");
         }
     }
     return QVariant();
 }

QVariant AnalysisProtocolsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Protocol");
                break;
            case 1:
                return QString("Feature");
                break;
            case 2:
                return QString("Show");
                break;
            case 3:
                return QString("Save");
                break;
            }
        }
        else if (orientation == Qt::Vertical) {
            return section+1;
        }
    }
    return QVariant();
}

void AnalysisProtocolsTableModel::setShowProtocol(const QModelIndex &index) {
    beginResetModel();
    if(show.at(index.row()) == Utils::ROMEO_NO) {
        show.replace(index.row(), Utils::ROMEO_YES);
    }
    else{
        show.replace(index.row(), Utils::ROMEO_NO);
    }
    endResetModel();
}

void AnalysisProtocolsTableModel::setSaveProtocol(const QModelIndex &index) {
    beginResetModel();
    if(save.at(index.row()) == Utils::ROMEO_NO) {
        save.replace(index.row(), Utils::ROMEO_YES);
    }
    else {
        save.replace(index.row(), Utils::ROMEO_NO);
    }
    endResetModel();
}

void AnalysisProtocolsTableModel::saveAll() {
    beginResetModel();

    bool saveState = false;

    int y = 0;
    int n = 0;
    for(int i=0; i<save.size(); ++i) {
        if(save.at(i) == Utils::ROMEO_NO) n++;
        else y++;
    }
    if(n == save.size()) saveState = false;
    else if(y == save.size()) saveState = true;

    if(saveState){
        save.fill(Utils::ROMEO_NO, features.size());
        saveState = false;
    }
    else {
        save.fill(Utils::ROMEO_YES, features.size());
        saveState = true;
    }
    endResetModel();
}

void AnalysisProtocolsTableModel::showAll()
{
    beginResetModel();

    bool showState = false;
    int y = 0;
    int n = 0;
    for(int i=0; i<show.size(); ++i) {
        if(show.at(i) == Utils::ROMEO_NO) n++;
        else y++;
    }
    if(n == show.size()) showState = false;
    else if(y == show.size()) showState = true;

    if(showState) {
        show.fill(Utils::ROMEO_NO, features.size());
        showState = false;
    }
    else {
        show.fill(Utils::ROMEO_YES, features.size());
        showState = true;
    }
    endResetModel();
}

QVector<QString> AnalysisProtocolsTableModel::getFeaturesToSave() const {
    return save;
}

QVector<QString> AnalysisProtocolsTableModel::getFeaturesToShow() const {
    return show;
}

QVector<AFeature*> AnalysisProtocolsTableModel::getFeatures() const {
    return features;
}
