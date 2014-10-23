#include "newprotocolview.h"

using Romeo::View::Window::NewProtocolView;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::AlgCreator;

NewProtocolView::NewProtocolView(QWidget *parent): APanel(parent)
{
    MainWindow::getMainWindow()->setWindowTitle("New Protocol - ROMEO");
    initializeView();
}

void NewProtocolView::createTop()
{
    topWidget = new QWidget(this);
    createLeft();
    createCenter();
    createRight();
}

void NewProtocolView::createLeft()
{
     infoBox = new QGroupBox("Informations", topWidget);
         infoWidget = new QWidget(infoBox);
            nameWidget = new QWidget(infoWidget);
                nameLabel = new QLabel("Name "+Utils::TXT_REQUIRED, nameWidget);
                nameLineEdit = new QLineEdit(nameWidget);
            typeWidget = new QWidget(infoWidget);
                typeLabel = new QLabel("Type "+Utils::TXT_REQUIRED, typeWidget);
                typeComboBox = new QComboBox(typeWidget);
                typeComboBox->setModel(APanel::getTypeRomeo(this));
        infoSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

void NewProtocolView::createCenter()
{
    featureBox = new QGroupBox("Features", topWidget);

        featButtonBox = new QWidget(featureBox);
            featureAdd = new QPushButton(featButtonBox);
            featureAdd->setText("Add Feature");
            featureRemoveBtn = new QPushButton(featButtonBox);
            featureRemoveBtn->setText("Remove Selected");
            featureRemoveBtn->setEnabled(false);

        featureList = new QTableView(featureBox);
        featureList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        featureList->setTabKeyNavigation(false);
        featureList->setSelectionMode(QAbstractItemView::SingleSelection);
        featureList->setSelectionBehavior(QAbstractItemView::SelectRows);
        featureList->horizontalHeader()->setHighlightSections(false);
        featureList->horizontalHeader()->setStretchLastSection(true);
        featureList->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);
        featureList->setProperty("showDropIndicator", QVariant(false));
        featureList->setDragDropOverwriteMode(false);
        featureList->setAlternatingRowColors(true);
        featureList->setCornerButtonEnabled(false);

        model = new NewProtocolFeatureTableModel();
        featureList->setModel(model);
        featureList->setSortingEnabled(false);
        featureList->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        featureList->resizeColumnsToContents();
}

void NewProtocolView::createRight()
{
    algorithmBox = new QGroupBox("Algorithms", topWidget);
        algorithmComboBox = new QComboBox(algorithmBox);
        setAlgorithmsComboBox();

        parametersWidget = new QWidget (algorithmBox);

        algorithmSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

void NewProtocolView::setAlgorithmsComboBox() {
    AlgCreator * ac = AlgCreator::getAlgCreator();
    QVector<AAlgorithm*> algorithms = ac->getAllAlgorithms();
    QStringList items;
    items<< Utils::ROMEO_SELECT_ALGORITHM;

    for(int i=0; i<algorithms.size(); ++i){
        items << algorithms.at(i)->getName();
    }

    algorithmComboBox->setModel(new QStringListModel(items, this));
}

void NewProtocolView::createBottom()
{
    bottomWidget = new NavWidget(NavWidget::_BACK_SAVE, this);
}

void NewProtocolView::setupLayout()
{
    QVBoxLayout *mainWidgetLayout = new QVBoxLayout(this);
    mainWidgetLayout->setSpacing(-1);
    mainWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mainWidgetLayout->addWidget(topWidget);
    mainWidgetLayout->addWidget(bottomWidget);
    setupTopLayout();
}

void NewProtocolView::setupTopLayout()
{
    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->setSpacing(-1);
    topWidgetLayout->setContentsMargins(10, 10, 10, 10);
    topWidgetLayout->addWidget(infoBox);
    topWidgetLayout->addWidget(featureBox);
    topWidgetLayout->addWidget(algorithmBox);
    topWidgetLayout->setStretch(0, 1);
    topWidgetLayout->setStretch(1, 2);
    topWidgetLayout->setStretch(2, 1);

    QVBoxLayout *infoBoxLayout = new QVBoxLayout(infoBox);
    infoBoxLayout->setSpacing(-1);
    infoBoxLayout->setContentsMargins(0, 10, 0, 0);
    infoBoxLayout->addWidget(infoWidget);
    infoBoxLayout->addItem(infoSpacer);

    QVBoxLayout *infoWidgetLayout = new QVBoxLayout(infoWidget);
    infoWidgetLayout->setSpacing(20);
    infoWidgetLayout->setContentsMargins(0, 0, 0, 0);
    infoWidgetLayout->addWidget(nameWidget);
    infoWidgetLayout->addWidget(typeWidget);

    QVBoxLayout *nameWidgetLayout = new QVBoxLayout(nameWidget);
    nameWidgetLayout->setSpacing(-1);
    nameWidgetLayout->setContentsMargins(0, 0, 0, 0);
    nameWidgetLayout->addWidget(nameLabel);
    nameWidgetLayout->addWidget(nameLineEdit);
    nameWidgetLayout->addWidget(labelInfo("Insert the name of the Protocol.", nameWidget));

    QVBoxLayout *typeWidgetLayout = new QVBoxLayout(typeWidget);
    typeWidgetLayout->setSpacing(-1);
    typeWidgetLayout->setContentsMargins(0, 0, 0, 0);
    typeWidgetLayout->addWidget(typeLabel);
    typeWidgetLayout->addWidget(typeComboBox);
    typeWidgetLayout->addWidget(labelInfo("Select the Type of the Protocol.", typeWidget));

    QHBoxLayout * featButtonBoxLayout = new QHBoxLayout(featButtonBox);
    featButtonBoxLayout->setSpacing(-1);
    featButtonBoxLayout->setContentsMargins(0, 0, 0, 0);
    featButtonBoxLayout->addWidget(featureAdd);
    featButtonBoxLayout->addWidget(featureRemoveBtn);

    QVBoxLayout *featureBoxLayout = new QVBoxLayout(featureBox);
    featureBoxLayout->setSpacing(-1);
    featureBoxLayout->setContentsMargins(0, 10, 0, 0);
    featureBoxLayout->addWidget(featButtonBox);
    featureBoxLayout->addWidget(featureList);
    featureBoxLayout->addWidget(labelInfo("Click \"Add Feature\" to add a Feature according to the Type selected.\nTo remove a Feature select it and click to Remove button.", featureBox));

    QVBoxLayout *algorithmBoxLayout = new QVBoxLayout(algorithmBox);
    algorithmBoxLayout->setSpacing(-1);
    algorithmBoxLayout->setContentsMargins(0, 10, 0, 0);
    algorithmBoxLayout->addWidget(algorithmComboBox);
    algorithmBoxLayout->addWidget(labelInfo("Select the Algorithm", algorithmBox));
    algorithmBoxLayout->addWidget(parametersWidget);    
    algorithmBoxLayout->addItem(algorithmSpacer);

     QVBoxLayout *parametersWidgetLayout = new QVBoxLayout(parametersWidget);
     parametersWidgetLayout->setSpacing(-1);
     parametersWidgetLayout->setContentsMargins(0, 0, 0, 0);
}

void NewProtocolView::setupView()
{
    createTop();
    createBottom();
}

void NewProtocolView::setupToolTip()
{
}

void NewProtocolView::addConnect() const
{
    connect(featureAdd, SIGNAL(clicked()), this, SIGNAL(addFeatureClicked()));
    connect(typeComboBox, SIGNAL(currentTextChanged(QString)), this, SIGNAL(typeChange(QString)));
    connect(featureRemoveBtn, SIGNAL(clicked()), this, SIGNAL(featureRemove()));
    connect(featureList, SIGNAL(clicked(QModelIndex)), this, SIGNAL(featureSelect(QModelIndex)));
    connect(algorithmComboBox, SIGNAL(currentTextChanged(QString)), this, SIGNAL(algorithmSelect(QString)));
}

void NewProtocolView::setupObjectName()
{
    setObjectName("NewProtocolView");
    topWidget->setObjectName("topWidget");
    infoBox->setObjectName("infoBox");
    infoWidget->setObjectName("infoWidget");
    nameWidget->setObjectName("nameWidget");
    nameLabel->setObjectName("nameLabel");
    nameLineEdit->setObjectName("nameLineEdit");
    typeWidget->setObjectName("typeWidget");
    typeLabel->setObjectName("typeLabel");
    typeComboBox->setObjectName("typeComboBox");
    featureBox->setObjectName("featureBox");
    featureList->setObjectName("featureList");
    featureAdd->setObjectName("featureAdd");
    algorithmBox->setObjectName("algorithmBox");
    algorithmComboBox->setObjectName("algorithmComboBox");
    parametersWidget->setObjectName("parametersWidget");
}

void NewProtocolView::loadCss(){
    QString styleSheet= MainWindow::loadCssStatic(":/Romeo/protocols.css");
    setStyleSheet(styleSheet);
}

QString NewProtocolView::getTypeSelected() const {
    return typeComboBox->currentText();
}

QString NewProtocolView::getAlgorithmSelected() const {
    return algorithmComboBox->currentText();
}

QString NewProtocolView::getProtocolName() const {
    return nameLineEdit->text();
}

QTableView * NewProtocolView::getFeaturesTable() const {
    return featureList;
}

void NewProtocolView::resetFields() {
    MainWindow::getMainWindow()->setWindowTitle("New Protocol - ROMEO");
    nameLineEdit->clear();
    nameLineEdit->setEnabled(true);
    typeComboBox->setCurrentIndex(0);
    typeComboBox->setEnabled(true);
    model->resetModel();
    algorithmComboBox->setCurrentIndex(0);
}

void NewProtocolView::addResultMessageWidget(const QString& txt, bool type) {
    removeResultMessageWidget();

    if(type)
        resultMessageWidget = ResultMessageWidget::successWidget(txt, this);
    else
        resultMessageWidget = ResultMessageWidget::errorWidget(txt, this);

    QBoxLayout * layout = qobject_cast<QBoxLayout*>(this->layout());

    layout->insertWidget(0, resultMessageWidget, 0, Qt::AlignHCenter);
}

void NewProtocolView::setEditFields(Protocol* protocol) {
    MainWindow::getMainWindow()->setWindowTitle("Edit Protocol - ROMEO");
    nameLineEdit->setText(protocol->getName());
    nameLineEdit->setEnabled(false);
    QString type = protocol->getType();
    typeComboBox->setCurrentText(type);
    typeComboBox->setEnabled(false);

    QVector<AFeature*> features = protocol->getFeatures();
    for(int i=0; i<features.size(); ++i)
        model->addFeature(features.at(i));

    AAlgorithm *algorithm = protocol->getAlgorithm();
    QStringList params;
    QMap<QString, QList<int> > list;
    if(algorithm) {
        algorithmComboBox->setCurrentText(algorithm->getName());
        params = algorithm->getParameters();
        list = algorithm->getParametersTypeList();
    }

    QMapIterator<QString, QList<int> > it(list);
    int itChoice = 0;

    for(int i=0; i<params.size(); ++i){
        QLineEdit *le = qobject_cast<QLineEdit*>(algorithmsFieldsList.at(i));
        QComboBox * cb = qobject_cast<QComboBox*>(algorithmsFieldsList.at(i));
        it.next();
        if(it.value().at(0) == Utils::_INT && le) {
            le->setText(params.at(i));
        }
        else if(it.value().at(0) == Utils::_CHOICE && cb){
            cb->setCurrentText(algorithm->getValueComboBox(itChoice, params.at(i)));
            itChoice++;
        }
    }
}

QModelIndexList NewProtocolView::getSelectedFeatures() const {
    QItemSelectionModel* selectedModel = featureList->selectionModel();
    return selectedModel->selectedRows();
}

void NewProtocolView::enableRemoveFeatureButton(const bool enable) {
    featureRemoveBtn->setEnabled(enable);
}

void NewProtocolView::setAlgorithmFields(AAlgorithm *alg){
    QMap<QString, QList<int> > map = alg->getParametersTypeList();

    if(map.size()>0) {
        QMapIterator<QString, QList<int> > it(map);
        int choiceIt=0;
        while (it.hasNext()) {
            it.next();

            QWidget *boxParam = new QWidget(parametersWidget);
            QLabel *labelParam = new QLabel(it.key(), boxParam);

            QVBoxLayout *boxParamLayout = new QVBoxLayout(boxParam);
            boxParamLayout->setSpacing(1);
            boxParamLayout->setContentsMargins(5, 5, 5, 5);
            boxParamLayout->addWidget(labelParam);

            switch(it.value().at(0)){
                case Utils::_INT:{
                    QLineEdit *lineEditParam = new QLineEdit(boxParam);
                    lineEditParam->setText(QString::number(it.value()[1]));
                    boxParamLayout->addWidget(lineEditParam);
                    boxParamLayout->addWidget(labelInfo("The parameter must be an INTEGER", boxParam));
                    algorithmsFieldsList.append(lineEditParam);
                    break;
                }
                case Utils::_CHOICE:{
                    QVector< QMap<char, QString> > vect = alg->getParametersOfTypeChoice();
                    if(vect.size()>0 && choiceIt<vect.size()){
                        QComboBox *comboBox = new QComboBox(boxParam);
                        boxParamLayout->addWidget(comboBox);
                        boxParamLayout->addWidget(labelInfo("Select a value from the list", boxParam));
                        QStringList items;

                        QMapIterator<char, QString> it2(vect.at(choiceIt));
                        while (it2.hasNext()) {
                            it2.next();
                            items<<it2.value();
                        }
                        char def = it.value()[1];
                        QString defChoice = alg->getValueComboBox(choiceIt, QString(def));
                        comboBox->setModel(new QStringListModel(items, comboBox));
                        comboBox->setCurrentText(defChoice);
                        algorithmsFieldsList.append(comboBox);
                        choiceIt++;
                    }

                    break;
                }
            }
            parametersWidget->layout()->addWidget(boxParam);
        }
    }
}

void NewProtocolView::removeAlgorithmFields() {
    QList<QWidget *> widgets = parametersWidget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);

    for(int i=0; i<widgets.size(); ++i)
        delete widgets.at(i);

    algorithmsFieldsList.clear();
}

QStringList NewProtocolView::getAlgorithmParameters(AAlgorithm * alg) const {
    QStringList ret;
    int itChoice = 0;

    for(int i=0; i<algorithmsFieldsList.size(); ++i){
        QLineEdit *le = qobject_cast<QLineEdit*>(algorithmsFieldsList.at(i));
        QComboBox * cb = qobject_cast<QComboBox*>(algorithmsFieldsList.at(i));
        if(le) {
            ret.append(le->text());
        }
        else if(cb){
            QString sel = cb->currentText();
            QString character = alg->getKeyComboBox(itChoice, sel);
            ret.append(character);
            itChoice++;
        }
    }

    return ret;
}
