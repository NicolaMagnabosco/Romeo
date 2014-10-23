#ifndef GROUPTABLEMODEL_H
#define GROUPTABLEMODEL_H

#include <QAbstractTableModel>
#include "utils.h"
#include <QVector>
#include "model/core/groupofsubject.h"
#include "model/util/dao/groupdao.h"
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::GroupOfSubject;
/*!
 *\file grouptablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-23
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-23 | Martignago Jimmy|       Romeo::Model::GroupTableModel        |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class GroupTableModel, extends TableModel, represents the model for the table of groups on the groups view.
         */
            class GroupTableModel : public TableModel
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
                 * \brief Constructor of the GroupTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                GroupTableModel(QObject *parent = 0);
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
                 * \brief The method reload the data of the model.
                 */
                void refreshModelData();

            };
        }
    }
}

#endif // GROUPTABLEMODEL_H
