#include "acontroller.h"
#include "controller/controllermanager.h"
#include "controller/welcomecontroller.h"
#include "controller/mainwindowcontroller.h"
#include "view/window/mainwindow.h"

using Romeo::Controller::WelcomeController;
using Romeo::Controller::ControllerManager;
using Romeo::Controller::AController;
using Romeo::Controller::MainWindowController;
using Romeo::View::Window::MainWindow;

AController::AController(APanel *parentView, QObject *parent) : QObject(parent), view(parentView)
{

    setObjectName("AController");

    connect(view, SIGNAL(backView()), this, SLOT(slotBack()));
}

AController::~AController()
{

}

void AController::slotBack()
{
    MainWindowController::getMainWindowController()->slotWelcome();
}
