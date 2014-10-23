#include "resultsview.h"

using Romeo::View::Window::ResultsView;

ResultsView::ResultsView(QWidget *parent) : APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("Analysis Results - ROMEO");
    initializeView();
}

void ResultsView::createTop()
{
    tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setTabKeyNavigation(false);
    tableView->setProperty("showDropIndicator", QVariant(false));
    tableView->setDragDropOverwriteMode(false);
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setCornerButtonEnabled(false);
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setHighlightSections(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);

    model = new ResultsTableModel(this);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    tableView->setModel(proxyModel);

    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->resizeSection(4, 150);
}

void ResultsView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_RESTART_SHOW, this);
    bottomWidget->setEnableRestart(false);
    bottomWidget->setEnableShow(false);
}

void ResultsView::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    if(model->rowCount() == 0) mainLayout->addWidget(labelEmpty("There are no Analysis Results!", this));
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(labelInfo("To show the results of an Analysis or restart it you have to select an Analysis in the table above and then click on the button \"Show\" or \"Restart\".\nTo show the results of an Analysis you can also click twice on the Analysis.", this));
    mainLayout->addWidget(bottomWidget);
}

void ResultsView::setupView()
{
    createTop();
    createBottom();
}

void ResultsView::setupObjectName()
{
    setObjectName("ResultsView");
    tableView->setObjectName("tableView");
    bottomWidget->setObjectName("bottomWidget");
}

void ResultsView::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/results.css");
    setStyleSheet(styleSheet);
}

void ResultsView::setupToolTip()
{

}

void ResultsView::addConnect() const
{
    connect(tableView, SIGNAL(clicked(QModelIndex)), this, SIGNAL(rowSelected(QModelIndex)));
    connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SIGNAL(rowSelectedDouble(QModelIndex)));
}

QAbstractItemModel *ResultsView::getModel() const
{
    return tableView->model();
}

void ResultsView::enableButtons()
{
    bottomWidget->setEnableRestart(true);
    bottomWidget->setEnableShow(true);
}
