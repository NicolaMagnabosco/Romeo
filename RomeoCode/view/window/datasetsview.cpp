#include "datasetsview.h"

using Romeo::View::Window::DatasetsView;

DatasetsView::DatasetsView(QWidget *parent) : APanel(parent) {
    MainWindow::getMainWindow()->setWindowTitle("Datasets - ROMEO");
    initializeView();
}

void DatasetsView::createTop() {

    topWidget = new QWidget(this);

    tableWidget = new QWidget(topWidget);

    datasetsTable = new QTableView(tableWidget);
    datasetsTable->setLineWidth(1);
    datasetsTable->setTabKeyNavigation(false);
    datasetsTable->setProperty("showDropIndicator", QVariant(false));
    datasetsTable->setDragDropOverwriteMode(false);
    datasetsTable->setAlternatingRowColors(true);
    datasetsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    datasetsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    datasetsTable->setCornerButtonEnabled(false);
    datasetsTable->horizontalHeader()->setHighlightSections(false);
    datasetsTable->horizontalHeader()->setStretchLastSection(true);
    datasetsTable->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

    model= new DatasetsTableModel();

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);    

    datasetsTable->setModel(proxyModel);
    datasetsTable->setSortingEnabled(true);
    datasetsTable->horizontalHeader()->setDefaultSectionSize(200);
    datasetsTable->resizeColumnsToContents();

    detailTabWidget = new QTabWidget(topWidget);
        groupTabScrollArea = new QScrollArea(detailTabWidget);
        groupTabScrollArea->setWidgetResizable(true);
            groupTabWidget = new QWidget();
                groupInfo = new QLabel(groupTabWidget);
                groupInfo->setAlignment(Qt::AlignTop);
                setGroupInfo("Select a Dataset to view this informations");
        protocolScrollArea = new QScrollArea(detailTabWidget);
        protocolScrollArea->setWidgetResizable(true);
            protocolTabWidget = new QWidget();
                protocolInfo = new QLabel(protocolTabWidget);
                protocolInfo->setAlignment(Qt::AlignTop);
                setProtocolsInfo("Select a Dataset to view this informations");
}

void DatasetsView::createBottom() {

    bottomWidget = new NavWidget(NavWidget::_BACK_DELETE, this);
}

void DatasetsView::setupLayout() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(bottomWidget);
    setupTopLayout();
}

void DatasetsView::setupTopLayout() {

    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);
    topWidgetLayout->addWidget(tableWidget);
    topWidgetLayout->addWidget(detailTabWidget);

    QVBoxLayout *tableWidgetLayout = new QVBoxLayout(tableWidget);
    tableWidgetLayout->setSpacing(-1);
    tableWidgetLayout->setContentsMargins(0, 0, 0, 0);
    if(model->rowCount() == 0) {
        tableWidgetLayout->addWidget(labelEmpty("There are no Datasets. Create one!", tableWidget));
        bottomWidget->setEnableDelete(false);
    }
    tableWidgetLayout->addWidget(datasetsTable);
    tableWidgetLayout->addWidget(labelInfo("List of Datasets.\nClick on a Dataset to view details.", tableWidget));

    QVBoxLayout *groupTabWidgetLayout = new QVBoxLayout(groupTabWidget);
    groupTabWidgetLayout->setSpacing(-1);
    groupTabWidgetLayout->setContentsMargins(5, 5, 5, 5);
    groupTabWidgetLayout->addWidget(groupInfo);

    QVBoxLayout *protocolTabWidgetLayout = new QVBoxLayout(protocolTabWidget);
    protocolTabWidgetLayout->setSpacing(-1);
    protocolTabWidgetLayout->setContentsMargins(5, 5, 5, 5);
    protocolTabWidgetLayout->addWidget(protocolInfo);

    detailTabWidget->addTab(groupTabScrollArea, tr("Group Of Subjects"));
    detailTabWidget->addTab(protocolScrollArea, tr("Protocols"));

    protocolScrollArea->setWidget(protocolTabWidget);
    groupTabScrollArea->setWidget(groupTabWidget);
}

void DatasetsView::loadCss() {

    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/datasets.css");
    setStyleSheet(styleSheet);
}

void DatasetsView::setupObjectName() {
    setObjectName("DatasetsView");
        topWidget->setObjectName("topWidget");
            datasetsTable->setObjectName("datasetsTable");
            detailTabWidget->setObjectName("detailTabWidget");
                groupTabScrollArea->setObjectName("groupTabScrollArea");
                    groupTabWidget->setObjectName("groupTabWidget");
                        groupInfo->setObjectName("groupInfo");
                protocolScrollArea->setObjectName("protocolScrollArea");
                    protocolTabWidget->setObjectName("protocolTabWidget");
                        protocolInfo->setObjectName("protocolInfo");
}

void DatasetsView::setupToolTip() {

}

void DatasetsView::addConnect() const {
    connect(datasetsTable, SIGNAL(clicked(QModelIndex)), this, SIGNAL(itemSelected(QModelIndex)));
}

void DatasetsView::setupView() {

    createTop();
    createBottom();
}

QTableView * DatasetsView::getDatasetTable() const {
    return datasetsTable;
}

void DatasetsView::setGroupInfo(const QString& txt) {
    groupInfo->clear();
    groupInfo->setText(txt);
}

void DatasetsView::setProtocolsInfo(const QString& txt) {
    protocolInfo->clear();
    protocolInfo->setText(txt);
}

void DatasetsView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}

void DatasetsView::resetDatasetInfo() {
    groupInfo->clear();
    groupInfo->setText("Select a Dataset to view this informations");
    protocolInfo->clear();
    protocolInfo->setText("Select a Dataset to view this informations");
}
