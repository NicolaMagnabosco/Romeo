#include "newsubjectview.h"

using Romeo::View::Window::NewSubjectView;
using Romeo::View::Component::ResultMessageWidget;

NewSubjectView::NewSubjectView(QWidget *parent):APanel(parent) {

    initializeView();
    MainWindow::getMainWindow()->setWindowTitle("New Subject - ROMEO");
}

void NewSubjectView::createTop() {

    QSizePolicy policyContainer(QSizePolicy::Fixed, QSizePolicy::Preferred);
    policyContainer.setHorizontalStretch(0);
    policyContainer.setVerticalStretch(0);

    QSizePolicy policyLineEdit(QSizePolicy::Fixed, QSizePolicy::Fixed);
    policyLineEdit.setHorizontalStretch(0);
    policyLineEdit.setVerticalStretch(0);

    QSizePolicy policyGroupBox(QSizePolicy::Preferred, QSizePolicy::Fixed);
    policyGroupBox.setHorizontalStretch(0);
    policyGroupBox.setVerticalStretch(0);

    groupBox = new QGroupBox(this);
    groupBox->setSizePolicy(policyGroupBox);

        nameBox = new QWidget(groupBox);
            subjectLabel = new QLabel("Subject Name "+Utils::TXT_REQUIRED,nameBox);
            subjectLineEdit = new  QLineEdit(nameBox);
            subjectLineEdit->setSizePolicy(policyLineEdit);
            subjectLineEdit->setMinimumWidth(400);

        typeBox = new QWidget(groupBox);
            typeLabel = new QLabel("Type "+Utils::TXT_REQUIRED, typeBox);
            typeComboBox = new QComboBox(typeBox);
            typeComboBox->setModel(APanel::getTypeRomeo(typeComboBox));
            typeComboBox->setSizePolicy(policyLineEdit);

        fileBox = new QWidget(groupBox);
            fileLabel = new QLabel("Add File "+Utils::TXT_REQUIRED,fileBox);
            fileContainer = new QWidget(fileBox);
            fileContainer->setSizePolicy(policyContainer);
                imageLineEdit = new QLineEdit(fileContainer);
                imageLineEdit->setEnabled(false);
                imageLineEdit->setSizePolicy(policyLineEdit);
                imageLineEdit->setMinimumWidth(400);
                searchFileButton = new QPushButton(fileContainer);
                searchFileButton->setText(tr("Search.."));
                searchFileButton->setEnabled(false);
                searchFileButton->setSizePolicy(policyLineEdit);

        maskBox = new QWidget(groupBox);
             maskLabel = new QLabel("Add Mask "+Utils::TXT_OPTIONAL,maskBox);
             maskContainer = new QWidget(maskBox);
             maskContainer->setSizePolicy(policyContainer);
                 maskLineEdit = new QLineEdit(maskContainer);
                 maskLineEdit->setEnabled(false);
                 maskLineEdit->setSizePolicy(policyLineEdit);
                 maskLineEdit->setMinimumWidth(400);
                 searchMaskButton = new QPushButton(maskContainer);
                 searchMaskButton->setText(tr("Search.."));
                 searchMaskButton->setEnabled(false);
                 searchMaskButton->setSizePolicy(policyLineEdit);
}

void NewSubjectView::createBottom() {

    bottomWidget = new NavWidget(NavWidget::_BACK_SAVE, this);
}

void NewSubjectView::setupLayout() {
   QVBoxLayout *mainWidgetLayout = new QVBoxLayout(this);
   mainWidgetLayout->setSpacing(-1);
   mainWidgetLayout->setContentsMargins(0, 0, 0, 0);
   mainWidgetLayout->addWidget(groupBox);
   mainWidgetLayout->addWidget(bottomWidget);

   QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);
   groupBoxLayout->setSpacing(20);
   groupBoxLayout->setContentsMargins(10, 10, 10, 10);
   groupBoxLayout->addWidget(nameBox, 0, Qt::AlignHCenter);
   groupBoxLayout->addWidget(typeBox, 0, Qt::AlignHCenter);
   groupBoxLayout->addWidget(fileBox, 0, Qt::AlignHCenter);
   groupBoxLayout->addWidget(maskBox, 0, Qt::AlignHCenter);

   QVBoxLayout *nameBoxLayout = new QVBoxLayout(nameBox);
   nameBoxLayout->setSpacing(1);
   nameBoxLayout->setContentsMargins(0, 0, 0, 0);
   nameBoxLayout->addWidget(subjectLabel);
   nameBoxLayout->addWidget(subjectLineEdit);
   nameBoxLayout->addWidget(labelInfo("Insert the name of the subject.", nameBox));

   QVBoxLayout *typeBoxLayout = new QVBoxLayout(typeBox);
   typeBoxLayout->setSpacing(1);
   typeBoxLayout->setContentsMargins(0, 0, 0, 0);
   typeBoxLayout->addWidget(typeLabel);
   typeBoxLayout->addWidget(typeComboBox);
   typeBoxLayout->addWidget(labelInfo("Select the type of image.", typeBox));

   QVBoxLayout *fileBoxLayout = new QVBoxLayout(fileBox);
   fileBoxLayout->setSpacing(1);
   fileBoxLayout->setContentsMargins(0, 0, 0, 0);
   fileBoxLayout->addWidget(fileLabel);
   fileBoxLayout->addWidget(fileContainer);
   fileBoxLayout->addWidget(labelInfo("Select the image to associate subject.", fileBox));

   QVBoxLayout *maskBoxLayout = new QVBoxLayout(maskBox);
   maskBoxLayout->setSpacing(1);
   maskBoxLayout->setContentsMargins(0, 0, 0, 0);
   maskBoxLayout->addWidget(maskLabel);
   maskBoxLayout->addWidget(maskContainer);
   maskBoxLayout->addWidget(labelInfo("Select mask to apply image.", maskBox));

   QHBoxLayout *fileContainerLayout = new QHBoxLayout(fileContainer);
   fileContainerLayout->setSpacing(-1);
   fileContainerLayout->setContentsMargins(0, 0, 0, 0);
   fileContainerLayout->addWidget(imageLineEdit);
   fileContainerLayout->addWidget(searchFileButton);

   QHBoxLayout *maskContainerLayout = new QHBoxLayout(maskContainer);
   maskContainerLayout->setSpacing(-1);
   maskContainerLayout->setContentsMargins(0, 0, 0, 0);
   maskContainerLayout->addWidget(maskLineEdit);
   maskContainerLayout->addWidget(searchMaskButton);
}


//load the css of new subject widget
void NewSubjectView::loadCss() {

    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/subjects.css");
    setStyleSheet(styleSheet);
}

void NewSubjectView::setupObjectName() {

    setObjectName("NewSubjectView");

    groupBox->setObjectName("groubBox");

    subjectLabel->setObjectName("subjectLabel");
    subjectLineEdit->setObjectName("subjectLineEdit");

    typeLabel->setObjectName("typeLabel");
    typeComboBox->setObjectName("typeComboBox");

    fileContainer->setObjectName("fileContainer");
    fileLabel->setObjectName("fileLabel");
    imageLineEdit->setObjectName("imageLineEdit");
    searchFileButton->setObjectName("searchFileButton");

    maskContainer->setObjectName("maskContainer");
    maskLabel->setObjectName("maskLabel");
    maskLineEdit->setObjectName("maskLineEdit");
    searchMaskButton->setObjectName("searchMaskButton");
}

void NewSubjectView::setSubjectName(const QString &name) {

    subjectName = name;
    subjectLineEdit->setText(name);
}

void NewSubjectView::setTypeSelection(const QString &type) {
    if(!type.isEmpty()) {
        typeSelected = type;
        typeComboBox->setCurrentText(type);
    }
    else {
     typeComboBox->setCurrentIndex(0);
    }
}

void NewSubjectView::setupToolTip() {

    subjectLineEdit->setToolTip("Insert a name for the Subject");
    searchFileButton->setToolTip("Add an image or a video");
    searchMaskButton->setToolTip("Add a image");
}

void NewSubjectView::addConnect() const {

    connect(searchFileButton, SIGNAL(clicked()), this, SIGNAL(addImage()));
    connect(searchMaskButton, SIGNAL(clicked()), this, SIGNAL(addMask()));
    connect(subjectLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(nameTextChanged(QString)));
    connect(imageLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(imageTextChanged(QString)));
    connect(maskLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(maskTextChanged(QString)));
    connect(typeComboBox, SIGNAL(currentTextChanged(QString)), this, SIGNAL(typeSelectionChanged(QString)));
}

void NewSubjectView::setImagePath(const QString& path) {

    subjectImage = path;
    imageLineEdit->setText(subjectImage);
}

void NewSubjectView::setMaskPath(const QString& path) {

    subjectMask = path;
    maskLineEdit->setText(subjectMask);
}

QString NewSubjectView::getSubjectName() const {

    return subjectName;
}

QString NewSubjectView::getTypeSelected() const {

    return typeSelected;
}

QString NewSubjectView::getImagePath() const {

    return subjectImage;
}

QString NewSubjectView::getMaskPath() const {

    return subjectMask;
}

void NewSubjectView::setupView() {

    createTop();
    createBottom();
}

void NewSubjectView::resetFields() {
    setSubjectName("");
    setImagePath("");
    setMaskPath("");
    setTypeSelection("");
    disableSearchFile();
}

void NewSubjectView::enableSearchFile() {
    searchFileButton->setEnabled(true);
    searchMaskButton->setEnabled(true);
    setImagePath("");
    setMaskPath("");
}

void NewSubjectView::disableSearchFile() {
    searchFileButton->setEnabled(false);
    searchMaskButton->setEnabled(false);
    setImagePath("");
    setMaskPath("");
}

void NewSubjectView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(groupBox->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}
