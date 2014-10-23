#include "analysisview.h"

using Romeo::View::Window::AnalysisView;
using Romeo::Model::Util::DAO::DatasetDAO;
using Romeo::Model::QtModel::AnalysisSubjectsTableModel;

AnalysisView::AnalysisView(QWidget *parent) : APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("Analysis - ROMEO");
    initializeView();
}

void AnalysisView::createTop() {
    topWidget = new QWidget(this);
    createLeft();
    createRight();
}

void AnalysisView::createLeft() {
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    leftWidget = new QWidget(topWidget);

    if(!noDatasets) {
        datasetBox = new QWidget(leftWidget);
        datasetSelect = new QLabel("Dataset "+Utils::TXT_REQUIRED, datasetBox);
        datasetComboBox = new QComboBox(datasetBox);
        datasetComboBox->setSizePolicy(sizePolicy);
        setDatasetComboBox();
    }

    subjectsBox = new QGroupBox(leftWidget);
    subjectsBox->setTitle("Subjects "+Utils::TXT_REQUIRED);

    selDesel = new SelectDeselectWidget(this);

    subjectListView = new QTableView(subjectsBox);
    subjectListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    subjectListView->setTabKeyNavigation(false);
    subjectListView->setProperty("showDropIndicator", QVariant(false));
    subjectListView->setDragDropOverwriteMode(false);
    subjectListView->setAlternatingRowColors(true);
    subjectListView->setSelectionMode(QAbstractItemView::MultiSelection);
    subjectListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    subjectListView->setCornerButtonEnabled(false);
    subjectListView->horizontalHeader()->setHighlightSections(false);
    subjectListView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

    subjectTableModel= new AnalysisSubjectsTableModel();

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(subjectTableModel);
    subjectListView->setModel(proxyModel);
    subjectListView->setSortingEnabled(true);
    subjectListView->resizeColumnsToContents();
    subjectListView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    subjectListView->horizontalHeader()->resizeSection(1, 50);   
}

void AnalysisView::checkDatasets()
{
    DatasetDAO dao;
    QVector<QString> datasets = dao.getAllDatasetName();
    if(datasets.size() > 0)
        noDatasets = false;
    else
        noDatasets = true;
}

void AnalysisView::setDatasetComboBox()
{
    DatasetDAO dao;
    QVector<QString> datasets = dao.getAllDatasetName();

    datasets.push_front(Utils::ROMEO_SELECT_DATASET);
    QStringList datasetsList = datasets.toList();
    datasetComboBox->setModel(new QStringListModel(datasetsList, datasetComboBox));
}

void AnalysisView::createRight() {
    rightWidget = new QWidget(topWidget);

    buttonBox = new QGroupBox(rightWidget);
    buttonBox->setTitle("Features to Show and Save Selector");
    saverButton=new QPushButton("Save select/deselect All", buttonBox);
    viewerButton=new QPushButton("Show select/deselect All", buttonBox);

    selectorBox = new QWidget(rightWidget);
    selectorList = new QTableView(selectorBox);

    selectorList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    selectorList->setTabKeyNavigation(false);
    selectorList->setProperty("showDropIndicator", QVariant(false));
    selectorList->setDragDropOverwriteMode(false);
    selectorList->setAlternatingRowColors(true);
    selectorList->setSelectionMode(QAbstractItemView::NoSelection);
    selectorList->setCornerButtonEnabled(false);
    selectorList->horizontalHeader()->setHighlightSections(false);
    selectorList->horizontalHeader()->setStretchLastSection(false);

    protocolsTableModel= new AnalysisProtocolsTableModel(this);

    selectorList->setModel(protocolsTableModel);
    selectorList->resizeColumnsToContents();
    selectorList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    selectorList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    selectorList->horizontalHeader()->resizeSection(2, 70);
    selectorList->horizontalHeader()->resizeSection(3, 70);  

    pathWidget = new QWidget(rightWidget);
    pathBox = new QGroupBox(pathWidget);
    pathBox->setTitle("Destination folder "+Utils::TXT_REQUIRED);
    lineEdit = new QLineEdit(pathBox);
    lineEdit->setEnabled(false);
    searchButton = new QPushButton("Search..", pathBox);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    searchButton->setSizePolicy(sizePolicy);
}

void AnalysisView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_START_ANALYSIS, this);
}

void AnalysisView::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(bottomWidget);

    setupTopLayout();
}

void AnalysisView::setupTopLayout()
{
    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);
    topWidgetLayout->addWidget(leftWidget);
    topWidgetLayout->addWidget(rightWidget);
    topWidgetLayout->setStretch(0, 5);
    topWidgetLayout->setStretch(1, 10);

    setupLeftLayout();
    setupRightLayout();
}

void AnalysisView::setupLeftLayout()
{
    QVBoxLayout *leftWidgetLayout = new QVBoxLayout(leftWidget);
    leftWidgetLayout->setSpacing(-1);
    leftWidgetLayout->setContentsMargins(0, 0, 0, 0);
    if(noDatasets) {
        leftWidgetLayout->addWidget(labelEmpty("There are no Datasets. Create one!", leftWidget));
        bottomWidget->setEnableStartAnalysis(false);
        searchButton->setEnabled(false);
    }
    else {
        leftWidgetLayout->addWidget(datasetBox);
    }
    leftWidgetLayout->addWidget(subjectsBox);

    if(!noDatasets) {
        QVBoxLayout *datasetBoxLayout = new QVBoxLayout(datasetBox);
        datasetBoxLayout->setSpacing(1);
        datasetBoxLayout->setContentsMargins(0, 0, 0, 0);
        datasetBoxLayout->addWidget(datasetSelect);
        datasetBoxLayout->addWidget(datasetComboBox);
        datasetBoxLayout->addWidget(labelInfo("Select Dataset for the Analysis.", datasetBox));
    }

    QVBoxLayout *subjectsBoxLayout = new QVBoxLayout(subjectsBox);
    subjectsBoxLayout->setSpacing(1);
    subjectsBoxLayout->setContentsMargins(0, 10, 0, 0);
    subjectsBoxLayout->addWidget(selDesel);
    subjectsBoxLayout->addWidget(subjectListView);
    subjectsBoxLayout->addWidget(labelInfo("Select the Subjects for the Analysis.\nTo show this list you have to select the Dataset.", subjectsBox));
}

void AnalysisView::setupRightLayout()
{
    QVBoxLayout *rightWidgetLayout = new QVBoxLayout(rightWidget);
    rightWidgetLayout->setSpacing(-1);
    rightWidgetLayout->setContentsMargins(0, 0, 0, 0);
    rightWidgetLayout->addWidget(buttonBox);
    rightWidgetLayout->addWidget(selectorBox);
    rightWidgetLayout->addWidget(pathWidget);

    QHBoxLayout *buttonBoxLayout = new QHBoxLayout(buttonBox);
    buttonBoxLayout->setSpacing(-1);
    buttonBoxLayout->setContentsMargins(0, 10, 0, 0);
    buttonBoxLayout->addWidget(viewerButton);
    buttonBoxLayout->addWidget(saverButton);

    QVBoxLayout *selectorBoxLayout = new QVBoxLayout(selectorBox);
    selectorBoxLayout->setSpacing(-1);
    selectorBoxLayout->setContentsMargins(0, 0, 0, 0);
    selectorBoxLayout->addWidget(selectorList);
    selectorBoxLayout->addWidget(labelInfo("Select the Features you want to see and export during the Analysis.\nClick on the checkbox or on the cell of the checkbox .\nAll Algorithms will be shown and exported during the analysis.", selectorBox));

    QVBoxLayout *pathWidgetLayout = new QVBoxLayout(pathWidget);
    pathWidgetLayout->setSpacing(1);
    pathWidgetLayout->setContentsMargins(0, 0, 0, 0);
    pathWidgetLayout->addWidget(pathBox);
    pathWidgetLayout->addWidget(labelInfo("Select the destination folder where the Algorithms and selected Features will be exported.", pathWidget));

    QHBoxLayout *pathBoxLayout = new QHBoxLayout(pathBox);
    pathBoxLayout->setSpacing(-1);
    pathBoxLayout->setContentsMargins(0, 10, 0, 0);
    pathBoxLayout->addWidget(lineEdit);
    pathBoxLayout->addWidget(searchButton);
}

void AnalysisView::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/analysis.css");
    setStyleSheet(styleSheet);
}

void AnalysisView::setupObjectName()
{
    setObjectName("AnalysisView");
    buttonBox->setObjectName("buttonBox");
}

void AnalysisView::setupToolTip()
{

}

void AnalysisView::addConnect() const
{
    if(!noDatasets) connect(datasetComboBox, SIGNAL(currentTextChanged(QString)), this, SIGNAL(datasetSelected(QString)));
    connect(searchButton, SIGNAL(clicked()), this, SIGNAL(selectDestinationDirectory()));
    connect(selectorList, SIGNAL(clicked(QModelIndex)), this, SIGNAL(featureSelected(QModelIndex)));
    connect(viewerButton, SIGNAL(clicked()), this, SIGNAL(showAllSignal()));
    connect(saverButton, SIGNAL(clicked()), this, SIGNAL(saveAllSignal()));
}

void AnalysisView::setupView()
{
    checkDatasets();
    createTop();
    createBottom();
}

QTableView *AnalysisView::getSubjectsTable() const {
    return subjectListView;
}

QModelIndexList AnalysisView::getSubjectsSelected() const {
    QItemSelectionModel* selectedModel = subjectListView->selectionModel();
    return selectedModel->selectedRows();
}

QString AnalysisView::getDestinationFolder() const
{
    return lineEdit->text();
}

void AnalysisView::setDestinationFolder(const QString& folder) {
    lineEdit->setText(folder);
}

void AnalysisView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}

QTableView *AnalysisView::getProtocolsTable() const {
    return selectorList;
}

void AnalysisView::resetView() {
    subjectTableModel->resetModelData();
    protocolsTableModel->resetModelData();
    checkDatasets();

    lineEdit->clear();
    datasetComboBox->clear();
    datasetComboBox->setEnabled(true);
    setDatasetComboBox();
}

void AnalysisView::setRestartData(Analysis *analysis) {
    if(analysis) {
        QString dataset = analysis->getDataset()->getName();
        datasetComboBox->setCurrentText(dataset);
        datasetComboBox->setEnabled(false);

        QItemSelectionModel* selectionModel = new QItemSelectionModel(subjectListView->model());

        for(int i=0; i<subjectListView->model()->rowCount(); ++i) {
            QModelIndex indexLeft(subjectListView->model()->index(i, 0));
            QModelIndex indexRight(subjectListView->model()->index(i, subjectListView->model()->columnCount()-1));

            QVector<QString> selSubjs = analysis->getSelectedSubject();
            bool ok = false;
            for(int j=0; j<selSubjs.size() && !ok; ++j){
                if(selSubjs.at(j) == indexLeft.data().toString()) {
                    ok = true;
                    QItemSelection selectionRow(indexLeft, indexRight);
                    selectionModel->select(selectionRow, QItemSelectionModel::Select);
                }
            }
        }

        subjectListView->setSelectionModel(selectionModel);

    }
}
