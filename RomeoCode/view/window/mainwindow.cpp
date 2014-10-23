#include "mainwindow.h"

using Romeo::View::Window::MainWindow;
using Romeo::View::Component::ToolBar;

MainWindow * MainWindow::mainWindow=0;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setObjectName("MainWindow");
    setWindowIcon(QIcon(":/Romeo/romeoLogo.png"));
    setupMainWindow();

    loadCss();

    addConnections();

    createShortCuts();
}

ToolBar * MainWindow::getToolBar() const
{
    return toolBar;
}

//set the general settings of main window
void MainWindow::setupMainWindow()
{
    setMinimumWidth(800);
    setMinimumHeight(700);
    toolBar = new ToolBar(this);
    assistant = new Assistant();
    addToolBar(toolBar);
}

void MainWindow::addConnections() const {
}

//add the central widget
void MainWindow::addCentralWidget(APanel *central)
{
    if(central) {

        this->central=central;
        this->central->setParent(this);

        if(this->central->isShowToolbar()) toolBar->show();
        else toolBar->hide();

        setCentralWidget(this->central);
    }
}

//load the default css file
void MainWindow::loadCss() const
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/default.css");
    qApp->setStyleSheet(styleSheet);
}

QString MainWindow::loadCssStatic(const QString& path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    return QString::fromUtf8(file.readAll());
}

void MainWindow::writeStatusBar(const QString& txt, int timeout)
{
    statusBar()->showMessage(txt, timeout);
}

MainWindow * MainWindow::getMainWindow()
{
    if(!MainWindow::mainWindow)
        MainWindow::mainWindow=new MainWindow();
    return MainWindow::mainWindow;
}

void MainWindow::createShortCuts() {

    QShortcut *nsSC = new QShortcut(Utils::SHORTCUT_SUBJECT_NEW, this);
    nsSC->setWhatsThis("New Subject");
    QShortcut *sSC = new QShortcut(Utils::SHORTCUT_SUBJECT_MANAGE, this);
    sSC->setWhatsThis("Manage Subjects");
    QShortcut *ngSC = new QShortcut(Utils::SHORTCUT_GROUP_NEW, this);
    ngSC->setWhatsThis("New Group of Subjects");
    QShortcut *gSC = new QShortcut(Utils::SHORTCUT_GROUP_MANAGE, this);
    gSC->setWhatsThis("Manage Groups of Subjects");
    QShortcut *npSC = new QShortcut(Utils::SHORTCUT_PROTOCOL_NEW, this);
    npSC->setWhatsThis("New Protocol");
    QShortcut *pSC = new QShortcut(Utils::SHORTCUT_PROTOCOL_MANAGE, this);
    pSC->setWhatsThis("Manage Protocols");
    QShortcut *ndSC = new QShortcut(Utils::SHORTCUT_DATASET_NEW, this);
    ndSC->setWhatsThis("New Dataset");
    QShortcut *dSC = new QShortcut(Utils::SHORTCUT_DATASET_MANAGE, this);
    dSC->setWhatsThis("Manage Datasets");
    QShortcut *saSC = new QShortcut(Utils::SHORTCUT_START_ANALYSIS, this);
    saSC->setWhatsThis("Start Analysis");
    QShortcut *arSC = new QShortcut(Utils::SHORTCUT_RESULT_ANALYSYS, this);
    arSC->setWhatsThis("Show Results");
    QShortcut *exitSC = new QShortcut(QKeySequence::Quit, this);
    exitSC->setWhatsThis("Close Romeo");
    QShortcut *exitSC2 = new QShortcut(QKeySequence::Close, this);
    exitSC2->setWhatsThis("Close Romeo");
    QShortcut *aboutSC = new QShortcut(Utils::SHORTCUT_ABOUT, this);
    aboutSC->setWhatsThis("About Romeo");
    QShortcut *helpMSC = new QShortcut(Utils::SHORTCUT_HELP_MANUAL, this);
    helpMSC->setWhatsThis("User Guide (Manual)");
    QShortcut *helpVSC = new QShortcut(Utils::SHORTCUT_HELP_VIDEO, this);
    helpVSC->setWhatsThis("Video Guide");
    QShortcut *homeSC = new QShortcut(Utils::SHORTCUT_HOME, this);
    homeSC->setWhatsThis("Home Page of Romeo");
    QShortcut *shortCutsSC = new QShortcut(Utils::SHORTCUT_SHORTCUTS, this);
    shortCutsSC->setWhatsThis("Shortcuts List");

    shortcuts.append(homeSC);
    shortcuts.append(nsSC);
    shortcuts.append(sSC);
    shortcuts.append(ngSC);
    shortcuts.append(gSC);
    shortcuts.append(npSC);
    shortcuts.append(pSC);
    shortcuts.append(ndSC);
    shortcuts.append(dSC);
    shortcuts.append(saSC);
    shortcuts.append(arSC);
    shortcuts.append(exitSC);
    shortcuts.append(exitSC2);
    shortcuts.append(aboutSC);
    shortcuts.append(helpMSC);
    shortcuts.append(helpVSC);
    shortcuts.append(shortCutsSC);

    connect(nsSC,SIGNAL(activated()), this, SIGNAL(createNewSubjectSC()));
    connect(sSC,SIGNAL(activated()), this, SIGNAL(showSubjectsSC()));
    connect(ngSC,SIGNAL(activated()), this, SIGNAL(createNewGroupSC()));
    connect(gSC,SIGNAL(activated()), this, SIGNAL(showGroupsSC()));
    connect(npSC,SIGNAL(activated()), this, SIGNAL(createNewProtocolSC()));
    connect(pSC,SIGNAL(activated()), this, SIGNAL(showProtocolsSC()));
    connect(ndSC,SIGNAL(activated()), this, SIGNAL(createNewDatasetSC()));
    connect(dSC,SIGNAL(activated()), this, SIGNAL(showDatasetsSC()));
    connect(saSC,SIGNAL(activated()), this, SIGNAL(startAnalysisSC()));
    connect(arSC,SIGNAL(activated()), this, SIGNAL(showResultsSC()));
    connect(exitSC,SIGNAL(activated()), this, SIGNAL(exitSC()));
    connect(exitSC2,SIGNAL(activated()), this, SIGNAL(exitSC()));
    connect(aboutSC,SIGNAL(activated()), this, SIGNAL(aboutSC()));
    connect(helpMSC,SIGNAL(activated()), this, SIGNAL(helpManualSC()));
    connect(helpVSC,SIGNAL(activated()), this, SIGNAL(helpVideoGuideSC()));
    connect(homeSC,SIGNAL(activated()), this, SIGNAL(homeSC()));
    connect(shortCutsSC,SIGNAL(activated()), this, SIGNAL(shortCutsSC()));
}

QVector<QShortcut*> MainWindow::getShotcuts() const {
    return shortcuts;
}

void MainWindow::setShortcutHomeEnable(bool enable) {
    for(int i=0; i<shortcuts.size(); ++i){
        if(shortcuts.at(i)->key()==Utils::SHORTCUT_ABOUT || shortcuts.at(i)->key()==Utils::SHORTCUT_HELP_MANUAL || shortcuts.at(i)->key()==Utils::SHORTCUT_HELP_VIDEO|| shortcuts.at(i)->key()==Utils::SHORTCUT_SHORTCUTS)
            shortcuts.at(i)->setEnabled(enable);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    int response = Romeo::View::Dialog::Dialog::dialogQuestion("Exit Romeo", "Are you sure you want to Exit from Romeo?", "All unsaved data will be lost!");
    if(response != QMessageBox::Yes)
        event->ignore();
    else
        delete assistant;
}

void MainWindow::showHelp(const QString &page, const QString &anchor) const
{
    assistant->showDocumentation(page, anchor);
}

APanel *MainWindow::getCentralWidget() const {
    return central;
}
