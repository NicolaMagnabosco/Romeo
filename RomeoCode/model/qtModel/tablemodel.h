#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
/*!
 *\file tablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-22
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-22 | Martignago Jimmy|           Romeo::Model::TableModel         |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
            /*!
             * \brief The class TableModel, extends QAbstractTableModel, represents the qt model for the tables of the view.
             */
            class TableModel : public QAbstractTableModel
            {
                Q_OBJECT
            protected:
                /*!
                 * \brief Constructor of the TableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                TableModel(QObject *parent = 0);

            public:
                /*!
                 * \brief Returns the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
                 */
                int rowCount(const QModelIndex &parent = QModelIndex()) const =0;
                /*!
                 * \brief Returns the number of columns for the children of the given parent.
                 */
                int columnCount(const QModelIndex &parent = QModelIndex()) const =0;
                /*!
                 * \brief Returns the data stored under the given role for the item referred to by the index.
                 */
                QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const =0;
                /*!
                 * \brief Returns the data for the given role and section in the header with the specified orientation.
                 */
                QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const =0;

            };
        }
    }
}

#endif // TABLEMODEL_H
