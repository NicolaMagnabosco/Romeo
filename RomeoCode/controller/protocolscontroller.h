#ifndef ROMEO_CONTROLLER_PROTOCOLSCONTROLLER_H
#define ROMEO_CONTROLLER_PROTOCOLSCONTROLLER_H

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/protocolsview.h"
#include "model/util/dao/featuredao.h"
#include "model/util/dao/algorithmdao.h"
#include "model/util/dao/protocoldao.h"
#include "model/core/algorithm/aalgorithm.h"
#include "model/core/feature/afeature.h"
#include "utils.h"
#include "view/dialog/dialog.h"
#include "model/qtModel/protocoltablemodel.h"
#include <QSortFilterProxyModel>
#include <controller/mainwindowcontroller.h>

using Romeo::Controller::AController;
using Romeo::View::Window::ProtocolsView;
using Romeo::Model::Core::Algorithm::AAlgorithm;

/*!
 *\file protocolscontroller.h
 *\author Nicolò Bissacco (alberto.adami.7@gmail.com)
 *\date 2013-02-26
*/
/*
*Changes:
*+----------+------------+--------------------+------------------------------------------------------------+------------------------------+
*|  Version +    Date    +    Programmer      +                             Changes                        +         Description          |
*+----------+------------+--------------------+------------------------------------------------------------+------------------------------+
*|                                                                                                                                        |
*|   0.0.1  | 2013-02-26 |   Nicolò Bissacco  |         Romeo::Controleller::ProtocolsController           |   First version of class     |
*|                                                                                                                                        |                                                                               
*|   0.0.2  | 2013-03-10 |   Nicolò Bissacco  |   Romeo::Controller::ProtocolsController::slotEditProtocol | Add slot for edit a protocol |
*|                                                                                                                                        |
*+----------+------------+--------------------+------------------------------------------------------------+------------------------------+
*/

namespace Romeo {
    namespace Controller {
        /*!
         * \brief The ProtocolsController class represent the controller for a ProtocolsView's object. 
         */
        class ProtocolsController : public AController
        {
            Q_OBJECT
        private:
            /*!
            * \brief item represents the name of the Protocol selected by the user in the associate view.
            */
            QString item;

            /*!
             * \brief featuresInfo method load the features informations
             * \param features is a vector of features pointer
             */
            void featuresInfo(QVector<AFeature*> features) const;
            /*!
             * \brief algorithmInfo method load the algorithm informations
             * \param algorithm is an algorithm pointer
             */
            void algorithmInfo(AAlgorithm* algorithm) const;

        protected:
            /*!
             * \brief createConnections creates all the connection for the Controller.
             */
            virtual void createConnections() const;

        public:
            /*!
             * \brief ProtocolsController constructs a ProtocolsController's object with the given view and parent.
             * \param view represent the view that the ProtocolsController have to manage.
             * \param parent represent the parent of the ProtocolsController.
             */
            ProtocolsController(ProtocolsView * view, QObject * parent = 0);

        public slots:
            /*!
             * \brief slotItemSelected show the details of the selected Protocol in the view.
             * \param index represent the index of the item associate to the Protocol selected by the user in the associate view.
             */
            void slotProtocolSelected(const QModelIndex & index);

            /*!
             * \brief slotDeleteProtocol deletes the selected Protocol from the system.
             */
            void slotDeleteProtocol();

            /*!
             * \breif slotEditProtocol allow to the user to modify the selected Protocol.
             * The slot redirect the user in the view for edit the Protocol.
             * There the user can add/remove features and add/remove the algorithms of the Protocol.
             */
            void slotEditProtocol();
        };
    } // namespace Controller
} // namespace Romeo

#endif // ROMEO_CONTROLLER_PROTOCOLSCONTROLLER_H
