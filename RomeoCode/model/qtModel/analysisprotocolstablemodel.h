#ifndef ANALYSISPROTOCOLSTABLEMODEL_H
#define ANALYSISPROTOCOLSTABLEMODEL_H

#include <QAbstractTableModel>
#include "model/core/protocol.h"
#include "model/util/dao/featuredao.h"
#include "model/core/feature/afeature.h"
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::Protocol;
using Romeo::Model::Core::Feature::AFeature;

/*!
 *\file analysisprotocolstablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-24
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                                +       Description             |
*+----------+------------+-----------------+-----------------------------------------------------+-------------------------------+
*|                                                                                                                               |
*|   0.0.1  | 2013-03-24 | Martignago Jimmy | Romeo::Model::qtModel::AnalysisProtocolsTableModel |    First version of class     |
*|                                                                                                                               |
*+----------+------------+-----------------+-----------------------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class AnalysisProtocolsTableModel, extends TableModel, represents the model for the table of features on the analyisi view.
         */
            class AnalysisProtocolsTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the name of the protocol
                 */
                QVector<QString> protocolName;
                /*!
                 * \brief Is the vector with the features of the model.
                 */
                QVector<AFeature*> features;
                /*!
                 * \brief Is the vector with the flags yes or no for the show features.
                 */
                QVector<QString> show;
                /*!
                 * \brief Is the vector with the flags yes or no for the save features.
                 */
                QVector<QString> save;

            public:
                /*!
                 * \brief Constructor of the AnalysisProtocolsTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                AnalysisProtocolsTableModel(QObject *parent = 0);
                /*!
                 * \brief Returns the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
                 */
                int rowCount(const QModelIndex &parent = QModelIndex()) const ;
                /*!
                 * \brief Returns the number of columns for the children of the given parent.
                 */
                int columnCount(const QModelIndex &parent = QModelIndex()) const;
                /*!
                 * \brief Returns the data stored under the given role for the item referred to by the index.
                 */
                QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
                /*!
                 * \brief Returns the data for the given role and section in the header with the specified orientation.
                 */
                QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
                /*!
                 * \brief The method load the data on the model with the given protocols
                 * \param protocolsV is the vector of protocols to load.
                 */
                void loadModelData(const QVector<Protocol*>& protocolsV);
                /*!
                 * \brief The method reset the model.
                 */
                void resetModelData();

                /*!
                 * \brief The method toogle state of show flag of the index
                 */
                void setShowProtocol(const QModelIndex &index);
                /*!
                 * \brief The method toogle state of save flag of the index
                 */
                void setSaveProtocol(const QModelIndex &index);

                /*!
                 * \brief The method toogle the save flag state of all features
                 */
                void saveAll();
                /*!
                 * \brief The method toogle the show flag state of all features
                 */
                void showAll();

                /*!
                 * \brief The method get the features to save
                 * \return Return the vector of the features to save.
                 */
                QVector<QString> getFeaturesToSave() const;
                /*!
                 * \brief The method get the features to show
                 * \return Return the vector of the features to show.
                 */
                QVector<QString> getFeaturesToShow() const;
                /*!
                 * \brief The method get al the features of the model.
                 * \return Return the vector of the features.
                 */
                QVector<AFeature*> getFeatures() const;

            };
        }
    }
}

#endif // ANALYSISPROTOCOLSTABLEMODEL_H
