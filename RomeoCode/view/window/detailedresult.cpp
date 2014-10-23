#include "detailedresult.h"

using Romeo::View::Window::DetailedResult;
using Romeo::View::Component::ImageLabel;

DetailedResult::DetailedResult(QWidget *parent) : APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("Detailed Results - ROMEO");
    initializeView();
}

void DetailedResult::createTop()
{
    title = new QLabel();

    topWidget = new QWidget(this);
    treeView = new QTreeView(topWidget);

    modelTree = new QFileSystemModel(this);
    treeView->setModel(modelTree);
    treeView->header()->resizeSection(0, 350);

    scrollArea = new QScrollArea(topWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setObjectName("scrollArea");
}

void DetailedResult::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_EXPORT, this);
}

void DetailedResult::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(-1);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->addWidget(title);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(labelInfo("To see the Results you need to click twice or expand the folder of the Subject, then select the folder of the Protocol.\nWill appear on the right the images related to the Features and Algorithms for the selected Protocol.\nTo enlarge a picture just click on it twice.", this));
    mainLayout->addWidget(bottomWidget);

    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(0, 0, 0, 0);    
    topWidgetLayout->addWidget(treeView);
    topWidgetLayout->addWidget(scrollArea);
    topWidgetLayout->setStretch(0, 7);
    topWidgetLayout->setStretch(1, 10);    
}

void DetailedResult::setupView()
{
    createTop();
    createBottom();
}

void DetailedResult::setupObjectName()
{
    setObjectName("DetailedResult");
    treeView->setObjectName("treeView");

}

void DetailedResult::setupToolTip()
{
    connect(treeView, SIGNAL(clicked(QModelIndex)), this, SIGNAL(treeClicked(QModelIndex)));
}

void DetailedResult::loadCss()
{
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/results.css");
    setStyleSheet(styleSheet);
}

void DetailedResult::addConnect() const
{

}

void DetailedResult::setTreePath(const QString& path)
{
    QDir dir;
    if(dir.exists(path)) {
        modelTree->setRootPath(path);
        treeView->setRootIndex(modelTree->index(path));
        modelTree->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    }
    else {
        QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(this->layout());
        layout->insertWidget(0,labelEmpty("There are no Results on this analysis!", this));
    }
}

QFileSystemModel *DetailedResult::getModelTree()
{
    return modelTree;
}

void DetailedResult::generateImages(const QString& path)
{
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
    scrollArea->setWidget(scrollAreaWidgetContents);

    int spacing = 10;

    QGridLayout *scrollAreaLayout = new QGridLayout(scrollAreaWidgetContents);
    scrollAreaLayout->setSpacing(spacing);
    scrollAreaLayout->setContentsMargins(spacing, spacing, spacing, spacing);

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList();

    int column = 2;
    int rowCount = 0;
    int columnCount = 0;
    int dimension = (scrollAreaWidgetContents->width()/column)-(spacing*(column+1));

    for(int i=0; i<list.size(); ++i) {
        if(list.at(i).isFile()) {
            QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            sizePolicy.setHorizontalStretch(0);
            sizePolicy.setVerticalStretch(0);

            QWidget *widget = new QWidget(scrollAreaWidgetContents);
            widget->setObjectName("widget");
            widget->setSizePolicy(sizePolicy);
            widget->setMinimumWidth(dimension);
            widget->setMaximumWidth(dimension);

            QString path = list.at(i).absoluteFilePath();
            ImageLabel *img = new ImageLabel(path, widget);
            img->setObjectName("img");
            img->setSizePolicy(sizePolicy);
            QImage image;

            if(list.at(i).fileName().endsWith(".nii") || list.at(i).fileName().endsWith(".hdr") || list.at(i).fileName().endsWith(".avi") || list.at(i).fileName().endsWith(".mpg")) {
                image = *getImage3DVideo(path);
            }
            else
                image = QImage(path);

            img->setImage(image, dimension);

            connect(img, SIGNAL(signalDoubleClicked(QString)), this, SIGNAL(ImageDoubleClicked(QString)));

            QLabel *txt = new QLabel(list.at(i).fileName());
            txt->setObjectName("txt");
            txt->setSizePolicy(sizePolicy);

            QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
            widgetLayout->setSpacing(0);
            widgetLayout->setContentsMargins(0, 0, 0, 0);
            widgetLayout->addWidget(img);
            widgetLayout->addWidget(txt);

            if(columnCount<column) {
                scrollAreaLayout->addWidget(widget, rowCount, columnCount);
                columnCount++;
            }
            else {
                columnCount = 0;
                rowCount++;
                scrollAreaLayout->addWidget(widget, rowCount, columnCount);
                columnCount++;
            }

            imageWidgetLit.append(widget);
        }        
    }

}

void DetailedResult::setpageTitle(const QString& txt)
{
    title->setText(txt);
}
