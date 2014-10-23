#ifndef ROMEO_CONTROLLER_DATASETSCONTROLLER_H
#define ROMEO_CONTROLLER_DATASETSCONTROLLER_H

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/datasetsview.h"
#include "model/util/dao/datasetdao.h"
#include "model/core/groupofsubject.h"
#include "model/core/feature/afeature.h"
#include "model/core/algorithm/aalgorithm.h"
#include "view/dialog/dialog.h"
#include "model/qtModel/datasetstablemodel.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::AController;
using Romeo::View::Window::DatasetsView;

/*!
 *\file datasetscontroller.h
 *\author Nicolò Bissaccò (nickbissa@gmail.com)
 *\date 2013-02-25
*/
/*
*Changes:
*+----------+--------------+-----------------+------------------------------------------------------------+---------------------------+
*|  Version +    Date      +   Programmer    +                             Changes                        +       Description         |
*+----------+--------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                    |
*|   0.0.1  | 2013-02-25   |  Nicolò Bissacco|             Romeo::Controleller::DatasetsController        |   First version of class  |
*|                                                                                                                                    |
*|   1.0.0  | 2013-03-10   |  Nicolò Bissacco|  Romeo::Controller::DatasetsController                     |Definitive Version of class|                                                                        |
*+----------+--------------+-----------------+------------------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Controller {
        /*!
         * \brief The DatasetsController class represents a controller of an object of type DatasetsView.
         */
        class DatasetsController : public AController
        {
            Q_OBJECT
        private:
            /*!
             * \brief item represents the name of the Dataset selected by the user in the associate view.
             */
            QString item;

            /*!
             * \brief featuresInfo method add the features informations to the string passed
             * \param feats is a vector of features pointer
             * \param txtProtocols is the string where the informations is added.
             */
            void featuresInfo(QVector<AFeature*> feats, QString &txtProtocols) const;
            /*!
             * \brief algorithmInfo method add the algorithm informations to the string passed
             * \param alg is the algprithm pointer
             * \param txtProtocols is the string where the informations is added.
             */
            void algorithmInfo(AAlgorithm* alg, QString &txtProtocols) const;

        protected:
            /*!
             * \brief createConnections create all the connection of the controller.
             */
            virtual void createConnections() const;

        public:
            /*!
             * \brief DatasetsController contructs a controller of a DatasetsView with the given view and parent.
             * \param view represents the DatasetsView which will be controlled by the DatasetsController object.
             * \param parent represents the parent of the DatasetsController object.
             */
            DatasetsController(DatasetsView * view, QObject * parent = 0);

        public slots:
            /*!
             * \brief slotItemSelected show the details of the selected Dataset in the view.
             * \param index represent the index of the item associate to the Dataset selected by the user.
             */
            void slotItemSelected(const QModelIndex & index);

            /*!
             * \brief slotDeleteDataset deletes the selected Dataset from the database.
             */
            void slotDeleteDataset();

            
        };

    } // namespace Controller
} // namespace Romeo

#endif // ROMEO_CONTROLLER_DATASETSCONTROLLER_H
