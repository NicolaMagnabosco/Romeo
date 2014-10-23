#ifndef DATASETPROTOCOLTABLEMODEL_H
#define DATASETPROTOCOLTABLEMODEL_H

#include <QAbstractTableModel>
#include "model/core/protocol.h"
#include <QVector>
#include "model/util/dao/protocoldao.h"
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::Protocol;
/*!
 *\file datasetprotocolstablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-24
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-24 | Martignago Jimmy|  Romeo::Model::DatasetprotocolTableModel   |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class DatasetProtocolTableModel, extends TableModel, represents the model for the table of protocols on the new dataset view.
         */
            class DatasetProtocolTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the vector with the protocols of the model.
                 */
                QVector<Protocol*> protocols;

            public:
                /*!
                 * \brief Constructor of the DatasetProtocolTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                DatasetProtocolTableModel(QObject *parent = 0);
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
                 * \brief The method load the data of the model based on type.
                 * \param type is the type of the protocols.
                 */
                void loadModelData(const QString& type);

                /*!
                 * \brief The method reset the model.
                 */
                void resetDatasetModel();

            };
        }
    }
}

#endif // DATASETPROTOCOLTABLEMODEL_H
