#include "toolbar.h"

using Romeo::View::Component::ToolBar;

//constructor
ToolBar::ToolBar(QWidget * parent) : QToolBar(parent)
{
    setObjectName("ToolBar");

    setupToolbar();

    addConnections();

    loadCss();
}

void ToolBar::addConnections()
{
    connect(homeButton, SIGNAL(clicked()), this, SIGNAL(backToHome()));
    connect(newSubjectButton, SIGNAL(clicked()), this, SIGNAL(createNewSubject()));
    connect(newGroupButton, SIGNAL(clicked()), this, SIGNAL(createNewGroup()));
    connect(newProtocolButton, SIGNAL(clicked()), this, SIGNAL(createNewProtocol()));
    connect(newDatasetButton, SIGNAL(clicked()), this, SIGNAL(createNewDataset()));

    connect(manageSubjectButton, SIGNAL(clicked()), this, SIGNAL(showSubjects()));
    connect(manageGroupButton, SIGNAL(clicked()), this, SIGNAL(showGroups()));
    connect(manageProtocolButton, SIGNAL(clicked()), this, SIGNAL(showProtocols()));
    connect(manageDatasetButton, SIGNAL(clicked()), this, SIGNAL(showDatasets()));

    connect(startAnalysisButton, SIGNAL(clicked()), this, SIGNAL(startAnalysis()));
    connect(resultsButton, SIGNAL(clicked()), this, SIGNAL(showResults()));

    connect(actionHelpInteractiveGuide, SIGNAL(triggered()), this, SIGNAL(helpManualSignal()));
    connect(actionHelpVideoGuide, SIGNAL(triggered()), this, SIGNAL(helpVideoGuideSignal()));

    connect(aboutAction, SIGNAL(triggered()), this, SIGNAL(menuAbout()));
    connect(shortCutsAction, SIGNAL(triggered()), this, SIGNAL(shortCutsSignal()));
    connect(exitButton, SIGNAL(clicked()), this, SIGNAL(menuExit()));
}

void ToolBar::setupToolbar()
{
    setFloatable(false);
    setAllowedAreas(Qt::LeftToolBarArea | Qt::TopToolBarArea | Qt::RightToolBarArea);

    createMenus();
    createButtons();
}

void ToolBar::createMenus()
{
    menuHelp = new QMenu(tr("Help"));
    menuHelp->setObjectName("menuHelp");

    actionHelpInteractiveGuide = new QAction(tr("Interactive Guide"), this);
    actionHelpInteractiveGuide->setObjectName("actionHelpInteractiveGuide");
    actionHelpInteractiveGuide->setToolTip("Interactive Manual Guide");
    actionHelpInteractiveGuide->setIcon(QIcon(":/Romeo/toolbar/manual.png"));
    actionHelpInteractiveGuide->setShortcut(Utils::SHORTCUT_HELP_MANUAL);

    actionHelpVideoGuide = new QAction(tr("Video Guide"), this);
    actionHelpVideoGuide->setObjectName("actionHelpVideoGuide");
    actionHelpVideoGuide->setToolTip("Help Video Guide");
    actionHelpVideoGuide->setIcon(QIcon(":/Romeo/toolbar/videoguide.png"));
    actionHelpVideoGuide->setShortcut(Utils::SHORTCUT_HELP_VIDEO);

    aboutAction = new QAction("About Us", this);
    aboutAction->setObjectName("aboutAction");
    aboutAction->setToolTip("About Us");
    aboutAction->setIcon(QIcon(":/Romeo/toolbar/about.png"));
    aboutAction->setShortcut(Utils::SHORTCUT_ABOUT);

    shortCutsAction = new QAction("ShortCut Keys", this);
    shortCutsAction->setObjectName("shortCutsAction");
    shortCutsAction->setToolTip("ShortCut Keys");
    shortCutsAction->setIcon(QIcon(":/Romeo/toolbar/shortcuts.png"));
    shortCutsAction->setShortcut(Utils::SHORTCUT_SHORTCUTS);

    menuHelp->addAction(actionHelpInteractiveGuide);
    menuHelp->addAction(actionHelpVideoGuide);
    menuHelp->addSeparator();
    menuHelp->addAction(shortCutsAction);
    menuHelp->addAction(aboutAction);
}

void ToolBar::createButtons()
{
    homeButton = new QToolButton(this);
    homeButton->setObjectName("homeButton");
    homeButton->setToolTip("Romeo Home Page :: "+Utils::SHORTCUT_HOME.toString());

    newSubjectButton = new QToolButton(this);
    newSubjectButton->setObjectName("newSubjectButton");
    newSubjectButton->setToolTip("Create new Subject :: "+Utils::SHORTCUT_SUBJECT_NEW.toString());

    manageSubjectButton = new QToolButton(this);
    manageSubjectButton->setObjectName("manageSubjectButton");
    manageSubjectButton->setToolTip("Manage the Subjects :: "+Utils::SHORTCUT_SUBJECT_MANAGE.toString());

    newGroupButton = new QToolButton(this);
    newGroupButton->setObjectName("newGroupButton");
    newGroupButton->setToolTip("Create new Group of Subjects :: "+Utils::SHORTCUT_GROUP_NEW.toString());

    manageGroupButton = new QToolButton(this);
    manageGroupButton->setObjectName("manageGroupButton");
    manageGroupButton->setToolTip("Manage Groups of Subjects :: "+Utils::SHORTCUT_GROUP_MANAGE.toString());

    newProtocolButton = new QToolButton(this);
    newProtocolButton->setObjectName("newProtocolButton");
    newProtocolButton->setToolTip("Create new Protocol :: "+Utils::SHORTCUT_PROTOCOL_NEW.toString());

    manageProtocolButton = new QToolButton(this);
    manageProtocolButton->setObjectName("manageProtocolButton");
    manageProtocolButton->setToolTip("Manage Protocols :: "+Utils::SHORTCUT_PROTOCOL_MANAGE.toString());

    newDatasetButton = new QToolButton(this);
    newDatasetButton->setObjectName("newDatasetButton");
    newDatasetButton->setToolTip("Create new Dataset :: "+Utils::SHORTCUT_DATASET_NEW.toString());

    manageDatasetButton = new QToolButton(this);
    manageDatasetButton->setObjectName("manageDatasetButton");
    manageDatasetButton->setToolTip("Manage Datasets :: "+Utils::SHORTCUT_DATASET_MANAGE.toString());

    startAnalysisButton = new QToolButton(this);
    startAnalysisButton->setObjectName("startAnalysisButton");
    startAnalysisButton->setToolTip("Start the Analysis :: "+Utils::SHORTCUT_START_ANALYSIS.toString());

    resultsButton = new QToolButton(this);
    resultsButton->setObjectName("resultsButton");
    resultsButton->setToolTip("Show the Analysis Results :: "+Utils::SHORTCUT_RESULT_ANALYSYS.toString());

    helpButton = new QToolButton(this);
    helpButton->setPopupMode(QToolButton::InstantPopup);
    helpButton->setObjectName("helpButton");
    helpButton->setToolTip("More Help");

    exitButton = new QToolButton(this);
    exitButton->setObjectName("exitButton");
    QKeySequence q = QKeySequence(QKeySequence::Quit);
    QKeySequence c = QKeySequence(QKeySequence::Close);
    exitButton->setToolTip("Click to exit Romeo :: "+q.toString()+" / "+c.toString());

    helpButton->setMenu(menuHelp);

    addWidget(homeButton);
    addSeparator();
    addWidget(newSubjectButton);
    addWidget(manageSubjectButton);
    addWidget(newGroupButton);
    addWidget(manageGroupButton);
    addWidget(newProtocolButton);
    addWidget(manageProtocolButton);
    addWidget(newDatasetButton);
    addWidget(manageDatasetButton);
    addSeparator();
    addWidget(startAnalysisButton);
    addWidget(resultsButton);
    addSeparator();
    addWidget(helpButton);
    addWidget(exitButton);
}

void ToolBar::loadCss()
{
    QFile file(":/Romeo/toolbar.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromUtf8(file.readAll());
    setStyleSheet(styleSheet);
}
