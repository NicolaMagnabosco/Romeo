#include "protocolsview.h"

using Romeo::View::Window::ProtocolsView;

ProtocolsView::ProtocolsView(QWidget *parent) : APanel(parent) {
    MainWindow::getMainWindow()->setWindowTitle("Protocols - ROMEO");
    initializeView();
}

void ProtocolsView::createTop() {

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    topWidget = new QWidget(this);

    tableWidget = new QWidget(topWidget);

    tableView = new QTableView(tableWidget);
    tableView->setSizePolicy(sizePolicy);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setTabKeyNavigation(false);
    tableView->setProperty("showDropIndicator", QVariant(false));
    tableView->setDragDropOverwriteMode(false);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setCornerButtonEnabled(false);
    tableView->horizontalHeader()->setHighlightSections(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

    model= new ProtocolTableModel();

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    tableView->setModel(proxyModel);
    tableView->setSortingEnabled(true);
    tableView->resizeColumnsToContents();

    infoBox = new QGroupBox(topWidget);
    infoBox->setSizePolicy(sizePolicy);
    infoBox->setTitle("Details");

    algorithmInfoScrollArea=new QScrollArea(infoBox);
    algorithmInfoScrollArea->setFrameShape(QFrame::NoFrame);
    algorithmInfoScrollArea->setWidgetResizable(true);

    algorithmInfoWidget=new QWidget();
    algorithmInfo=new QLabel(algorithmInfoWidget);
    algorithmInfo->setAlignment(Qt::AlignTop);

    featureInfoScrollArea=new QScrollArea(infoBox);
    featureInfoScrollArea->setFrameShape(QFrame::NoFrame);
    featureInfoScrollArea->setWidgetResizable(true);

    featureInfoWidget=new QWidget();
    featureInfo = new QLabel(featureInfoWidget);
    featureInfo->setAlignment(Qt::AlignTop);
}

void ProtocolsView::createBottom() {

    bottomWidget = new NavWidget(NavWidget::_BACK_EDIT_DELETE, this);
}

void ProtocolsView::setupLayout() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //space between top and bottom block
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(bottomWidget);
    setupTopLayout();
}

void ProtocolsView::setupTopLayout() {

    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);
    topWidgetLayout->addWidget(tableWidget);
    topWidgetLayout->addWidget(infoBox);

    QVBoxLayout *tableWidgetLayout = new QVBoxLayout(tableWidget);
    tableWidgetLayout->setSpacing(-1);
    tableWidgetLayout->setContentsMargins(0, 0, 0, 0);
    if(model->rowCount() == 0) {
        tableWidgetLayout->addWidget(labelEmpty("There are no Protocols. Create one!", tableWidget));
        bottomWidget->setEnableEdit(false);
        bottomWidget->setEnableDelete(false);
    }
    tableWidgetLayout->addWidget(tableView);
    tableWidgetLayout->addWidget(labelInfo("List of Protocols.\nSelect a Protocol to show details.", tableWidget));

    QVBoxLayout *infoBoxLayout = new QVBoxLayout(infoBox);
    infoBoxLayout->setSpacing(-1);
    infoBoxLayout->setContentsMargins(10, 10, 10, 10);
    infoBoxLayout->addWidget(algorithmInfoScrollArea);
    infoBoxLayout->addWidget(featureInfoScrollArea);

    QVBoxLayout *algorithmInfoWidgetLayout = new QVBoxLayout(algorithmInfoWidget);
    algorithmInfoWidgetLayout->setSpacing(-1);
    algorithmInfoWidgetLayout->setContentsMargins(5, 5, 5, 5);
    algorithmInfoWidgetLayout->addWidget(labelInfo("Details of Algorithm", algorithmInfoWidget));
    algorithmInfoWidgetLayout->addWidget(algorithmInfo);
    algorithmInfoScrollArea->setWidget(algorithmInfoWidget);

    QVBoxLayout *protocolInfoWidgetLayout= new QVBoxLayout(featureInfoWidget);
    protocolInfoWidgetLayout->setSpacing(-1);
    protocolInfoWidgetLayout->setContentsMargins(5, 5, 5, 5);
    protocolInfoWidgetLayout->addWidget(labelInfo("Details of Features", featureInfoWidget));
    protocolInfoWidgetLayout->addWidget(featureInfo);
    featureInfoScrollArea->setWidget(featureInfoWidget);
}

void ProtocolsView::loadCss() {

    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/protocols.css");
    setStyleSheet(styleSheet);
}

void ProtocolsView::setupObjectName() {

    setObjectName("ProtocolsView");
        topWidget->setObjectName("topWidget");
            tableView->setObjectName("tableView");
            infoBox->setObjectName("infoBox");
                algorithmInfoScrollArea->setObjectName("algorithmInfoScrollArea");
                    algorithmInfoWidget->setObjectName("algorithmInfoWidget");
                        algorithmInfo->setObjectName("algorithmInfo");
                featureInfoScrollArea->setObjectName("featureInfoScrollArea");
                featureInfoWidget->setObjectName("featureInfoWidget");
                featureInfo->setObjectName("featureInfo");
}

void ProtocolsView::setupToolTip() {

}

void ProtocolsView::addConnect() const {
    connect(tableView, SIGNAL(clicked(QModelIndex)), this, SIGNAL(protocolSelected(QModelIndex)));
}

void ProtocolsView::setupView() {

    createTop();
    createBottom();
}

QTableView *ProtocolsView::getProtocolsTable() const {
    return tableView;
}

QScrollArea *ProtocolsView::getAlgorithmBox() const {
    return algorithmInfoScrollArea;
}

QLabel *ProtocolsView::getAlgorithmLabel() const{
    return algorithmInfo;
}

QScrollArea *ProtocolsView::getFeatureBox() const {
    return featureInfoScrollArea;
}

QLabel *ProtocolsView::getFeatureLabel() const {
    return featureInfo;
}

void ProtocolsView::resetProtocolInfo() {
    algorithmInfo->clear();
    featureInfo->clear();
}

void ProtocolsView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}
