
#ifndef WELCOMECONTROLLER_H
#define WELCOMECONTROLLER_H

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/welcomeview.h"

using Romeo::View::Window::WelcomeView;

/*!
 *\file welcomecontroller.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-15
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                 Changes                   +         Description       |
*+----------+------------+-----------------+-------------------------------------------+---------------------------+
*|                                                                                                                 |
*|   0.0.1  | 2013-02-15 |   Adami Alberto |  Romeo::Controller::WelcomeController     |   First version of class  |
*|                                                                                                                 |
*|   0.0.2  | 2013-10-28 |   Adami Alberto |  Romeo::Controller::WelcomeController     | Complete the documentation|
*|                                                                                                                 |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Controller {     
        /*!
         * \brief The WelcomeController class represents the controller for a WelcomeView object.
         */
        class WelcomeController : public AController
        {
            Q_OBJECT
        protected:
            /*!
             * \brief createConnections creates all the connection for the Controller.
             */
            virtual void createConnections() const;

        public:
            /*!
             * \brief WelcomeController construct an WelcomeController object with the given view and parent.
             * \param view represent the view that the WelcomeController have to manage.
             * \param parent represent the parent of the WelcomeController.
             */
            WelcomeController(WelcomeView * view, QObject * parent = 0);
        };
    }//namespace Controller
}//namespace Romeo

#endif // WELCOMECONTROLLER_H
