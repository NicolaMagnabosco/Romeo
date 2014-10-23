#include "featureparams.h"

using Romeo::View::Dialog::FeatureParams;
using Romeo::View::Dialog::Dialog;

FeatureParams::FeatureParams(const QVector<AFeature*>& featureP, QWidget *parent) :
    QDialog(parent), features(featureP), feature(0)
{
    setWindowTitle("Feature Selector");
    setWindowIcon(QIcon(":/Romeo/romeoLogo.png"));
    setFixedSize(QSize(500, 300));

    setModal(true);

    createTop();
    createBottom();
    createLayout();
    setupObjectName();
    addConnect();
}

void FeatureParams::createTop()
{
    createFeatureBox();
    createFirstBox();
    createSecondBox();
    createDynamicBox();
    resetBox();
}

void FeatureParams::createFeatureBox()
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    featuresBox = new QGroupBox(this);
    featuresBox->setTitle("Select the Feature");
    featuresComboBox = new QComboBox(featuresBox);
    featuresComboBox->setSizePolicy(sizePolicy);

    featuresComboBox->addItem(Utils::ROMEO_SELECT_FEATURE);
    for(int i=0; i<features.size(); ++i)
        featuresComboBox->addItem(features.at(i)->getName());
}

void FeatureParams::createFirstBox() {
    firstOrderBox = new QGroupBox(this);
    firstOrderBox->setTitle("Parameters");
    firstFirstParam = new QWidget(firstOrderBox);
    firstWSizeLabel = new QLabel(Utils::FEATURE_WINDOW_SIZE, firstFirstParam);
    firstWSize = new QLineEdit(firstFirstParam);
}

void FeatureParams::createSecondBox()
{
    secondOrderBox = new QGroupBox(this);
    secondOrderBox->setTitle("Parameters");
    secondFirstParam = new QWidget(secondOrderBox);
    secondWSizeLabel = new QLabel(Utils::FEATURE_WINDOW_SIZE, secondFirstParam);
    secondWSize = new QLineEdit(secondFirstParam);
    secondSecondParam = new QWidget(secondOrderBox);
    secondGlcmLabel = new QLabel(Utils::FEATURE_GLCM+" "+Utils::FEATURE_GLCM_FULL, secondSecondParam);
    secondGlcm = new QLineEdit(secondSecondParam);
}

void FeatureParams::createDynamicBox()
{
    dynamicBox = new QGroupBox(this);
    dynamicBox->setTitle("Parameters");
    dynamicSecondParam = new QWidget(dynamicBox);
    dynamicInitialFrameLabel = new QLabel(Utils::FEATURE_INITIAL_FRAME, dynamicSecondParam);
    dynamicInitialFrame = new QLineEdit(dynamicSecondParam);
    dynamicThirdParam = new QWidget(dynamicBox);
    dynamicFinalFrameLabel = new QLabel(Utils::FEATURE_FINAL_FRAME, dynamicThirdParam);
    dynamicFinalFrame = new QLineEdit(dynamicThirdParam);
}

void FeatureParams::createBottom()
{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    bottomWidget = new QWidget(this);
    bottomWidget->setSizePolicy(sizePolicy);

    cancelButton = new QPushButton("Cancel", bottomWidget);
    cancelButton->setSizePolicy(sizePolicy1);

    okButton = new QPushButton("Ok", bottomWidget);
    okButton->setSizePolicy(sizePolicy1);
}

void FeatureParams::createLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(-1);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->addWidget(featuresBox);
    layout->addWidget(firstOrderBox);
    layout->addWidget(secondOrderBox);
    layout->addWidget(dynamicBox);
    layout->addWidget(bottomWidget);

    QHBoxLayout *featuresBoxLayout = new QHBoxLayout(featuresBox);
    featuresBoxLayout->setSpacing(-1);
    featuresBoxLayout->setContentsMargins(0, 0, 0, 0);
    featuresBoxLayout->addWidget(featuresComboBox);

    QVBoxLayout *firstOrderBoxLayout = new QVBoxLayout(firstOrderBox);
    firstOrderBoxLayout->setSpacing(-1);
    firstOrderBoxLayout->setContentsMargins(0, 0, 0, 0);
    firstOrderBoxLayout->addWidget(firstFirstParam);

    QHBoxLayout *firstFirstParamLayout = new QHBoxLayout(firstFirstParam);
    firstFirstParamLayout->setSpacing(-1);
    firstFirstParamLayout->setContentsMargins(0, 0, 0, 0);
    firstFirstParamLayout->addWidget(firstWSizeLabel);
    firstFirstParamLayout->addWidget(firstWSize);

    QVBoxLayout *secondOrderBoxLayout = new QVBoxLayout(secondOrderBox);
    secondOrderBoxLayout->setSpacing(-1);
    secondOrderBoxLayout->setContentsMargins(0, 0, 0, 0);
    secondOrderBoxLayout->addWidget(secondFirstParam);
    secondOrderBoxLayout->addWidget(secondSecondParam);

    QHBoxLayout *secondFirstParamLayout = new QHBoxLayout(secondFirstParam);
    secondFirstParamLayout->setSpacing(-1);
    secondFirstParamLayout->setContentsMargins(0, 0, 0, 0);
    secondFirstParamLayout->addWidget(secondWSizeLabel);
    secondFirstParamLayout->addWidget(secondWSize);

    QHBoxLayout *secondSecondParamLayout = new QHBoxLayout(secondSecondParam);
    secondSecondParamLayout->setSpacing(-1);
    secondSecondParamLayout->setContentsMargins(0, 0, 0, 0);
    secondSecondParamLayout->addWidget(secondGlcmLabel);
    secondSecondParamLayout->addWidget(secondGlcm);

    QVBoxLayout *dynamicBoxLayout = new QVBoxLayout(dynamicBox);
    dynamicBoxLayout->setSpacing(-1);
    dynamicBoxLayout->setContentsMargins(0, 0, 0, 0);
    dynamicBoxLayout->addWidget(dynamicSecondParam);
    dynamicBoxLayout->addWidget(dynamicThirdParam);

    QHBoxLayout *dynamicSecondParamLayout = new QHBoxLayout(dynamicSecondParam);
    dynamicSecondParamLayout->setSpacing(-1);
    dynamicSecondParamLayout->setContentsMargins(0, 0, 0, 0);
    dynamicSecondParamLayout->addWidget(dynamicInitialFrameLabel);
    dynamicSecondParamLayout->addWidget(dynamicInitialFrame);

    QHBoxLayout *dynamicThirdParamLayout = new QHBoxLayout(dynamicThirdParam);
    dynamicThirdParamLayout->setSpacing(-1);
    dynamicThirdParamLayout->setContentsMargins(0, 0, 0, 0);
    dynamicThirdParamLayout->addWidget(dynamicFinalFrameLabel);
    dynamicThirdParamLayout->addWidget(dynamicFinalFrame);

    QHBoxLayout *bottomWidgetlayout = new QHBoxLayout(bottomWidget);
    bottomWidgetlayout->setSpacing(-1);
    bottomWidgetlayout->setContentsMargins(0, 0, 0, 0);
    bottomWidgetlayout->addWidget(cancelButton);
    bottomWidgetlayout->addWidget(okButton);
}

void FeatureParams::setupObjectName()
{
    setObjectName("FeatureParams");
    featuresBox->setObjectName("featuresBox");
        featuresComboBox->setObjectName("featuresComboBox");
    firstOrderBox->setObjectName("firstOrderBox");
        firstFirstParam->setObjectName("firstFirstParam");
            firstWSizeLabel->setObjectName("firstWSizeLabel");
            firstWSize->setObjectName("firstWSize");
    secondOrderBox->setObjectName("secondOrderBox");
        secondFirstParam->setObjectName("secondFirstParam");
            secondWSizeLabel->setObjectName("secondWSizeLabel");
            secondWSize->setObjectName("secondWSize");
        secondSecondParam->setObjectName("secondSecondParam");
            secondGlcmLabel->setObjectName("secondGlcmLabel");
            secondGlcm->setObjectName("secondGlcm");
    dynamicBox->setObjectName("dynamicBox");
        dynamicSecondParam->setObjectName("dynamicSecondParam");
            dynamicInitialFrameLabel->setObjectName("dynamicInitialFrameLabel");
            dynamicInitialFrame->setObjectName("dynamicInitialFrame");
        dynamicThirdParam->setObjectName("dynamicThirdParam");
            dynamicFinalFrameLabel->setObjectName("dynamicFinalFrameLabel");
            dynamicFinalFrame->setObjectName("dynamicFinalFrame");
    bottomWidget->setObjectName("bottomWidget");
        cancelButton->setObjectName("cancelButton");
        okButton->setObjectName("okButton");
}

void FeatureParams::addConnect()
{
    connect(featuresComboBox, SIGNAL(currentTextChanged(QString)), this, SIGNAL(featureSelected(QString)));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(slotOk()));
}

void FeatureParams::resetBox()
{
    firstOrderBox->setVisible(false);    
    secondOrderBox->setVisible(false);    
    dynamicBox->setVisible(false);    
    feature=0;
    resetDefaultValues();
}

void FeatureParams::resetDefaultValues()
{
    firstWSize->setText(QString::number(3));

    secondWSize->setText(QString::number(3));
    secondGlcm->setText(QString::number(1));

    dynamicInitialFrame->setText(QString::number(1));
    dynamicFinalFrame->setText(QString::number(1));
}

void FeatureParams::visibleBox(const QString& typeS)
{
    if(typeS == Utils::FEATURE_FIRST_ORDER) {
        firstOrderBox->setVisible(true);
        secondOrderBox->setVisible(false);
        dynamicBox->setVisible(false);
        type=Utils::FEATURE_FIRST_ORDER;
    }
    else if(typeS == Utils::FEATURE_SECOND_ORDER) {
        firstOrderBox->setVisible(false);
        secondOrderBox->setVisible(true);
        dynamicBox->setVisible(false);
        type=Utils::FEATURE_SECOND_ORDER;
    }
    else if(typeS == Utils::FEATURE_DYNAMIC) {
        firstOrderBox->setVisible(false);
        secondOrderBox->setVisible(false);
        dynamicBox->setVisible(true);
        type=Utils::FEATURE_DYNAMIC;
    }
}

void FeatureParams::slotOk()
{
    if(!feature) {
        Dialog::dialogCritical("Error", "You must select a feature");
        return;
    }

    params.clear();
    bool okParams = false;
    bool isInt;
    int wsMin = 3;
    int wsMax = 39;
    bool windowSizeError = false;
    int glcmMin = 1;
    int glcmMax = 1;
    bool glcmSizeError = false;
    int ifMin = 1;
    bool initialFrameError = false;
    bool finalFrameError = false;

    if(type == Utils::FEATURE_FIRST_ORDER) {
        if(!firstWSize->text().isEmpty()) {
            firstWSize->text().toInt(&isInt);
            if(isInt && (firstWSize->text().toInt()<wsMin || firstWSize->text().toInt()>wsMax || !(firstWSize->text().toInt()%2))) windowSizeError = true;

            params.append(firstWSize->text());
            okParams = true;
        }
    }
    else if(type == Utils::FEATURE_SECOND_ORDER) {
        if(!secondWSize->text().isEmpty() && !secondGlcm->text().isEmpty()) {
            secondWSize->text().toInt(&isInt);            
            if(isInt && (secondWSize->text().toInt()<wsMin || secondWSize->text().toInt()>wsMax || !(secondWSize->text().toInt()%2))) windowSizeError = true;
            if(isInt && !windowSizeError) {
                secondGlcm->text().toInt(&isInt);
                glcmMax = secondWSize->text().toInt()/2;
                if(isInt && (secondGlcm->text().toInt()<glcmMin || secondGlcm->text().toInt()>glcmMax)) glcmSizeError=true;
            }

            params.append(secondWSize->text());
            params.append(secondGlcm->text());
            okParams = true;
        }
    }
    else if(type == Utils::FEATURE_DYNAMIC) {
        if(!dynamicInitialFrame->text().isEmpty() && !dynamicFinalFrame->text().isEmpty()) {
            dynamicInitialFrame->text().toInt(&isInt);
            if(isInt && dynamicInitialFrame->text().toInt()<ifMin) initialFrameError=true;
            dynamicFinalFrame->text().toInt(&isInt);
            if(isInt && !initialFrameError && dynamicFinalFrame->text().toInt()<dynamicInitialFrame->text().toInt()) finalFrameError=true;
            if(isInt && !finalFrameError && dynamicInitialFrame->text().toInt()>dynamicInitialFrame->text().toInt()) initialFrameError=true;

            params.append(dynamicInitialFrame->text());
            params.append(dynamicFinalFrame->text());
            okParams = true;
        }
    }


    if(okParams) {
        if(!isInt) Dialog::dialogCritical("Error", "All parameters must be of integer type");
        else if(windowSizeError) Dialog::dialogCritical("Error", Utils::FEATURE_WINDOW_SIZE+" must be between "+QString::number(wsMin)+" and "+QString::number(wsMax)+" and must be odd");
        else if(glcmSizeError) Dialog::dialogCritical("Error", Utils::FEATURE_GLCM+" must be between "+QString::number(glcmMin)+" and "+Utils::FEATURE_WINDOW_SIZE+"/2");
        else if(initialFrameError) Dialog::dialogCritical("Error", Utils::FEATURE_INITIAL_FRAME+" must be between "+QString::number(ifMin)+" and "+Utils::FEATURE_FINAL_FRAME);
        else if(finalFrameError) Dialog::dialogCritical("Error", Utils::FEATURE_FINAL_FRAME+" must be between "+Utils::FEATURE_INITIAL_FRAME+" and last frame of the video");
        else emit ok(params);
    }
    else Dialog::dialogCritical("Error", "All parameters are required");
}

void FeatureParams::setFeature(AFeature* featureF)
{
    feature=featureF;
}

AFeature * FeatureParams::getFeature() const
{
    return feature;
}
