#include "mainwindowcontroller.h"
#include "view/window/welcomeview.h"
#include "view/window/subjectsview.h"
#include "view/window/resultsview.h"
#include "view/window/protocolsview.h"
#include "view/window/newsubjectview.h"
#include "view/window/newgroupview.h"
#include "view/window/newprotocolview.h"
#include "view/window/newdatasetview.h"
#include "view/window/groupview.h"
#include "view/window/analysisview.h"
#include "view/window/datasetsview.h"
#include "controller/controllermanager.h"
#include "controller/welcomecontroller.h"
#include "controller/subjectscontroller.h"
#include "controller/newsubjectcontroller.h"
#include "controller/groupscontroller.h"
#include "controller/newgroupcontroller.h"
#include "controller/protocolscontroller.h"
#include "controller/newprotocolcontroller.h"
#include "controller/datasetscontroller.h"
#include "controller/newdatasetcontroller.h"
#include "controller/analysiscontroller.h"
#include "controller/resultscontroller.h"
#include "view/dialog/dialog.h"
#include "model/help/assistant.h"
#include "view/window/detailedresult.h"
#include "controller/detailedresultcontroller.h"

using Romeo::Controller::MainWindowController;

using Romeo::View::Window::WelcomeView;
using Romeo::View::Window::SubjectsView;
using Romeo::View::Window::ResultsView;
using Romeo::View::Window::ProtocolsView;
using Romeo::View::Window::NewSubjectView;
using Romeo::View::Window::NewGroupView;
using Romeo::View::Window::NewProtocolView;
using Romeo::View::Window::NewDatasetView;
using Romeo::View::Window::GroupView;
using Romeo::View::Window::AnalysisView;
using Romeo::View::Window::DatasetsView;
using Romeo::View::Window::DetailedResult;
using Romeo::Controller::ControllerManager;
using Romeo::Controller::WelcomeController;
using Romeo::Controller::SubjectsController;
using Romeo::Controller::NewSubjectController;
using Romeo::Controller::GroupsController;
using Romeo::Controller::NewGroupController;
using Romeo::Controller::ProtocolsController;
using Romeo::Controller::NewProtocolController;
using Romeo::Controller::DatasetsController;
using Romeo::Controller::NewDatasetController;
using Romeo::Controller::AnalysisController;
using Romeo::Controller::ResultsController;
using Romeo::Controller::DetailedResultController;
using Romeo::View::Dialog::Dialog;
using Romeo::Model::Util::Log::Log;
using Romeo::Model::Help::Assistant;

MainWindowController::MainWindowController(MainWindow *main, QObject *parent):QObject(parent), mainView(main), firstOpen(true)
{
    createConnections();
}

void MainWindowController::registerToSystem(APanel *view, AController *controller) const
{
    mainView->addCentralWidget(view);
    ControllerManager *manager = ControllerManager::getControllerManager();
    manager->addController(*controller);

    WelcomeView *welcomeView=qobject_cast<WelcomeView*>(view);
    if(welcomeView) 
        mainView->setShortcutHomeEnable(true);
    else 
        mainView->setShortcutHomeEnable(false);
}

void MainWindowController::createConnections() const
{
    //toolbar
    connect(mainView->getToolBar(), SIGNAL(backToHome()), this, SLOT(slotWelcome()));
    connect(mainView->getToolBar(), SIGNAL(createNewSubject()), this, SLOT(slotNewSubject()));
    connect(mainView->getToolBar(), SIGNAL(showSubjects()), this, SLOT(slotShowSubjects()));
    connect(mainView->getToolBar(), SIGNAL(createNewGroup()), this, SLOT(slotNewGroup()));
    connect(mainView->getToolBar(), SIGNAL(showGroups()), this, SLOT(slotShowGroups()));
    connect(mainView->getToolBar(), SIGNAL(createNewProtocol()), this, SLOT(slotNewProtocol()));
    connect(mainView->getToolBar(), SIGNAL(showProtocols()), this, SLOT(slotShowProtocols()));
    connect(mainView->getToolBar(), SIGNAL(createNewDataset()), this, SLOT(slotNewDataset()));
    connect(mainView->getToolBar(), SIGNAL(showDatasets()), this, SLOT(slotShowDatasets()));
    connect(mainView->getToolBar(), SIGNAL(startAnalysis()), this, SLOT(slotStartAnalysis()));
    connect(mainView->getToolBar(), SIGNAL(showResults()), this, SLOT(slotAnalysisResults()));
    connect(mainView->getToolBar(), SIGNAL(menuExit()), this, SLOT(slotCloseRomeo()));
    connect(mainView->getToolBar(), SIGNAL(menuAbout()), this, SLOT(slotAboutRomeo()));
    connect(mainView->getToolBar(), SIGNAL(shortCutsSignal()), this, SLOT(slotShortCuts()));
    connect(mainView->getToolBar(), SIGNAL(helpManualSignal()), this, SLOT(slotHelp()));
    connect(mainView->getToolBar(), SIGNAL(helpVideoGuideSignal()), this, SLOT(slotHelpVideo()));

    //shortcuts
    connect(mainView, SIGNAL(createNewSubjectSC()), this, SLOT(slotNewSubject()));
    connect(mainView, SIGNAL(showSubjectsSC()), this, SLOT(slotShowSubjects()));
    connect(mainView, SIGNAL(createNewGroupSC()), this, SLOT(slotNewGroup()));
    connect(mainView, SIGNAL(showGroupsSC()), this, SLOT(slotShowGroups()));
    connect(mainView, SIGNAL(createNewProtocolSC()), this, SLOT(slotNewProtocol()));
    connect(mainView, SIGNAL(showProtocolsSC()), this, SLOT(slotShowProtocols()));
    connect(mainView, SIGNAL(createNewDatasetSC()), this, SLOT(slotNewDataset()));
    connect(mainView, SIGNAL(showDatasetsSC()), this, SLOT(slotShowDatasets()));
    connect(mainView, SIGNAL(startAnalysisSC()), this, SLOT(slotStartAnalysis()));
    connect(mainView, SIGNAL(showResultsSC()), this, SLOT(slotAnalysisResults()));
    connect(mainView, SIGNAL(exitSC()), this, SLOT(slotCloseRomeo()));
    connect(mainView, SIGNAL(aboutSC()), this, SLOT(slotAboutRomeo()));
    connect(mainView, SIGNAL(helpManualSC()), this, SLOT(slotHelp()));
    connect(mainView, SIGNAL(helpVideoGuideSC()), this, SLOT(slotHelpVideo()));
    connect(mainView, SIGNAL(homeSC()), this, SLOT(slotWelcome()));
    connect(mainView, SIGNAL(shortCutsSC()), this, SLOT(slotShortCuts()));

    connect(mainView, SIGNAL(helpPage()), this, SLOT(slotHelpPage()));
}

MainWindowController * MainWindowController::getMainWindowController()
{
    if(!mainWindowController) {

        MainWindow *mainWindow=MainWindow::getMainWindow();
        mainWindowController=new MainWindowController(mainWindow);
    }
    return mainWindowController;
}

MainWindowController::~MainWindowController()
{
    //delete the mainView
    delete mainView;
}

void MainWindowController::slotWelcome()
{
    WelcomeView *view = new WelcomeView(mainView);
    WelcomeController *controller = new WelcomeController(view);
    registerToSystem(view, controller);

    if(firstOpen) {
        MainWindow::getMainWindow()->writeStatusBar("Welcome to ROMEO", 5000);
        firstOpen = false;
    }
}

void MainWindowController::slotNewSubject()
{
    NewSubjectView *view = new NewSubjectView(mainView);
    NewSubjectController *controller = new NewSubjectController(view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to New Subject");
}

void MainWindowController::slotShowSubjects()
{
    SubjectsView *view = new SubjectsView(mainView);
    SubjectsController *controller = new SubjectsController(view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to Subjects View");
}

void MainWindowController::slotNewGroup()
{
    NewGroupView *view = new NewGroupView(mainView);
    NewGroupController *controller = new NewGroupController(view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to New Group");
}

void MainWindowController::slotEditGroup(const QString & group)
{
    NewGroupView *view = new NewGroupView(mainView);
    NewGroupController *controller = new NewGroupController(view, group);
    controller->setEditFields(group);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to Edit Group "+group);
}

void MainWindowController::slotShowGroups(const QString &from)
{
    GroupView *view = new GroupView(mainView);
    GroupsController *controller = new GroupsController(view);
    registerToSystem(view, controller);

    if(from.isEmpty())
        Log::writeLog(Log::_USER_ACTION_,"Go to Groups View");
    else
        Log::writeLog(Log::_USER_ACTION_,"Go to Groups View from edit Group "+from);
}

void MainWindowController::slotNewProtocol()
{
    NewProtocolView *view = new NewProtocolView(mainView);
    NewProtocolController *controller = new NewProtocolController(view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to New Protocol");
}

void MainWindowController::slotEditProtocol(const QString &protocol)
{
    NewProtocolView *view = new NewProtocolView(mainView);
    NewProtocolController *controller = new NewProtocolController(view, protocol);
    controller->setEditFields(protocol);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to Edit Protocol "+protocol);
}

void MainWindowController::slotShowProtocols(const QString &from)
{
    ProtocolsView *view = new ProtocolsView(mainView);
    ProtocolsController *controller = new ProtocolsController(view);
    registerToSystem(view, controller);

    if(from.isEmpty())
        Log::writeLog(Log::_USER_ACTION_,"Go to Protocols View");
    else
        Log::writeLog(Log::_USER_ACTION_,"Go to Protocols View from edit Protocol "+from);
}

void MainWindowController::slotNewDataset()
{
    NewDatasetView *view = new NewDatasetView(mainView);
    NewDatasetController *controller = new NewDatasetController(view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to New Dataset");
}

void MainWindowController::slotShowDatasets(const QString &from)
{
    DatasetsView *view = new DatasetsView(mainView);
    DatasetsController *controller = new DatasetsController(view);
    registerToSystem(view, controller);

    if(from.isEmpty())
        Log::writeLog(Log::_USER_ACTION_,"Go to Datasets View");
    else
        Log::writeLog(Log::_USER_ACTION_,"Go to Datasets View from edit Dataset "+from);
}

void MainWindowController::slotStartAnalysis()
{
    AnalysisView *view = new AnalysisView(MainWindow::getMainWindow());
    AnalysisController *controller = new AnalysisController(view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to Start Analysis View");
}

void MainWindowController::slotRestartAnalysis(int id)
{
    AnalysisView *view = new AnalysisView(mainView);
    AnalysisController *controller = new AnalysisController(view, id);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to ReStart Analysis "+QString::number(id));
}

void MainWindowController::slotAnalysisResults(int from)
{
    ResultsView *view = new ResultsView(MainWindow::getMainWindow());
    ResultsController *controller = new ResultsController(view);
    registerToSystem(view, controller);

    switch(from) {
        case 1:
            Log::writeLog(Log::_USER_ACTION_,"Go to Analysis Results");
            break;
        case 2:
            Log::writeLog(Log::_USER_ACTION_,"Back to Analysis Results from Restart Analysis");
            break;
        case 3:
            Log::writeLog(Log::_USER_ACTION_,"Back to Analysis Results from Show Detailed Results");
            break;
        default:
            Log::writeLog(Log::_USER_ACTION_,"Go to Analysis Results");
    }

}

void MainWindowController::slotDetailedResults(int id, const QString& title)
{
    DetailedResult *view = new DetailedResult(MainWindow::getMainWindow());
    DetailedResultController *controller = new DetailedResultController(id, title, view);
    registerToSystem(view, controller);

    Log::writeLog(Log::_USER_ACTION_,"Go to Detailed Result View (ID: "+QString::number(id)+")");
}

void MainWindowController::slotAboutRomeo()
{
    QString txt;
    txt = "ROMEO v1.0";
    txt += "\n\nA clustering analysis tool.";
    txt += "\npublished under the GNU GPL2.0 by";
    txt += "\n\nSevenMonkeys:";
    txt += "\nAlberto Adami";
    txt += "\nNicolò Bissacco";
    txt += "\nBeatrice Feltre";
    txt += "\nLuca Luisetto";
    txt += "\nNicola Magnabosco";
    txt += "\nJimmy Martignago";
    txt += "\nDavide Scapin";
    txt += "\n\nseven.monkeys@gmail.com";

    Dialog::dialogInfo("About Romeo", txt);
}

void MainWindowController::slotShortCuts()
{
    QVector<QShortcut*> shortcuts = mainView->getShotcuts();
    QString list;
    for(int i=0; i<shortcuts.size(); ++i)
        list += "<b>"+shortcuts.at(i)->key().toString()+"</b> :: "+shortcuts.at(i)->whatsThis()+"<br/>";

    Dialog::dialogInfo("ShortCuts List", list);
}

void MainWindowController::slotCloseRomeo()
{
    mainView->close();
}

void MainWindowController::slotHelp()
{
    mainView->showHelp("index");
}

void MainWindowController::slotHelpPage()
{
    QString pageName = mainView->getCentralWidget()->objectName();
    if(pageName == "NewSubjectView") mainView->showHelp("createsubject");
    else if(pageName == "SubjectsView") mainView->showHelp("visualizesubject");
    else if(pageName == "NewGroupView") mainView->showHelp("creategroup");
    else if(pageName == "GroupView") mainView->showHelp("visualizegroup");
    else if(pageName == "NewProtocolView") mainView->showHelp("createprotocol");
    else if(pageName == "ProtocolsView") mainView->showHelp("visualizeprotocol");
    else if(pageName == "NewDatasetView") mainView->showHelp("createdataset");
    else if(pageName == "DatasetsView") mainView->showHelp("visualizedataset");
    else if(pageName == "AnalysisView") mainView->showHelp("analysisdetails");
    else if(pageName == "ResultsView") mainView->showHelp("analysisresult");
    else if(pageName == "DetailedResult") mainView->showHelp("analysisresult", "fig18");
    else mainView->showHelp("index");
}

void MainWindowController::slotHelpVideo()
{
    QDesktopServices::openUrl(QUrl("http://youtu.be/JvtW1po9hRU"));
}

MainWindowController *MainWindowController::mainWindowController=0;
