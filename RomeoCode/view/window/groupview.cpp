#include "groupview.h"

using Romeo::View::Window::GroupView;

GroupView::GroupView(QWidget *parent) : APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("Groups Of Subjects - ROMEO");
    initializeView();
}

void GroupView::createTop()
{
    topWidget = new QWidget(this);

    tableWidget = new QWidget(topWidget);

    groupTable = new QTableView(tableWidget);
    groupTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    groupTable->setTabKeyNavigation(false);
    groupTable->setSelectionMode(QAbstractItemView::SingleSelection);
    groupTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    groupTable->horizontalHeader()->setHighlightSections(false);
    groupTable->horizontalHeader()->setStretchLastSection(true);
    groupTable->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    groupTable->setProperty("showDropIndicator", QVariant(false));
    groupTable->setDragDropOverwriteMode(false);
    groupTable->setAlternatingRowColors(true);
    groupTable->setCornerButtonEnabled(false);

    modelTable = new GroupTableModel();
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(modelTable);
    groupTable->setModel(proxyModel);
    groupTable->setSortingEnabled(true);
    groupTable->horizontalHeader()->resizeSection(1, 50);
    groupTable->horizontalHeader()->resizeSection(2, 70);
    groupTable->resizeColumnsToContents();

    groupBox = new QGroupBox(topWidget);
    groupBox->setTitle("Details");

    subjectList = new QTableView(groupBox);
    subjectList->setAlternatingRowColors(true);
    subjectList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    subjectList->setTabKeyNavigation(false);
    subjectList->setSelectionMode(QAbstractItemView::NoSelection);
    subjectList->setSelectionBehavior(QAbstractItemView::SelectRows);
    subjectList->horizontalHeader()->setHighlightSections(false);
    subjectList->horizontalHeader()->setStretchLastSection(true);
    subjectList->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    subjectList->setProperty("showDropIndicator", QVariant(false));
    subjectList->setDragDropOverwriteMode(false);
    subjectList->setAlternatingRowColors(true);
    subjectList->setCornerButtonEnabled(false);

    modelSubjectsTable = new GroupSubjectsTableModel();
    QSortFilterProxyModel *proxySubjectsModel = new QSortFilterProxyModel(this);
    proxySubjectsModel->setSourceModel(modelSubjectsTable);
    subjectList->setModel(proxySubjectsModel);
    subjectList->setSortingEnabled(true);
    subjectList->resizeColumnsToContents();
    subjectList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    subjectList->horizontalHeader()->resizeSection(0, 150);
    subjectList->horizontalHeader()->resizeSection(1, 50);
}

void GroupView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_EDIT_DELETE, this);
}

void GroupView::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(bottomWidget);
    setupTopLayout();
}

void GroupView::setupTopLayout()
{
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);
    groupBoxLayout->setSpacing(-1);
    groupBoxLayout->setContentsMargins(10, 10, 10, 10);
    groupBoxLayout->addWidget(subjectList);
    groupBoxLayout->addWidget(labelInfo("List of Subjects in the Group.", groupBox));

    QVBoxLayout *tableWidgetLayout = new QVBoxLayout(tableWidget);
    tableWidgetLayout->setSpacing(-1);
    tableWidgetLayout->setContentsMargins(0, 0, 0, 0);
    if(modelTable->rowCount() == 0) {
        tableWidgetLayout->addWidget(labelEmpty("There are no Groups. Create one!", tableWidget));
        bottomWidget->setEnableEdit(false);
        bottomWidget->setEnableDelete(false);
    }
    tableWidgetLayout->addWidget(groupTable);
    tableWidgetLayout->addWidget(labelInfo("List of Groups.\nClick on a Group to view details.", tableWidget));

    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);
    topWidgetLayout->addWidget(tableWidget);
    topWidgetLayout->addWidget(groupBox);
}

void GroupView::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/groups.css");
    setStyleSheet(styleSheet);
}

void GroupView::setupObjectName()
{
    setObjectName("GroupView");
    topWidget->setObjectName("topWidget");
    groupTable->setObjectName("groupTable");
    groupBox->setObjectName("groupBox");
    subjectList->setObjectName("subjectList");
    bottomWidget->setObjectName("bottomWidget");
}

void GroupView::setupToolTip()
{

}

void GroupView::setupView()
{
    createTop();
    createBottom();
}

void GroupView::addConnect() const {
    connect(groupTable, SIGNAL(clicked(QModelIndex)), this, SIGNAL(itemSelected(QModelIndex)));
}

QTableView * GroupView::getGroupTable() const {
    return groupTable;
}

QTableView * GroupView::getSubjectsTable() const {
    return subjectList;
}

void GroupView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}
