#ifndef ROMEO_CONTROLLER_NEWPROTOCOLCONTROLLER_H
#define ROMEO_CONTROLLER_NEWPROTOCOLCONTROLLER_H

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/newprotocolview.h"
#include "model/core/featcreator.h"
#include "utils.h"
#include "view/dialog/featureparams.h"
#include "model/core/feature/afeature.h"
#include "view/dialog/dialog.h"
#include "model/core/protocol.h"
#include "model/util/dao/protocoldao.h"
#include "controller/mainwindowcontroller.h"
#include "model/core/algcreator.h"
#include "model/core/algorithm/aalgorithm.h"

using Romeo::Controller::AController;
using Romeo::View::Window::NewProtocolView;
using Romeo::View::Dialog::FeatureParams;

/*!
 *\file newprotocolcontroller.h
 *\author Nicolò Bissacco (alberto.adami.7@gmail.com)
 *\date 2013-02-21
*/

/*
*Changes:
*+----------+------------+---------------- +--------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                  Changes                   +       Description         |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|                                                                                                                 |
*|   0.0.1  | 2013-02-21 |   Nicolò Bissaccò Alberto |  Romeo::Controleller::NewProtocolController|   First version of class  |
*|                                                                                                                 |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Controller {
        /*!
         * \brief The NewSubjectController class represent the controller for a NewSubjectView's object.
         */
        class NewProtocolController : public AController
        {
            Q_OBJECT
        private:
            /*!
             * \brief edit represents the state of used.
             * It's true if the user is editing a Protocol, otherwhise is false if the user is creating a new Protocol.
             */
            bool edit;
            /*!
             * \brief idEdit represents the id of the Protocol that the user is edit
             */
            QString idEdit;
            /*!
             * \brief dialogFeture represent a pointer to the dialog for add a feature.
             */
            FeatureParams *dialogFeature;
            /*!
             * \brief featuresToRemove contains the id's of the features that the user want to remove from the protrocol.
            */
            QVector<int> featuresToRemove;
            /*!
             * \brief create_Update method save or update the protocol on the database
             * \param protocol is the protocol to save or update
             * \param name is the name of the protocol
             */
            void create_Update(Protocol *protocol, QString &name);

        protected:
            /*!
             * \brief Creates all the connection for the Controller.
             */
            void createConnections() const;
        public:
            /*!
             * \brief Constructs a NewProtocolController's object with the given view and parent.
             * \param view represent the NewProtocol's object that the controller manage.
             * \param parent represent the parent of the controller.
             */
            NewProtocolController(NewProtocolView *view, QObject *parent=0);
            /*!
             * \brief Constructs a NewProtocolController's object with the given view, protocol and parent.
             * This constructor is used when the the view wanted to be used for change a protocol.
             * \param view represent the NewProtocol's object that the controller manage.
             * \param protocol represent hte name of the protocol that the user want to change.
             * \param parent represent the parent of the controller.
             */
            NewProtocolController(NewProtocolView *view, const QString &protocol, QObject *parent=0);
            
            /*!
             * \brief setEditFields method prepare the field for edit with the given protocol
             * \param protocolS is the protocol used to set fields
             */
            void setEditFields(const QString &protocolS);

        public slots:
            /*!
             * \brief 
             */
            void slotAddFeatureClicked();

            /*!
             * \brief slotFeatureSelected slot recieve the signal when the user select the feature on the dialog of features selection
             * \param feature is the name of feature selected
             */
            void slotFeatureSelected(const QString &feature);
            /*!
             * \brief Slot that add the feature add by the user to the Protocol's feature.
             * \param pramsS represent the prameters of the feature add by the feature in the protocol.
             */
            void slotOk(const QStringList &paramsS);
            /*!
             * \brief Slot that change the type of the Protocol that the user is going to create.
             *  The slot update the associate view with the appropiated informations.
             * \param selection represent the type of the Protocol selected by the user in the view. (2d, 2d-t, 3d, 3d-t)
             */
            void slotTypeChanged(const QString &selection);
            /*!
             * \brief Slot that have the goal to save the Protocol in the Reomeo's system.
             */
            void slotSaveProtocol();
            /*!
             * \brief Slot that remove the selected feature by the user in the view from the Protocol.
             */
            void slotFeatureRemove();
            /*!
             * \brief slotFeatureSelect slot recieve the signal when the user select a feature on the features table
             * \param index is the selected index of the table
             */
            void slotFeatureSelect(const QModelIndex &index);
            /*!
             * \brief slotAlgorithmSelect slot recieve the signal when the user select the algorithm
             * \param selection is the name of the algorithm selected
             */
            void slotAlgorithmSelect(const QString &selection);
            /*!
             * \breif Slot that returns at the previous view visualize from the user.
             */
            virtual void slotBack();
        };

    } // namespace Controller

} // namespace Romeo

#endif // ROMEO_CONTROLLER_NEWPROTOCOLCONTROLLER_H
