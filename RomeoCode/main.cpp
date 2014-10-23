
#include <QApplication>
#include "view/window/mainwindow.h"
#include "controller/mainwindowcontroller.h"
#include "model/util/log/log.h"

using Romeo::Model::Util::Log::Log;
using Romeo::View::Window::MainWindow;
using Romeo::Controller::MainWindowController;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    //enable or disable log
    Log::setEnable(false);
    //create the mainWindow object
    MainWindow *mainWindow=MainWindow::getMainWindow();
    MainWindowController *mainWindowController = MainWindowController::getMainWindowController();
    mainWindowController->slotWelcome();
    mainWindow->show();
    return a.exec();
}
