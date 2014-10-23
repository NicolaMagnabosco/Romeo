



#ifndef ACONTROLLER_H
#define ACONTROLLER_H

#include <QObject>
#include "view/window/apanel.h"
#include "view/window/mainwindow.h"
#include "view/window/welcomeview.h"

using Romeo::View::Window::WelcomeView;
using Romeo::View::Window::MainWindow;
using Romeo::View::Window::APanel;

/*!
 *\file acontroller.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-15
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description         |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|                                                                                                           |
*|   0.0.1  | 2013-02-15 |   Adami Alberto |  Romeo::Controleller::Acontroller   |   First version of class  |
*|                                                                                                           |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Controller {
         /*!
         * \brief The AController class represent a generic controller for the Romeo application.
         * It have the goal to manage a generic object of type APanel *.
         */
        class AController : public QObject
        {
            Q_OBJECT
        protected:
            /*!
             * \brief view represent the APanel's object that the AController's object manage.
             */
            APanel * view;

            /*!
             * \brief Constructs an AController's object with the given view and parent
             * \param view represent the APanel's object that the AController manage.
             * \param parent represent the QObject parent of the controller.
             */
             AController(APanel * view, QObject * parent = 0);

            /*!
             * \brief Create all the connection of the controller.
             * This is an abstract Method.
             */
            virtual void createConnections() const = 0;

        public:
            /*!
             * \brief Delete the AController and the associate view.
             */
            virtual ~AController();

        public slots:
            /*!
             * \brief slotBack manages the user's request to visualize the previous view.
             */
            virtual void slotBack();
        };
    }
}

#endif // ACONTROLLER_H
