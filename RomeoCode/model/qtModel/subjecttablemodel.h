#ifndef SUBJECTTABLEMODEL_H
#define SUBJECTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "model/core/asubject.h"
#include "utils.h"
#include "model/util/dao/subjectdao.h"
#include "model/qtModel/tablemodel.h"

using Romeo::Model::Core::ASubject;
/*!
 *\file subjecttablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-22
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-22 | Martignago Jimmy|      Romeo::Model::SubjectTableModel       |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
            /*!
             * \brief The class SubjectTableModel, extends TableModel, represents the model for the table of subjects on the subjects view.
             */
            class SubjectTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the vector with the subjects of the model.
                 */
                QVector<ASubject*> subjects;

                /*!
                 * \brief This method load the data of the model.
                 */
                void loadModelData();

            public:
                /*!
                 * \brief Constructor of the SubjectTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                SubjectTableModel(QObject *parent = 0);
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
                 * \brief Delete the subjects on the class.
                 */
                ~SubjectTableModel();

            signals:

            public slots:

            };
        }
    }
}

#endif // SUBJECTTABLEMODEL_H
