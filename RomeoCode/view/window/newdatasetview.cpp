#include "newdatasetview.h"

using Romeo::View::Window::NewDatasetView;

NewDatasetView::NewDatasetView(QWidget *parent): APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("New Dataset - ROMEO");
    initializeView();
}

void NewDatasetView::createTop()
{
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    topWidget = new QWidget(this);

    datasetLabel = new QLabel("Dataset Name "+Utils::TXT_REQUIRED, topWidget);
    datasetLabel->setSizePolicy(sizePolicy1);

    datasetLineEdit = new QLineEdit(topWidget);
    datasetLineEdit->setSizePolicy(sizePolicy1);
    datasetLineEdit->setMinimumWidth(300);
}

void NewDatasetView::createCenter()
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    centralWidget = new QWidget(this);
    subjectBox = new QGroupBox(centralWidget);
    subjectBox->setTitle("Group Of Subjects "+Utils::TXT_REQUIRED);
        subjectTable = new QTableView(subjectBox);
        subjectTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        subjectTable->setTabKeyNavigation(false);
        subjectTable->setProperty("showDropIndicator", QVariant(false));
        subjectTable->setDragDropOverwriteMode(false);
        subjectTable->setAlternatingRowColors(true);
        subjectTable->setSelectionMode(QAbstractItemView::SingleSelection);
        subjectTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        subjectTable->setCornerButtonEnabled(false);
        subjectTable->horizontalHeader()->setHighlightSections(false);
        subjectTable->horizontalHeader()->setStretchLastSection(true);
        subjectTable->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

        modelGroups = new DatasetGroupTableModel();
        QSortFilterProxyModel *proxyModelG = new QSortFilterProxyModel(this);
        proxyModelG->setSourceModel(modelGroups);
        subjectTable->setModel(proxyModelG);
        subjectTable->setSortingEnabled(true);
        subjectTable->resizeColumnsToContents();
        subjectTable->horizontalHeader()->resizeSection(1, 50);

    protocolBox = new QGroupBox(centralWidget);
    protocolBox->setTitle("Protocols "+Utils::TXT_REQUIRED);
        protocolTable = new QTableView(protocolBox);
        protocolTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        protocolTable->setTabKeyNavigation(false);
        protocolTable->setProperty("showDropIndicator", QVariant(false));
        protocolTable->setDragDropOverwriteMode(false);
        protocolTable->setAlternatingRowColors(true);
        protocolTable->setSelectionMode(QAbstractItemView::MultiSelection);
        protocolTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        protocolTable->setCornerButtonEnabled(false);
        protocolTable->horizontalHeader()->setHighlightSections(false);
        protocolTable->horizontalHeader()->setStretchLastSection(true);
        protocolTable->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

        modelProtocols = new DatasetProtocolTableModel();
        QSortFilterProxyModel *proxyModelP = new QSortFilterProxyModel(this);
        proxyModelP->setSourceModel(modelProtocols);
        protocolTable->setModel(proxyModelP);
        protocolTable->setSortingEnabled(true);
        protocolTable->resizeColumnsToContents();
        protocolTable->horizontalHeader()->resizeSection(1, 50);        

    detailsBox = new QGroupBox(centralWidget);
    detailsBox->setTitle("Details");
        detailSubjectScrollArea = new QScrollArea(detailsBox);
        detailSubjectScrollArea->setWidgetResizable(true);
            detailSubjectScrollAreaWidget = new QWidget();
                detailSubject = new QLabel(detailSubjectScrollAreaWidget);
                detailSubject->setAlignment(Qt::AlignTop);
        detailProtocolScrollArea = new QScrollArea(detailsBox);
        detailProtocolScrollArea->setWidgetResizable(true);
            detailProtocolScrollAreaWidget = new QWidget();
                detailProtocol = new QLabel(detailProtocolScrollAreaWidget);
                detailProtocol->setAlignment(Qt::AlignTop);
}

void NewDatasetView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_SAVE, this);
}

void NewDatasetView::setupLayout()
{
    // create the main layout and add three main widget (top, center, bottom)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // the following methods create and setup the layout of the three main widgets (top)
    setupTopLayout();
    setupCenterLayout();

    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(centralWidget);
    mainLayout->addWidget(bottomWidget);    
}

void NewDatasetView::setupTopLayout()
{
    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);

    topWidgetLayout->addWidget(datasetLabel);
    topWidgetLayout->addWidget(datasetLineEdit);
    topWidgetLayout->addWidget(labelInfo("Insert the name of Dataset.", topWidget));
}

void NewDatasetView::setupCenterLayout()
{
    QHBoxLayout *centralWidgetLayout = new QHBoxLayout(centralWidget);
    centralWidgetLayout->setSpacing(-1);
    centralWidgetLayout->setContentsMargins(10, 0, 10, 0);

    QVBoxLayout *subjectBoxLayout = new QVBoxLayout(subjectBox);
    subjectBoxLayout->setSpacing(-1);
    subjectBoxLayout->setContentsMargins(0, 5, 0, 0);
    subjectBoxLayout->addWidget(subjectTable);
    subjectBoxLayout->addWidget(labelInfo("Select the Group of Subject to associate to Dataset.\nWhen you click on Group the details are shown on the right.", subjectBox));
    centralWidgetLayout->addWidget(subjectBox);

    QVBoxLayout *protocolBoxLayout = new QVBoxLayout(protocolBox);
    protocolBoxLayout->setSpacing(-1);
    protocolBoxLayout->setContentsMargins(0, 5, 0, 0);
    protocolBoxLayout->addWidget(protocolTable);
    protocolBoxLayout->addWidget(labelInfo("Select the Protocols to associate to Dataset.\nWhen you click on Protocol the details of last Protocol selected are shown on the right.", protocolBox));
    centralWidgetLayout->addWidget(protocolBox);

    QVBoxLayout *detailsBoxLayout = new QVBoxLayout(detailsBox);
    detailsBoxLayout->setSpacing(-1);
    detailsBoxLayout->setContentsMargins(0, 5, 0, 0);
    centralWidgetLayout->addWidget(detailsBox);

    QVBoxLayout *detailSubjectScrollAreaWidgetLayout = new QVBoxLayout(detailSubjectScrollAreaWidget);    
    detailSubjectScrollAreaWidgetLayout->setSpacing(-1);
    detailSubjectScrollAreaWidgetLayout->setContentsMargins(5, 5, 5, 5);
    detailSubjectScrollAreaWidgetLayout->addWidget(labelInfo("Details of the Group selected", detailSubjectScrollAreaWidget));
    detailSubjectScrollAreaWidgetLayout->addWidget(detailSubject);
    detailSubjectScrollArea->setWidget(detailSubjectScrollAreaWidget);
    detailsBoxLayout->addWidget(detailSubjectScrollArea);

    QVBoxLayout *detailProtocolScrollAreaWidgetLayout = new QVBoxLayout(detailProtocolScrollAreaWidget);
    detailProtocolScrollAreaWidgetLayout->setSpacing(-1);
    detailProtocolScrollAreaWidgetLayout->setContentsMargins(5, 5, 5, 5);
    detailProtocolScrollAreaWidgetLayout->addWidget(labelInfo("Details of the last Protocol selected", detailProtocolScrollAreaWidget));
    detailProtocolScrollAreaWidgetLayout->addWidget(detailProtocol);
    detailProtocolScrollArea->setWidget(detailProtocolScrollAreaWidget);
    detailsBoxLayout->addWidget(detailProtocolScrollArea);

    centralWidgetLayout->setStretch(0,1);
    centralWidgetLayout->setStretch(1,1);
    centralWidgetLayout->setStretch(2,1);
}

void NewDatasetView::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/datasets.css");
    setStyleSheet(styleSheet);
}

void NewDatasetView::setupObjectName()
{
    setObjectName("NewDatasetView");
        topWidget->setObjectName("topWidget");
            datasetLabel->setObjectName("datasetLabel");
            datasetLineEdit->setObjectName("datasetLineEdit");

        centralWidget->setObjectName("centralWidget");
            subjectBox->setObjectName("subjectBox");
                subjectTable->setObjectName("subjectTable");
            protocolBox->setObjectName("protocolBox");
                protocolTable->setObjectName("protocolTable");
            detailsBox->setObjectName("detailsBox");
                detailSubjectScrollArea->setObjectName("detailSubjectScrollArea");
                    detailSubjectScrollAreaWidget->setObjectName("detailSubjectScrollAreaWidget");
                        detailSubject->setObjectName("detailSubject");
                detailProtocolScrollArea->setObjectName("detailProtocolScrollArea");
                    detailProtocolScrollAreaWidget->setObjectName("detailProtocolScrollAreaWidget");
                        detailProtocol->setObjectName("detailProtocol");
}

void NewDatasetView::setupToolTip()
{

}

void NewDatasetView::addConnect() const
{
    connect(subjectTable, SIGNAL(clicked(QModelIndex)), this, SIGNAL(groupSelected(QModelIndex)));
    connect(protocolTable, SIGNAL(clicked(QModelIndex)), this, SIGNAL(protocolSelected(QModelIndex)));
}

void NewDatasetView::setupView()
{
    createTop();
    createCenter();
    createBottom();
}

QTableView *NewDatasetView::getGroupsTable() const {
    return subjectTable;
}

QTableView *NewDatasetView::getProtocolsTable() const {
    return protocolTable;
}

QLabel *NewDatasetView::getGroupInfoLabel() const {
    return detailSubject;
}

QLabel *NewDatasetView::getProtocolInfoLabel() const {
    return detailProtocol;
}

void NewDatasetView::setGroupInfo(const QString& txt) {
    detailSubject->clear();
    detailSubject->setText(txt);
}

void NewDatasetView::setProtocolInfo(const QString& txt) {
    detailProtocol->clear();
    detailProtocol->setText(txt);
}

QString NewDatasetView::getName() const {
    return datasetLineEdit->text();
}

QModelIndex NewDatasetView::getGroupSelected() const {
    return subjectTable->currentIndex();
}

QModelIndexList NewDatasetView::getProtocolsSelected() const {
    QItemSelectionModel* selectedModel = protocolTable->selectionModel();
    return selectedModel->selectedRows();
}

void NewDatasetView::resetFields() {
    datasetLineEdit->clear();
    modelGroups->resetDatasetModel();
    modelProtocols->resetDatasetModel();
    resetInfo();
}

void NewDatasetView::resetInfo() {
    detailSubject->clear();
    detailProtocol->clear();
}

void NewDatasetView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}

void NewDatasetView::setEditFields(Dataset* dataset) {
    MainWindow::getMainWindow()->setWindowTitle("Edit Dataset - ROMEO");
    datasetLineEdit->setText(dataset->getName());
    datasetLineEdit->setEnabled(false);
}
