#ifndef GROUPSUBJECTSTABLEMODEL_H
#define GROUPSUBJECTSTABLEMODEL_H

#include <QAbstractListModel>
#include "model/core/asubject.h"
#include "utils.h"
#include <QVector>
#include <QImage>
#include <QDir>
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::ASubject;
/*!
 *\file groupsubjectstablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-23
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-23 | Martignago Jimmy|   Romeo::Model::GroupSubjectsTableModel    |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class GroupSubjectsTableModel, extends TableModel, represents the model for the table of subjects on the groups view.
         */
            class GroupSubjectsTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the vector with the subjects of the model.
                 */
                QVector<ASubject*> subjects;

            public:
                /*!
                 * \brief Constructor of the GroupSubjectsTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                GroupSubjectsTableModel(QObject *parent = 0);
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
                void resetListModel();
                /*!
                 * \brief The method reset the model and reload the model with the subjects passed.
                 * \param subjectsV are a vector of subjects to add to the model.
                 */
                void resetListModel(QVector<ASubject*> subjectsV);

            };
        }
    }
}

#endif // GROUPSUBJECTSTABLEMODEL_H
