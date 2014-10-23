#ifndef NEWPROTOCOLFEATURETABLEMODEL_H
#define NEWPROTOCOLFEATURETABLEMODEL_H

#include <QAbstractTableModel>
#include "model/core/feature/afeature.h"
#include <QVector>
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::Feature::AFeature;

/*!
 *\file newprotocoltablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-02-22
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-02-22 | Martignago Jimmy|    Romeo::Model::NewProtocolTableModel     |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class NewProtocolFeatureTableModel, extends TableModel, represents the model for the table of features on the new protocol view.
         */
            class NewProtocolFeatureTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the vector with the features of the model.
                 */
                QVector<AFeature*> features;

            public:
                /*!
                 * \brief Constructor of the NewProtocolFeatureTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                NewProtocolFeatureTableModel(QObject *parent = 0);
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
                 * \brief The method add the feature to the model.
                 * \param feat is the feature to add.
                 */
                void addFeature(AFeature* feat);
                /*!
                 * \brief The method reset the model.
                 */
                void resetModel();
                /*!
                 * \brief The method return the features in the model
                 * \return Return a vector with features pointer.
                 */
                QVector<AFeature*> getFeatures() const;
                /*!
                 * \brief The method remove the feature in the model based on index.
                 */
                void removeFeatures(QModelIndexList indexes);
                /*!
                 * \brief Return the id of the feature of the model of the given index.
                 * \return Return the id of feature.
                 */
                int getFeatureId(int index) const;

            };
        }
    }
}

#endif // NEWPROTOCOLFEATURETABLEMODEL_H
