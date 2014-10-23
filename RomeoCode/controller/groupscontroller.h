#ifndef ROMEO_CONTROLLER_GROUPSCONTROLLER_H
#define ROMEO_CONTROLLER_GROUPSCONTROLLER_H

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/groupview.h"
#include "model/util/dao/groupdao.h"
#include "model/qtModel/groupsubjectstablemodel.h"
#include "model/qtModel/grouptablemodel.h"
#include <QSortFilterProxyModel>
#include "view/dialog/dialog.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::AController;
using Romeo::View::Window::GroupView;

/*!
*\file groupscontroller.h
*\author Adami Alberto (albertoa.adami.7@gmail.com)
*\date 2013-02-25
*\brief The APanel class is the base class of the Romeos'view.
*/
/*
*Changes:
*+----------+------------+---------------- +--------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +         Changes                +       Description         |
*+----------+------------+-----------------+--------------------------------+---------------------------+
*|                                                                                                      |
*|   0.0.1  | 2013-02-13 |   Adami Alberto |  Romeo::View::Window::Apanel   | First version of class    |
*|                                                                                                      |
*+----------+------------+-----------------+--------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Controller {
        /*!
         * \brief The GroupsController class represents a controller of an object of type GroupsView.
         */
        class GroupsController : public AController
        {
            Q_OBJECT
        private:
            /*!
             * \brief item represents the name of the Group selected by the user in the associate view.
             */
            QString item;

        protected:
             /*!
             * \brief createConnections create all the connection of the controller.
             */
            virtual void createConnections() const;

        public:
             /*!
             * \brief GroupsController contructs a controller of a GroupsView with the given view and parent.
             * \param view represents the GroupsView which will be controlled by the GroupsController object.
             * \param parent represents the parent of the GroupsController object.
             */
            GroupsController(GroupView * view, QObject * parent = 0);

        public slots:
            /*!
             * \brief slotItemSelected show the details of the selected Group in the view.
             * \param index represent the index of the item associate to the Group selected by the user.
             */
            void slotItemSelected(const QModelIndex & index);

            /*!
             * \brief slotDeleteGroup deletes the selected group of Subject from the database.
             */
            void slotDeleteGroup();

            /*!
             * \brief slotEditGroup allows the user to edit the selected Group.
             * The slot redirects the user to an other view. The user could add or remove Subjects from the Group.
            */
            void slotEditGroup();
        };
    } // namespace Controller
} // namespace Romeo

#endif // ROMEO_CONTROLLER_GROUPSCONTROLLER_H
