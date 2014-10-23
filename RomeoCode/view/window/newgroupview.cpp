#include "newgroupview.h"

using Romeo::View::Window::NewGroupView;

NewGroupView::NewGroupView(QWidget *parent): APanel(parent), nSubjects(0)
{
    MainWindow::getMainWindow()->setWindowTitle("New Group Of Subjects - ROMEO");
    initializeView();
}

void NewGroupView::createTop()
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    topWidget = new QWidget(this);

    createBox = new QGroupBox(tr("Create a new Group"),topWidget);
    groupName = new QWidget(createBox);
    groupLabel = new QLabel("Group name "+Utils::TXT_REQUIRED, groupName);
    groupLineEdit = new QLineEdit(groupName);

    groupType = new QWidget(createBox);
    typeLabel = new QLabel("Type "+Utils::TXT_REQUIRED, groupType);
    comboBoxType = new QComboBox(groupType);
    comboBoxType->setModel(APanel::getTypeRomeo(comboBoxType));

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    model = new NewGroupTableModel();
    listGroup = new QGroupBox("List of Subjects("+QString::number(nSubjects)+") "+Utils::TXT_REQUIRED, topWidget);
    tableView = new QTableView();
    tableView->setSizePolicy(sizePolicy);    
    tableView->setLineWidth(1);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setTabKeyNavigation(false);
    tableView->setProperty("showDropIndicator", QVariant(false));
    tableView->setDragDropOverwriteMode(false);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setCornerButtonEnabled(false);
    tableView->horizontalHeader()->setHighlightSections(false);
    tableView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
    tableView->verticalHeader()->setVisible(false);

    tableView->setModel(model);
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->resizeColumnsToContents();

    selDeselAllWidget = new SelectDeselectWidget(this);
}

void NewGroupView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_SAVE, this);
}

void NewGroupView::setupLayout(){
    QVBoxLayout *mainWidgetLayout = new QVBoxLayout(this);
    mainWidgetLayout->setSpacing(-1);
    mainWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mainWidgetLayout->addWidget(topWidget);
    mainWidgetLayout->addWidget(bottomWidget);
    setupTopLayout();
}

void NewGroupView::setupTopLayout()
{
    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);
    topWidgetLayout->addWidget(createBox);
    topWidgetLayout->addWidget(listGroup);

    QVBoxLayout *createBoxLayout = new QVBoxLayout(createBox);
    createBoxLayout->setSpacing(20);
    createBoxLayout->setContentsMargins(10, 10, 10, 10);
    createBoxLayout->addWidget(groupName);
    createBoxLayout->addWidget(groupType);
    createBoxLayout->addItem(verticalSpacer);

    QVBoxLayout *groupNameLayout = new QVBoxLayout(groupName);
    groupNameLayout->setSpacing(1);
    groupNameLayout->setContentsMargins(0, 0, 0, 0);
    groupNameLayout->addWidget(groupLabel);
    groupNameLayout->addWidget(groupLineEdit);
    groupNameLayout->addWidget(labelInfo("Select the type of Group.", groupName));

    QVBoxLayout *groupTypeLayout = new QVBoxLayout(groupType);
    groupTypeLayout->setSpacing(1);
    groupTypeLayout->setContentsMargins(0, 0, 0, 0);
    groupTypeLayout->addWidget(typeLabel);
    groupTypeLayout->addWidget(comboBoxType);
    groupTypeLayout->addWidget(labelInfo("Insert the name of the Group.", groupType));

    QVBoxLayout *listGroupLayout = new QVBoxLayout(listGroup);
    listGroupLayout->setSpacing(-1);
    listGroupLayout->setContentsMargins(10, 10, 10, 10);
    listGroupLayout->addWidget(tableView);
    listGroupLayout->addWidget(selDeselAllWidget);
    listGroupLayout->addWidget(labelInfo("List of Subjects according to the Type selected.\nSelect the Subjects to be added to the group.", listGroup));
}

void NewGroupView::setupObjectName()
{
    setObjectName("NewGroupView");
    topWidget->setObjectName("topWidget");
    createBox->setObjectName("createBox");
    groupName->setObjectName("groupName");
    groupLabel->setObjectName("groupLabel");
    groupLineEdit->setObjectName("groupLineEdit");
    groupType->setObjectName("groupType");
    typeLabel->setObjectName("typeLabel");
    comboBoxType->setObjectName("comboBoxType");
    listGroup->setObjectName("listGroup");
    tableView->setObjectName("tableView");
}

void NewGroupView::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/groups.css");
    setStyleSheet(styleSheet);
}

void NewGroupView::setupToolTip()
{
    groupLineEdit->setToolTip("Insert a Group name");
    comboBoxType->setToolTip("Select a type");
}

void NewGroupView::addConnect() const
{
    connect(comboBoxType, SIGNAL(currentTextChanged(QString)), this, SIGNAL(typeSelection(QString)));
}

void NewGroupView::setupView(){
    createTop();
    createBottom();
}

QTableView* NewGroupView::getTableView() {
    return tableView;
}

QSortFilterProxyModel * NewGroupView::updateProxyModel(NewGroupTableModel *model) {
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->clear();
    return proxyModel;
}

NewGroupTableModel * NewGroupView::getNewGroupTableModel() const {
    return model;
}

QString NewGroupView::getName() const {
    return groupLineEdit->text();
}

QString NewGroupView::getType() const {
    return comboBoxType->currentText();
}

QModelIndexList NewGroupView::getSelectedSubjects() const {
    QItemSelectionModel* selectedModel = tableView->selectionModel();
    return selectedModel->selectedRows();
}

void NewGroupView::resetFields() {
    MainWindow::getMainWindow()->setWindowTitle("New Group Of Subjects - ROMEO");
    createBox->setTitle("Create a new Group");
    groupLineEdit->clear();
    groupLineEdit->setEnabled(true);
    comboBoxType->setCurrentIndex(0);
    comboBoxType->setEnabled(true);
    model->resetListModel();
}

void NewGroupView::setNSubjects(int n) {
    if(n>0) nSubjects=n;
    else nSubjects=0;

    listGroup->setTitle("List of Subjects("+QString::number(nSubjects)+") "+Utils::TXT_REQUIRED);
}

void NewGroupView::setEditFields(GroupOfSubject* group) {
    MainWindow::getMainWindow()->setWindowTitle("Edit Group Of Subjects - ROMEO");

    createBox->setTitle("Edit Group");
    groupLineEdit->setText(group->getName());
    groupLineEdit->setEnabled(false);
    QString type = group->getImageType();
    comboBoxType->setCurrentText(type);
    comboBoxType->setEnabled(false);

    QItemSelectionModel* selectedModel = new QItemSelectionModel(tableView->model());

    for(int i=0; i<tableView->model()->rowCount(); ++i) {
        QModelIndex indexLeft(tableView->model()->index(i, 0));
        QModelIndex indexRight(tableView->model()->index(i, tableView->model()->columnCount()-1));

        if(group->getSubjectWithName(indexLeft.data().toString())) {
            QItemSelection selectionRow(indexLeft, indexRight);
            selectedModel->select(selectionRow, QItemSelectionModel::Select);
        }
    }

    tableView->setSelectionModel(selectedModel);
    tableView->setFocus();
}

void NewGroupView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}
