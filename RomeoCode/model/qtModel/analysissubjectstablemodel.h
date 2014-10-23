#ifndef ANALYSISSUBJECTSTABLEMODEL_H
#define ANALYSISSUBJECTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "model/core/asubject.h"
#include "utils.h"
#include "model/util/dao/datasetdao.h"
#include "model/qtModel/tablemodel.h"
/*!
 *\file analysissubjectstablemodel.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-24
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                       +       Description             |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*|                                                                                                                      |
*|   0.0.1  | 2013-03-24 | Martignago Jimmy|  Romeo::Model::AnalysisSubjectTableModel   |    First version of class     |
*|                                                                                                                      |
*+----------+------------+-----------------+--------------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace QtModel {
        /*!
         * \brief The class AnalysisSubjectsTableModel, extends TableModel, represents the model for the table of subjects on the analysis view.
         */
            class AnalysisSubjectsTableModel : public TableModel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Is the vector with the subjects of the model.
                 */
                QVector<ASubject*> subjects;

            public:
                /*!
                 * \brief Constructor of the AnalysisSubjectsTableModel class with the given parent.
                 * \param parent is the parent of the class object.
                 */
                AnalysisSubjectsTableModel(QObject *parent = 0);
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
                 * \brief The method load the data on the model with the subjects of the dataset.
                 * \param dataset is the dataset to load.
                 */
                void loadModelData(const QString& dataset);
                /*!
                 * \brief The method reset the model.
                 */
                void resetModelData();
            };
        }
    }
}

#endif // ANALYSISSUBJECTSTABLEMODEL_H
