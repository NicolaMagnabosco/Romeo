#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include "controller/acontroller.h"

using Romeo::Controller::AController;

/*!
 *\file controllermanager.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-13
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-13 |   Adami Alberto |  Romeo::Controleller::ControllerManager                    |   First version of class  |
*|                                                                                                                                  |
*|   0.0.2    2013-02-17 |   Adami Alberto |  Romeo::Controller::ControllerManager::removeController()  | Add slot for remove       |                            |                                                                               |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Controller {
        /*!
         * \brief The ControllerManager class have the goal to manage all the AController's objects in the system.
         * The class deletes the controllers when they are not more necessary and adds the controllers when they were
         * been created.
         */
        class ControllerManager: public QObject
        {
            Q_OBJECT
        private:
            //constructor
            /*!
             * \brief Construct a ControllerManager with the given parent.
             * \param parent represent the parent of the ControllerManager object.
             */
            ControllerManager(QObject * parent = 0);

            //members
            /*!
             * \brief Represent a pointer to the unique instance of ControllerManger
             */
            static ControllerManager * controllerManager;
            /*!
             * \brief Represent the pointer to the AController's object active.
             */
            AController * activeController;

        public:
            /*!
             * \brief Return the unique instance of the ContollerManager's class.
             * If it doesn't exist, it'll be created.
             * \return ControllerManager* that rappresented the unique instance.
             */
            static ControllerManager * getControllerManager();

            /*!
             * \brief Add the controller object at the list of controller controlled.
             * \param controller rappresent the controller to  add at the list of active controller.
            */
            void addController(const AController & controller);

            /*!
             * \brief Destroy all the Acontroller controllated from the ControllerManager's object.
             * All signals to and from the Acontroller's objects are automatically disconnected, and any pending posted events
             * for the object are removed from the event queue.
            */
            ~ControllerManager();
        };
    }
}
#endif // CONTROLLERMANAGER_H
