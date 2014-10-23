#include "welcomecontroller.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::WelcomeController;
using Romeo::Controller::MainWindowController;

WelcomeController::WelcomeController(WelcomeView *view, QObject *parent): AController(view,parent)
{

    setObjectName("WelcomeController");
    createConnections();
}

void WelcomeController::createConnections() const
{

    //cast the view to a WelcomeView* pointer
    WelcomeView *welcomeView=qobject_cast<WelcomeView*>(view);

    connect(welcomeView, SIGNAL(createNewSubject()), MainWindowController::getMainWindowController(), SLOT(slotNewSubject()));
    connect(welcomeView, SIGNAL(showSubjects()), MainWindowController::getMainWindowController(), SLOT(slotShowSubjects()));
    connect(welcomeView, SIGNAL(createNewGroup()), MainWindowController::getMainWindowController(), SLOT(slotNewGroup()));
    connect(welcomeView, SIGNAL(showGroups()), MainWindowController::getMainWindowController(), SLOT(slotShowGroups()));
    connect(welcomeView, SIGNAL(createNewProtocol()), MainWindowController::getMainWindowController(), SLOT(slotNewProtocol()));
    connect(welcomeView, SIGNAL(showProtocols()), MainWindowController::getMainWindowController(), SLOT(slotShowProtocols()));
    connect(welcomeView, SIGNAL(createNewDataset()), MainWindowController::getMainWindowController(), SLOT(slotNewDataset()));
    connect(welcomeView, SIGNAL(showDatasets()), MainWindowController::getMainWindowController(), SLOT(slotShowDatasets()));
    connect(welcomeView, SIGNAL(startAnalysis()), MainWindowController::getMainWindowController(), SLOT(slotStartAnalysis()));
    connect(welcomeView, SIGNAL(showResults()), MainWindowController::getMainWindowController(), SLOT(slotAnalysisResults()));

    connect(welcomeView, SIGNAL(userGuide()), MainWindowController::getMainWindowController(), SLOT(slotHelp()));
    connect(welcomeView, SIGNAL(videoGuide()), MainWindowController::getMainWindowController(), SLOT(slotHelpVideo()));
    connect(welcomeView, SIGNAL(shortcutsList()), MainWindowController::getMainWindowController(), SLOT(slotShortCuts()));
    connect(welcomeView, SIGNAL(aboutus()), MainWindowController::getMainWindowController(), SLOT(slotAboutRomeo()));
    connect(welcomeView, SIGNAL(exitSignal()), MainWindowController::getMainWindowController(), SLOT(slotCloseRomeo()));
}
