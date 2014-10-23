#ifndef DATASETSTABLEMODEL_H
#define DATASETSTABLEMODEL_H

#include "model/qtModel/tablemodel.h"
#include "model/core/dataset.h"
#include "model/util/dao/datasetdao.h"
#include "utils.h"

using Romeo::Model::Core::Dataset;
/*!
 *\file datasetsstablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-23
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-23 | Martignago Jimmy|     Romeo::Model::DatasetsTableModel       |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class DatasetsTableModel, extends TableModel, represents the model for the table of datsets on the datasets view.
         */
            class DatasetsTableModel : public TableModel
            {
                Q_OBJECT

            private:
                /*!
                 * \brief Is the vector with the datasets of the model.
                 */
                QVector<Dataset*> datasets;
                /*!
                 * \brief This method load the data of the model.
                 */
                void loadModelData();

            public:
                /*!
                 * \brief Constructor of the DatasetsTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                DatasetsTableModel(QObject *parent = 0);

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
                 * \brief The method reload the model.
                 */
                void refreshModelData();

            };
        }
    }
}

#endif // DATASETSTABLEMODEL_H
