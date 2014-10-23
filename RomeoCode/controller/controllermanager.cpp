#include "controllermanager.h"

using Romeo::Controller::ControllerManager;

//construct an empty activeController
ControllerManager::ControllerManager(QObject *parent):QObject(parent), activeController(0)
{

}

//get the instance of class
ControllerManager * ControllerManager::getControllerManager()
{

    //create the instance if doesn't exists already
    if(!ControllerManager::controllerManager)
        ControllerManager::controllerManager=new ControllerManager();
    //return the unique instance
    return ControllerManager::controllerManager;
}

void ControllerManager::addController(const AController& controller)
{

    if(activeController)
        //deallocate the old activeController
        delete activeController;

    //cast the AController reference
    AController *cController = const_cast<AController*>(&controller);
    activeController = cController;
}

//destructor
ControllerManager::~ControllerManager()
{
    //deallocate the activeController object
    delete activeController;
}

//initialize the static instance member
ControllerManager* ControllerManager::controllerManager=0;
