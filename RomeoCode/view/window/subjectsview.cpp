#include "subjectsview.h"

using Romeo::View::Window::SubjectsView;

SubjectsView::SubjectsView(QWidget *parent) : APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("Subjects - ROMEO");
    initializeView();
}

void SubjectsView::setupView()
{
    createTop();
    createBottom();
}

void SubjectsView::createTop()
{
    topWidget = new QWidget(this);

    setupTable();
    setupInfoBlock();
}

void SubjectsView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_ONLY_BACK, this);
}

void SubjectsView::setupLayout()
{
    QVBoxLayout *widgetLayout = new QVBoxLayout(this);
    widgetLayout->setSpacing(-1);
    widgetLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setStretch(0, 1);
    topWidgetLayout->setStretch(1, 1);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout * tableWidgetLayout = new QVBoxLayout(tableWidget);
    tableWidgetLayout->setSpacing(-1);
    tableWidgetLayout->setContentsMargins(0, 0, 0, 0);
    if(model->rowCount() == 0) tableWidgetLayout->addWidget(labelEmpty("There are no Subjects. Create one!", tableWidget));
    tableWidgetLayout->addWidget(tableView);
    tableWidgetLayout->addWidget(labelInfo("List of Subjects.\nClick on a Subject to view details.\nTo enlarge a picture just click on it twice.", tableWidget));

    //add top widget
    widgetLayout->addWidget(topWidget);

    //add table to top block
    topWidgetLayout->addWidget(tableWidget);

    //add image widget to info block
    QVBoxLayout *imgWidgetLayout = new QVBoxLayout(imgWidget);
    QLabel *lab1 = labelInfo("Image of the Subject", imgWidget);
    lab1->setMinimumHeight(15);
    lab1->setMaximumHeight(15);
    imgWidgetLayout->addWidget(lab1);
    imgWidgetLayout->addWidget(subjectImg);
    imgWidgetLayout->setSpacing(-1);
    imgWidgetLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *maskWidgetLayout = new QVBoxLayout(maskWidget);
    QLabel *lab2 = labelInfo("Mask of the Subject", maskWidget);
    lab2->setMinimumHeight(15);
    lab2->setMaximumHeight(15);
    maskWidgetLayout->addWidget(lab2);
    maskWidgetLayout->addWidget(subjectMask);
    maskWidgetLayout->setSpacing(-1);
    maskWidgetLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *infoBoxLayout = new QVBoxLayout(infoBox);
    infoBoxLayout->addWidget(imgScrollArea);
    infoBoxLayout->setSpacing(-1);
    infoBoxLayout->setContentsMargins(0, 5, 0, 0);

    QHBoxLayout *imgContainerLayout = new QHBoxLayout(imgContainer);
    imgContainerLayout->setSpacing(-1);
    imgContainerLayout->setContentsMargins(5, 5, 5, 5);
    imgContainerLayout->addWidget(imgWidget);
    imgContainerLayout->addWidget(maskWidget);
    imgContainerLayout->setStretch(0,1);
    imgContainerLayout->setStretch(1,1);
    imgScrollArea->setWidget(imgContainer);

    //add text informations to info block
    QVBoxLayout *infoWidgetlayout = new QVBoxLayout(infoWidget);
    infoWidgetlayout->addWidget(infoTxt);    
    infoWidgetlayout->setSpacing(-1);
    infoWidgetlayout->setContentsMargins(5, 5, 5, 5);
    infoScrollArea->setWidget(infoWidget);
    infoBoxLayout->addWidget(infoScrollArea);

    //add info block to top block
    topWidgetLayout->addWidget(infoBox);

    //add bottom widget
    widgetLayout->addWidget(bottomWidget);
}

void SubjectsView::setupTable()
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    tableWidget = new QWidget(topWidget);

    tableView = new QTableView(tableWidget);
    tableView->setSizePolicy(sizePolicy);
    tableView->setLineWidth(1);
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

    model = new SubjectTableModel(this);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    tableView->setModel(proxyModel);
    tableView->setSortingEnabled(true);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->resizeSection(2, 45);
    tableView->horizontalHeader()->resizeSection(1, 50);
}

void SubjectsView::setupInfoBlock()
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    infoBox = new QGroupBox(topWidget);
        imgScrollArea = new QScrollArea(infoBox);
            imgContainer = new QWidget(imgScrollArea);
                imgWidget = new QWidget(imgContainer);
                    subjectImg = new ImageLabel("", imgWidget);
                    subjectImg->setAlignment(Qt::AlignTop);
                maskWidget = new QWidget(imgContainer);
                    subjectMask = new ImageLabel("", maskWidget);
                    subjectMask->setAlignment(Qt::AlignTop);
        infoScrollArea = new QScrollArea(infoBox);
            infoWidget = new QWidget(infoScrollArea);
                infoTxt = new QLabel(infoWidget);
                infoTxt->setAlignment(Qt::AlignTop);

    infoBox->setTitle("Details");

    infoBox->setSizePolicy(sizePolicy);
    imgScrollArea->setFrameShape(QFrame::NoFrame);
    imgScrollArea->setWidgetResizable(true);

    infoScrollArea->setFrameShape(QFrame::NoFrame);
    infoScrollArea->setWidgetResizable(true);
}

void SubjectsView::setupObjectName()
{
    setObjectName("SubjectsView");

        topWidget->setObjectName("topWidget");
            tableView->setObjectName("tableView");
            infoBox->setObjectName("infoBox");
                imgScrollArea->setObjectName("imgScrollArea");
                    imgWidget->setObjectName("imgWidget");
                        subjectImg->setObjectName("subjectImg");
                    maskWidget->setObjectName("maskWidget");
                        subjectMask->setObjectName("subjectMask");
                infoScrollArea->setObjectName("infoScrollArea");
                    infoWidget->setObjectName("infoWidget");
                        infoTxt->setObjectName("infoTxt");   
}

void SubjectsView::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/subjects.css");
    setStyleSheet(styleSheet);
}

void SubjectsView::setupToolTip()
{

}

void SubjectsView::addConnect() const
{
    connect(tableView, SIGNAL(clicked(QModelIndex)), this, SIGNAL(itemSelected(QModelIndex)));
    connect(subjectImg, SIGNAL(signalDoubleClicked(QString)), this, SIGNAL(ImageDoubleClicked(QString)));
    connect(subjectMask, SIGNAL(signalDoubleClicked(QString)), this, SIGNAL(MaskDoubleClicked(QString)));
}

QTableView * SubjectsView::getTableView() const
{
    return tableView;
}

void SubjectsView::setSubjectImgs(const QImage& image, const QImage& mask, const QString& pathI, const QString& pathM)
{
    if(!pathI.isEmpty())
        subjectImg->setPath(pathI);

    if(!pathM.isEmpty())
        subjectMask->setPath(pathM);

    subjectImg->setPixmap(QPixmap::fromImage(image.scaled(subjectImg->width(), subjectImg->height(), Qt::KeepAspectRatio)));
    subjectMask->setPixmap(QPixmap::fromImage(mask.scaled(subjectMask->width(), subjectMask->height(), Qt::KeepAspectRatio)));
}

void SubjectsView::setSubjectInfo(const QString& txt)
{
    infoTxt->setText(txt);
}
