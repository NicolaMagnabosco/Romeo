#ifndef ROMEO_CONTROLLER_NEWGROUPCONTROLLER_H
#define ROMEO_CONTROLLER_NEWGROUPCONTROLLER_H

#include <QObject>
#include <QListView>
#include "view/window/newgroupview.h"
#include "controller/acontroller.h"
#include "model/qtModel/newgrouptablemodel.h"
#include "utils.h"
#include "view/dialog/dialog.h"
#include "model/util/dao/groupdao.h"
#include "model/util/dao/subjectdao.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::AController;
using Romeo::View::Window::NewGroupView;

/*!
 *\file newgroupcontroller.h
 *\author Nicolò Bissacco (nickbissa@gmail.com)
 *\date 2013-02-21
*/
/*
*Changes:
*+----------+------------+-------------------+--------------------------------------------+---------------------------+
*|  Version +    Date    +     Programmer    +                  Changes                   +       Description         |
*+----------+------------+-------------------+--------------------------------------------+---------------------------+
*|                                                                                                                    |
*|   0.0.1  | 2013-02-21 |   Nicolò Bissacco |  Romeo::Controller::NewGroupController     |   First version of class  |
*|                                                                                                                    |
*|   1.0.0  | 2013-03-10 |   Nicolò Bissacco |  Romeo::Controller::NewGroupController::   |   Final version of class  |
*+----------+------------+-------------------+--------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Controller {
        /*!
         * \brief The NewGroupController class represent the controller for a NewGroupView's object.
         */
        class NewGroupController : public AController
        {
            Q_OBJECT
        private:
            /*!
             * \brief edit represents the state of used.
             * It's true if the user is editing a Group, otherwhise is false if the user is creating a new Group.
             */
            bool edit;

            /*!
             * \brief idEdit represent the id of the Group that the user is editing.
             */
            QString idEdit;

            /*!
             * \brief create_Update method save or update the group on the database
             * \param group is the group to save or update
             * \param name is the name of the group
             */
            void create_Update(GroupOfSubject *group, QString &name);

        protected:
             /*!
             * \brief Creates all the connection for the Controller.
             */
            virtual void createConnections() const;

        public:
            /*!
             * \brief Constructs a NewGroupView's object with the given view and parent.
             * \param view represent the NewGroup's object that the controller manage.
             * \param parent represent the parent of the controller.
             */
            NewGroupController(NewGroupView * view, QObject * parent = 0);

            /*!
             * \brief Constructs a NewGroupView's object with the given view, group and parent.
             * This constructor is used when the the view wanted to be used for change a protocol.
             * \param view represent the NewProtocol's object that the controller manage.
             * \param protocol represent the name of the group that the user want to edit.
             * \param parent represent the parent of the controller.
             */
            NewGroupController(NewGroupView * view, const QString & group, QObject * parent = 0);

        public slots:
            /*!
             * \brief Slot that select all the subject in the view's table.
             */
            void slotSelectAll();

            /*!
             * \brief Slot that deselct all the subject in the view's table.
             */
            void slotDeselectAll();

            /*!
             * \brief Slot htat show int the view all the subject of the type selceted by the user in the view.
             * \param selcetion represent the type of subjects selcted by the user (2d, 2d-t, 3d, 3d-t).
             */
            void slotTypeSelection(const QString & selection);

            /*!
             * \brief Slot that save the Gruup of Subject in the Romeo's system.
             * If the dates are incomplete or incorrect show an error to the user.
             */
            void slotSaveGroup();

            /*!
             * \brief Slot that load the dates of the selected group by the user in the associate view.
             * \param groupS rerpresents the name of the group to be show in the associate view.
             */
            void setEditFields(const QString & groupS);

            /*!
             * \brief Slot that returns to the previous view visulizated by the user.
            */
            virtual void slotBack();
        };

    } // namespace Controller

} // namespace Romeo

#endif // ROMEO_CONTROLLER_NEWGROUPCONTROLLER_H
