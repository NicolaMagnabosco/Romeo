#include "welcomeview.h"

using Romeo::View::Window::WelcomeView;

//contructor
WelcomeView::WelcomeView(QWidget *parent) : APanel(parent) {
    MainWindow::getMainWindow()->setWindowTitle("ROMEO");

    setShowToolbar(false);

    initializeView();
}

//setup the widget
void WelcomeView::setupView() {

    setupLeftFrame();
    setupRightFrame();
}

void WelcomeView::setupLayout() {

    QHBoxLayout *principalLayout = new QHBoxLayout(this);
    principalLayout->addWidget(frameLeft);
    principalLayout->addWidget(frameRight);
    principalLayout->setStretch(0, 2);
    principalLayout->setStretch(1, 1);
    principalLayout->setSpacing(-1);
    principalLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layoutLeft = new QVBoxLayout(frameLeft);
    layoutLeft->setSpacing(-1);
    layoutLeft->setContentsMargins(0, 0, 0, 0);
    layoutLeft->addWidget(boxSubject);
    layoutLeft->addWidget(boxGroup);
    layoutLeft->addWidget(boxProtocol);
    layoutLeft->addWidget(boxDataset);

    QHBoxLayout *layoutBoxSubject = new QHBoxLayout(boxSubject);
    layoutBoxSubject->setSpacing(-1);
    layoutBoxSubject->setContentsMargins(0, 0, 0, 0);
    layoutBoxSubject->addWidget(btnNewSubject);
    layoutBoxSubject->addWidget(btnShowSubject);

    QHBoxLayout *layoutBoxGroup = new QHBoxLayout(boxGroup);
    layoutBoxGroup->setSpacing(-1);
    layoutBoxGroup->setContentsMargins(0, 0, 0, 0);
    layoutBoxGroup->addWidget(btnNewGroup);
    layoutBoxGroup->addWidget(btnShowGroup);

    QHBoxLayout *layoutBoxProtocol = new QHBoxLayout(boxProtocol);
    layoutBoxProtocol->setSpacing(-1);
    layoutBoxProtocol->setContentsMargins(0, 0, 0, 0);
    layoutBoxProtocol->addWidget(btnNewProtocol);
    layoutBoxProtocol->addWidget(btnShowProtocol);

    QHBoxLayout *layoutBoxDataset = new QHBoxLayout(boxDataset);
    layoutBoxDataset->setSpacing(-1);
    layoutBoxDataset->setContentsMargins(0, 0, 0, 0);
    layoutBoxDataset->addWidget(btnNewDataset);
    layoutBoxDataset->addWidget(btnShowDataset);

    QVBoxLayout *layoutRight = new QVBoxLayout(frameRight);
    layoutRight->setSpacing(-1);
    layoutRight->setContentsMargins(0, 0, 0, 0);
    layoutRight->addWidget(boxAnalysis);
    layoutRight->addWidget(boxGuide);
    layoutRight->addWidget(boxExit);
    layoutRight->addWidget(widgetRomeo);

    QVBoxLayout *layoutBoxAnalysis = new QVBoxLayout(boxAnalysis);
    layoutBoxAnalysis->setSpacing(-1);
    layoutBoxAnalysis->setContentsMargins(0, 0, 0, 0);
    layoutBoxAnalysis->addWidget(btnStartAnalysis);
    layoutBoxAnalysis->addWidget(btnAnalysisResults);

    QHBoxLayout *layoutBoxGuide = new QHBoxLayout(boxGuide);
    layoutBoxGuide->setSpacing(-1);
    layoutBoxGuide->setContentsMargins(0, 0, 0, 0);
    layoutBoxGuide->addWidget(btnUserGuide);
    layoutBoxGuide->addWidget(btnVideoGuide);
    layoutBoxGuide->addWidget(btnShortcuts);
    layoutBoxGuide->addWidget(btnAbout);

    QHBoxLayout *layoutBoxExit = new QHBoxLayout(boxExit);
    layoutBoxExit->setSpacing(-1);
    layoutBoxExit->setContentsMargins(0, 0, 0, 0);
    layoutBoxExit->addWidget(btnExit);
}

//setup the left frame of widet
void WelcomeView::setupLeftFrame() {

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    frameLeft = new QFrame(this);
        boxSubject = new QGroupBox(frameLeft);
            btnNewSubject = new QPushButton(boxSubject);
            btnShowSubject = new QPushButton(boxSubject);
            btnNewSubject->setSizePolicy(sizePolicy);
            btnShowSubject->setSizePolicy(sizePolicy);
        boxGroup = new QGroupBox(frameLeft);
            btnNewGroup = new QPushButton(boxGroup);
            btnShowGroup = new QPushButton(boxGroup);
            btnNewGroup->setSizePolicy(sizePolicy);
            btnShowGroup->setSizePolicy(sizePolicy);
        boxProtocol = new QGroupBox(frameLeft);
            btnNewProtocol = new QPushButton(boxProtocol);
            btnShowProtocol = new QPushButton(boxProtocol);
            btnNewProtocol->setSizePolicy(sizePolicy);
            btnShowProtocol->setSizePolicy(sizePolicy);
        boxDataset = new QGroupBox(frameLeft);
            btnNewDataset = new QPushButton(boxDataset);
            btnShowDataset = new QPushButton(boxDataset);
            btnNewDataset->setSizePolicy(sizePolicy);
            btnShowDataset->setSizePolicy(sizePolicy);

    boxSubject->setTitle(tr("Subject"));
    boxGroup->setTitle(tr("Group of Subjects"));
    boxProtocol->setTitle(tr("Protocol"));
    boxDataset->setTitle(tr("Dataset"));  
}

//setup the right part of widget
void WelcomeView::setupRightFrame() {

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    frameRight = new QFrame(this);
        boxAnalysis = new QGroupBox(frameRight);
            btnStartAnalysis = new QPushButton(boxAnalysis);
            btnAnalysisResults = new QPushButton(boxAnalysis);
            btnStartAnalysis->setSizePolicy(sizePolicy);
            btnAnalysisResults->setSizePolicy(sizePolicy);

        boxGuide = new QGroupBox(frameRight);
            btnUserGuide = new QPushButton(boxGuide);
            btnVideoGuide = new QPushButton(boxGuide);
            btnUserGuide->setSizePolicy(sizePolicy);
            btnVideoGuide->setSizePolicy(sizePolicy);
            btnShortcuts = new QPushButton(boxGuide);
            btnAbout = new QPushButton(boxGuide);
            btnShortcuts->setSizePolicy(sizePolicy);
            btnAbout->setSizePolicy(sizePolicy);
        boxExit = new QGroupBox(frameRight);
            btnExit = new QPushButton(boxExit);
            btnExit->setSizePolicy(sizePolicy);

        widgetRomeo = new QWidget();

    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    boxAnalysis->setTitle(tr("Analysis"));
    boxAnalysis->setSizePolicy(sizePolicy1);

    boxGuide->setTitle("More Help");
    boxGuide->setSizePolicy(sizePolicy1);
    boxExit->setTitle("Exit Romeo");
    boxExit->setSizePolicy(sizePolicy1);
}

//load the css of welcome widget
void WelcomeView::loadCss() {

    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/welcome.css");
    setStyleSheet(styleSheet);
}

void WelcomeView::setupToolTip() {

    //subject
    btnNewSubject->setToolTip("Create new Subject :: "+Utils::SHORTCUT_SUBJECT_NEW.toString());
    btnShowSubject->setToolTip("View existent Subjects :: "+Utils::SHORTCUT_SUBJECT_MANAGE.toString());

    //group
    btnNewGroup->setToolTip("Create new Group of Subjects :: "+Utils::SHORTCUT_GROUP_NEW.toString());
    btnShowGroup->setToolTip("View and manage existent Groups of Subjects :: "+Utils::SHORTCUT_GROUP_MANAGE.toString());

    //protocol
    btnNewProtocol->setToolTip("Create new Protocol :: "+Utils::SHORTCUT_PROTOCOL_NEW.toString());
    btnShowProtocol->setToolTip("View and manage existent Protocols :: "+Utils::SHORTCUT_PROTOCOL_MANAGE.toString());

    //dataset
    btnNewDataset->setToolTip("Create new Dataset :: "+Utils::SHORTCUT_DATASET_NEW.toString());
    btnShowDataset->setToolTip("View and manage existent Datasets :: "+Utils::SHORTCUT_DATASET_MANAGE.toString());

    //analysis
    btnStartAnalysis->setToolTip("Start Analysis :: "+Utils::SHORTCUT_START_ANALYSIS.toString());
    btnAnalysisResults->setToolTip("View Results of Analysis :: "+Utils::SHORTCUT_RESULT_ANALYSYS.toString());

    btnUserGuide->setToolTip("Show Romeo User Manual :: "+Utils::SHORTCUT_HELP_MANUAL.toString());
    btnVideoGuide->setToolTip("Show Romeo Video Guide :: "+Utils::SHORTCUT_HELP_VIDEO.toString());

    btnShortcuts->setToolTip("Show Romeo ShortCuts List :: "+Utils::SHORTCUT_SHORTCUTS.toString());
    btnAbout->setToolTip("Show Informations About Romeo :: "+Utils::SHORTCUT_ABOUT.toString());

    QKeySequence q = QKeySequence(QKeySequence::Quit);
    QKeySequence c = QKeySequence(QKeySequence::Close);
    btnExit->setToolTip("Exit Romeo :: "+q.toString()+" / "+c.toString());
}

void WelcomeView::setupObjectName() {

    setObjectName("WelcomeView");

        frameLeft->setObjectName("frameLeft");
            boxSubject->setObjectName("boxSubject");
                btnNewSubject->setObjectName("btnNewSubject");
                btnShowSubject->setObjectName("btnShowSubject");
            boxGroup->setObjectName("boxGroup");
                btnNewGroup->setObjectName("btnNewGroup");
                btnShowGroup->setObjectName("btnShowGroup");
            boxProtocol->setObjectName("boxProtocol");
                btnNewProtocol->setObjectName("btnNewProtocol");
                btnShowProtocol->setObjectName("btnShowProtocol");
            boxDataset->setObjectName("boxDataset");
                btnNewDataset->setObjectName("btnNewDataset");
                btnShowDataset->setObjectName("btnShowDataset");
        frameRight->setObjectName("frameRight");
            boxAnalysis->setObjectName("boxAnalysis");
                btnStartAnalysis->setObjectName("btnStartAnalysis");
                btnAnalysisResults->setObjectName("btnAnalysisResults");                
            boxGuide->setObjectName("boxGuide");
                btnUserGuide->setObjectName("btnUserGuide");
                btnVideoGuide->setObjectName("btnVideoGuide");
                btnShortcuts->setObjectName("btnShortcuts");
                btnAbout->setObjectName("btnAbout");
            boxExit->setObjectName("boxExit");
                btnExit->setObjectName("btnExit");
            widgetRomeo->setObjectName("widgetRomeo");
}

void WelcomeView::addConnect() const {

    connect(btnNewSubject, SIGNAL(clicked()), this, SIGNAL(createNewSubject()));
    connect(btnShowSubject, SIGNAL(clicked()), this, SIGNAL(showSubjects()));
    connect(btnNewGroup, SIGNAL(clicked()), this, SIGNAL(createNewGroup()));
    connect(btnShowGroup, SIGNAL(clicked()), this, SIGNAL(showGroups()));
    connect(btnNewProtocol, SIGNAL(clicked()), this, SIGNAL(createNewProtocol()));
    connect(btnShowProtocol, SIGNAL(clicked()), this, SIGNAL(showProtocols()));
    connect(btnNewDataset, SIGNAL(clicked()), this, SIGNAL(createNewDataset()));
    connect(btnShowDataset, SIGNAL(clicked()), this, SIGNAL(showDatasets()));
    connect(btnStartAnalysis, SIGNAL(clicked()), this, SIGNAL(startAnalysis()));
    connect(btnAnalysisResults, SIGNAL(clicked()), this, SIGNAL(showResults()));

    connect(btnUserGuide, SIGNAL(clicked()), this, SIGNAL(userGuide()));
    connect(btnVideoGuide, SIGNAL(clicked()), this, SIGNAL(videoGuide()));
    connect(btnShortcuts, SIGNAL(clicked()), this, SIGNAL(shortcutsList()));
    connect(btnAbout, SIGNAL(clicked()), this, SIGNAL(aboutus()));
    connect(btnExit, SIGNAL(clicked()), this, SIGNAL(exitSignal()));
}
