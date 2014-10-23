#ifndef ROMEO_CONTROLLER_NEWDATASETCONTROLLER_H
#define ROMEO_CONTROLLER_NEWDATASETCONTROLLER_H

#include "controller/acontroller.h"
#include "view/window/newdatasetview.h"
#include "model/qtModel/datasetprotocoltablemodel.h"
#include "model/qtModel/datasetgrouptablemodel.h"
#include <QSortFilterProxyModel>
#include "model/util/dao/groupdao.h"
#include "view/dialog/dialog.h"
#include "model/util/dao/datasetdao.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::AController;
using Romeo::View::Window::NewDatasetView;

/*!
 *\file newdatasetcontroller.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-21
*/
/*
*Changes:
*+----------+------------+---------------- +--------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                  Changes                   +       Description         |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|                                                                                                                 |
*|   0.0.1  | 2013-02-21 |   Adami Alberto |  Romeo::Controleller::NewDatasetController |   First version of class  |
*|                                                                                                                 |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Controller {

    /*!
     * \brief The NewDatasetController class, extends AController, represents the controller for the user inputs of the new dataset view.
     */
        class NewDatasetController : public AController
        {
            Q_OBJECT
        private:
            /*!
             * \brief edit flag true if it is a edit dataset, false if it is a new dataset
             */
            bool edit;
            /*!
             * \brief idEdit is the id of the dataset to edit
             */
            QString idEdit;
            /*!
             * \brief group is the group selected
             */
            QString group;
            /*!
             * \brief protocol is the protocol selected
             */
            QString protocol;

            /*!
             * \brief featuresInfo method set the features informations text
             * \param features is a vector of feature pointers
             * \param txt is the string where the informations are added.
             */
            void featuresInfo(QVector<AFeature*> features, QString &txt) const;
            /*!
             * \brief algorithmInfo method set the algorithm informations text
             * \param algorithm is an algorithm pointer
             * \param txt is the string where the informations are added.
             */
            void algorithmInfo(AAlgorithm* algorithm, QString &txt) const;

        protected:
            /*!
             * \brief createConnections method create the connections between view and controller
             */
            void createConnections() const;

        public:
            /*!
             * \brief NewDatasetController constructor create the controller object
             * \param view is the view connected
             * \param parent is the parent of controller object
             */
            NewDatasetController(NewDatasetView *view, QObject *parent=0);
            /*!
             * \brief NewDatasetController constructor create the controller object for edit
             * \param view is the view connected
             * \param dataset is the name of the dataset to edit
             * \param parent is the parent of controller object
             */
            NewDatasetController(NewDatasetView *view, const QString &dataset, QObject *parent=0);
            /*!
             * \brief setEditFields method set the fields for edit dataset
             * \param datasetE is the name of the dataset to edit
             */
            void setEditFields(const QString &datasetE);

        public slots:
            /*!
             * \brief slotGroupSelected slot recieve the signal when the user select the group
             * \param index
             */
            void slotGroupSelected(const QModelIndex &index);
            /*!
             * \brief slotProtocolSelected slot recieve the signal when the user select the protocol
             * \param index
             */
            void slotProtocolSelected(const QModelIndex &index);
            /*!
             * \brief slotSaveDataset slot recieve the signal when the user click on save button
             */
            void slotSaveDataset();

            /*!
             * \brief slotBack slot recieve the signal when the user click on back button.
             * Go to welcome vie if it is a new dataset.
             * Go to datasets view if it is an edit dataset.
             */
            virtual void slotBack();
        };

    } // namespace Controller
} // namespace Romeo

#endif // ROMEO_CONTROLLER_NEWDATASETCONTROLLER_H
