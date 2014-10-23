#include "navwidget.h"

using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;

NavWidget::NavWidget(Type type, APanel *parent) : QWidget(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);

    QHBoxLayout *widgetLayout = new QHBoxLayout(this);
    widgetLayout->setSpacing(-1);
    widgetLayout->setContentsMargins(10, 10, 10, 10);

    setSizePolicy(sizePolicy2);

    navContainer = new QWidget(this);
    navContainer->setSizePolicy(sizePolicy);
    QHBoxLayout *navContainerLayout = new QHBoxLayout(navContainer);
    navContainerLayout->setSpacing(-1);
    navContainerLayout->setContentsMargins(0, 0, 0, 0);

    helpContainer = new QWidget(this);
    helpContainer->setSizePolicy(sizePolicy1);
    QHBoxLayout *helpContainerLayout = new QHBoxLayout(helpContainer);
    helpContainerLayout->setSpacing(-1);
    helpContainerLayout->setContentsMargins(0, 0, 0, 0);

    create(type, navContainerLayout, helpContainerLayout);

    widgetLayout->addWidget(navContainer);
    widgetLayout->addWidget(helpContainer);

    setupObjectsName();
}

void NavWidget::create(Type type, QHBoxLayout *navContainerLayout, QHBoxLayout *helpContainerLayout)
{
    switch(type) {
        // If type = _ONLY_BACK
        case _ONLY_BACK:
            createBackButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;
        // if type = _BACK_SAVE
        case _BACK_SAVE:
            createBackButton(navContainerLayout, navContainer);
            createSaveButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        // if type = _BACK_EDIT
        case _BACK_EDIT:
            createBackButton(navContainerLayout, navContainer);
            createEditButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        // if type = _BACK_EDIT_DELETE
        case _BACK_EDIT_DELETE:
            createBackButton(navContainerLayout, navContainer);
            createEditButton(navContainerLayout, navContainer);
            createDeleteButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        // if type = _BACK_DELETE
        case _BACK_DELETE:
            createBackButton(navContainerLayout, navContainer);
            createDeleteButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        // if type = _BACK_START_ANALYSIS
        case _BACK_START_ANALYSIS:
            createBackButton(navContainerLayout, navContainer);
            createStartAnalysisButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        //_BACK_RESTART_SHOW
        case _BACK_RESTART_SHOW:
            createBackButton(navContainerLayout, navContainer);
            createRestartButton(navContainerLayout, navContainer);
            createShowButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        //_BACK_EXPORT
        case _BACK_EXPORT:
            createBackButton(navContainerLayout, navContainer);
            createExportButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
            break;

        default:
            createBackButton(navContainerLayout, navContainer);
            createHelpButton(helpContainerLayout, helpContainer);
    }
}

void NavWidget::createBackButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    backButton = new QPushButton(parent);
    backButton->setObjectName("backButton");
    backButton->setSizePolicy(sizePolicy);
    backButton->setText("Back");
    backButton->setToolTip(tr("Back to previous page"));
    backButton->setEnabled(enable);

    layout->addWidget(backButton);

    connect(backButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(backView()));
}

void NavWidget::createEditButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    editButton = new QPushButton(parent);
    editButton->setObjectName("editButton");
    editButton->setSizePolicy(sizePolicy);
    editButton->setText("Edit");
    editButton->setToolTip("Edit the selected element");
    editButton->setEnabled(enable);

    layout->addWidget(editButton);

    connect(editButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(editObject()));
}

void NavWidget::createSaveButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    saveButton = new QPushButton(parent);
    saveButton->setObjectName("saveButton");
    saveButton->setSizePolicy(sizePolicy);
    saveButton->setText("Save");
    saveButton->setToolTip("Save the element on the system");
    saveButton->setEnabled(enable);

    layout->addWidget(saveButton);

    connect(saveButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(saveObject()));
}


void NavWidget::createDeleteButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    deleteButton = new QPushButton(parent);
    deleteButton->setObjectName("deleteButton");
    deleteButton->setSizePolicy(sizePolicy);
    deleteButton->setText("Delete");
    deleteButton->setToolTip("Delete the selected element");
    deleteButton->setEnabled(enable);

    layout->addWidget(deleteButton);

    connect(deleteButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(deleteObject()));
}

void NavWidget::createRestartButton(QHBoxLayout *layout, QWidget* parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    restartButton = new QPushButton(parent);
    restartButton->setObjectName("restartButton");
    restartButton->setSizePolicy(sizePolicy);
    restartButton->setText("Restart");
    restartButton->setToolTip("Restart the selected Analysis");
    restartButton->setEnabled(enable);

    layout->addWidget(restartButton);

    connect(restartButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(restartAnalysis()));
}

void NavWidget::createShowButton(QHBoxLayout *layout, QWidget* parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    showButton = new QPushButton(parent);
    showButton->setObjectName("showButton");
    showButton->setSizePolicy(sizePolicy);
    showButton->setText("Show");
    showButton->setToolTip("Show the results of selected Analysis");
    showButton->setEnabled(enable);

    layout->addWidget(showButton);

    connect(showButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(showAnalysisResults()));
}

void NavWidget::createStartAnalysisButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    startAnalysisButton = new QPushButton(parent);
    startAnalysisButton->setObjectName("startAnalysisButton");
    startAnalysisButton->setSizePolicy(sizePolicy);
    startAnalysisButton->setText("Start Analysis");
    startAnalysisButton->setToolTip("Start the Analysis");
    startAnalysisButton->setEnabled(enable);

    layout->addWidget(startAnalysisButton);

    connect(startAnalysisButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(startAnalysis()));
}

void NavWidget::createExportButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    exportButton = new QPushButton(parent);
    exportButton->setObjectName("exportButton");
    exportButton->setSizePolicy(sizePolicy);
    exportButton->setText("Export");
    exportButton->setToolTip("Export the Analysis Results");
    exportButton->setEnabled(enable);

    layout->addWidget(exportButton);

    connect(exportButton, SIGNAL(clicked()), qobject_cast<APanel*>(this->parentWidget()), SIGNAL(exportSignal()));
}

void NavWidget::createHelpButton(QHBoxLayout *layout, QWidget *parent, bool enable)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    helpButton = new QPushButton(parent);
    helpButton->setObjectName("helpButton");
    helpButton->setSizePolicy(sizePolicy);
    helpButton->setCursor(QCursor(Qt::PointingHandCursor));
    helpButton->setToolTip(tr("Get Help for this page"));
    helpButton->setEnabled(enable);

    layout->addWidget(helpButton);

    connect(helpButton, SIGNAL(clicked()), MainWindow::getMainWindow(), SIGNAL(helpPage()));
}

void NavWidget::setupObjectsName()
{
    this->setObjectName("NavWidgetx");
    navContainer->setObjectName("navContainer");
    helpContainer->setObjectName("helpContainer");
}

void NavWidget::setEnableBack(bool enable)
{
    if(backButton)
        backButton->setEnabled(enable);
}

void NavWidget::setEnableEdit(bool enable)
{
    if(editButton)
        editButton->setEnabled(enable);
}

void NavWidget::setEnableSave(bool enable)
{
    if(saveButton)
        saveButton->setEnabled(enable);
}

void NavWidget::setEnableDelete(bool enable)
{
    if(deleteButton)
        deleteButton->setEnabled(enable);
}

void NavWidget::setEnableStartAnalysis(bool enable)
{
    if(startAnalysisButton)
        startAnalysisButton->setEnabled(enable);
}

void NavWidget::setEnableHelp(bool enable)
{
    if(helpButton)
        helpButton->setEnabled(enable);
}

void NavWidget::setEnableRestart(bool enable)
{
    if(restartButton)
        restartButton->setEnabled(enable);
}

void NavWidget::setEnableShow(bool enable)
{
    if(showButton)
        showButton->setEnabled(enable);
}
