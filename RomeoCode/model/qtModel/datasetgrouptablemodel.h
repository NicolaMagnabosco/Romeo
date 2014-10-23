#ifndef DATASETGROUPTABLEMODEL_H
#define DATASETGROUPTABLEMODEL_H

#include <QAbstractTableModel>
#include "model/core/groupofsubject.h"
#include <QVector>
#include "model/util/dao/groupdao.h"
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::GroupOfSubject;
/*!
 *\file datasetgroupstablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-24
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-24 | Martignago Jimmy|   Romeo::Model::DatasetGroupTableModel     |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class DatasetGroupTableModel, extends TableModel, represents the model for the table of groups on the new dataset view.
         */
            class DatasetGroupTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the vector with the groups of the model.
                 */
                QVector<GroupOfSubject*> groups;
                /*!
                 * \brief This method load the data of the model.
                 */
                void loadModelData();

            public:
                /*!
                 * \brief Constructor of the DatasetGroupTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                DatasetGroupTableModel(QObject *parent = 0);
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
                 * \brief The method reset the model.
                 */
                void resetDatasetModel();

            };
        }
    }
}

#endif // DATASETGROUPTABLEMODEL_H
