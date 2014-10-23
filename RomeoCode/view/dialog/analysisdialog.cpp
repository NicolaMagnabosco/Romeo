#include "analysisdialog.h"
#include "view/dialog/dialog.h"
#include <QCloseEvent>
#include <QPixmap>

using Romeo::View::Dialog::AnalysisDialog;
using Romeo::View::Dialog::Dialog;

AnalysisDialog::AnalysisDialog(int numberOfStep, int subjects, QWidget *parent): QDialog(parent), finished(false), number(numberOfStep), currentSubject(0), totalSubjects(subjects), images(), imageShow(-1)
{
    setWindowTitle("Analysis Progress");
    setWindowIcon(QIcon(":/Romeo/romeoLogo.png"));
    setMinimumWidth(600);

    setModal(true);

    createTop();
    createProgress();
    createBottom();
    createLayout();
    setupObjectName();
    addConnect();
    updateButtonsState();
}

void AnalysisDialog::createTop()
{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    previewBox = new QGroupBox(this);

    imageDescription = new QLabel(previewBox);
    imageDescription->setAlignment(Qt::AlignHCenter);
    imageDescription->setSizePolicy(sizePolicy);

    previewImage = new QLabel(previewBox);
    previewImage->setMinimumHeight(300);
    previewImage->setAlignment(Qt::AlignHCenter);

    buttonWidget = new QWidget(previewBox);
    buttonWidget->setSizePolicy(sizePolicy);

    nextButton = new QPushButton("Next", buttonWidget);
    nextButton->setSizePolicy(sizePolicy1);

    QString subjectNumber = QString("Subject ");
    subjectNumber.append(QString::number(currentSubject));
    subjectNumber.append(" di ");
    subjectNumber.append(QString::number(totalSubjects));
    numberSubjects = new QLabel(subjectNumber, buttonWidget);
    numberSubjects->setSizePolicy(sizePolicy1);
    numberSubjects->setAlignment(Qt::AlignHCenter);

    previousButton = new QPushButton("Previous", buttonWidget);
    previousButton->setSizePolicy(sizePolicy1);
}

void AnalysisDialog::createProgress()
{
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    progressWidget = new QWidget(this);
    progressWidget->setSizePolicy(sizePolicy);

    progressBar = new QProgressBar(progressWidget);
    progressBar->setMaximum(number);
    progressBar->setAlignment(Qt::AlignCenter);

    progressLabel = new QLabel("Progress", progressWidget);
    progressLabel->setAlignment(Qt::AlignHCenter);
}

void AnalysisDialog::createBottom()
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
}

void AnalysisDialog::createLayout()
{
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    dialogLayout->setSpacing(-1);
    dialogLayout->setContentsMargins(10, 10, 10, 10);
    dialogLayout->addWidget(previewBox);
    dialogLayout->addWidget(progressWidget);
    dialogLayout->addWidget(bottomWidget);

    QVBoxLayout *previewBoxLayout = new QVBoxLayout(previewBox);
    previewBoxLayout->setSpacing(-1);
    previewBoxLayout->setContentsMargins(0, 10, 0, 0);
    previewBoxLayout->addWidget(imageDescription);
    previewBoxLayout->addWidget(previewImage);
    previewBoxLayout->addWidget(buttonWidget);

    QHBoxLayout *buttonWidgetLayout = new QHBoxLayout(buttonWidget);
    buttonWidgetLayout->setSpacing(-1);
    buttonWidgetLayout->setContentsMargins(0, 0, 0, 0);
    buttonWidgetLayout->addWidget(previousButton);
    buttonWidgetLayout->addWidget(numberSubjects);
    buttonWidgetLayout->addWidget(nextButton);

    QVBoxLayout *progressWidgetLayout = new QVBoxLayout(progressWidget);
    progressWidgetLayout->setSpacing(-1);
    progressWidgetLayout->setContentsMargins(0, 0, 0, 0);
    progressWidgetLayout->addWidget(progressBar);
    progressWidgetLayout->addWidget(progressLabel);

    QHBoxLayout *bottomWidgetlayout = new QHBoxLayout(bottomWidget);
    bottomWidgetlayout->setSpacing(-1);
    bottomWidgetlayout->setContentsMargins(0, 0, 0, 0);
    bottomWidgetlayout->addWidget(cancelButton);
}

void AnalysisDialog::setupObjectName()
{
    setObjectName("AnalysisDialog");
    previewBox->setObjectName("previewBox");
        imageDescription->setObjectName("imageDescription");
        previewImage->setObjectName("previewImage");
        buttonWidget->setObjectName("buttonWidget");
            nextButton->setObjectName("nextButton");
            numberSubjects->setObjectName("numberSubjects");
    progressWidget->setObjectName("progressWidget");
        progressBar->setObjectName("progressBar");
        progressLabel->setObjectName("progressLabel");
    bottomWidget->setObjectName("bottomWidget");
        cancelButton->setObjectName("cancelButton");
}

void AnalysisDialog::addConnect()
{
    connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelAnalysis()));
    connect(nextButton, SIGNAL(clicked()), this, SIGNAL(nextImage()));
    connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previousImage()));
}

void AnalysisDialog::closeEvent(QCloseEvent *event)
{
    //control if the analysis is just finished
    if(finished) {
        event->accept();
        emit closeOnFinish();
    }
    else
    {
        int answer = Dialog::dialogQuestion("Cancel Analysis", "Are you sure to cancel the analysis?","","",this);
        if(answer == QMessageBox::No)
            event->ignore();
        else if(answer == QMessageBox::Yes) {
            emit realClose();
            event->accept();
        }
    }

}

void AnalysisDialog::setBarValue(const QString &description)
{
    int value = progressBar->value() + 1;
    progressBar->setValue(value);
    progressLabel->setText(description);
}

void AnalysisDialog::analysisFinish()
{
    int maximum = progressBar->maximum();
    progressBar->setValue(maximum);
    progressLabel->setText("Analysis complete succesfull");
    finished = true;
    cancelButton->setText("Ok");
    cancelButton->setEnabled(true);
}

void AnalysisDialog::addImage(QImage *image, const QString &description)
{
    if(image) {
        images.append(image);
        imagesDescription.append(description);
        imageShow = images.size()-1;
        previewImage->setPixmap(QPixmap::fromImage(image->scaled(previewImage->width(), previewImage->height(), Qt::KeepAspectRatio)));
        imageDescription->setText(description);
        updateButtonsState();
    }
}

void AnalysisDialog::showImage(int i)
{
    if(i != -1 && i < images.size()) {
        QImage *image = images.at(i);
        QString description = imagesDescription.at(i);
        previewImage->setPixmap(QPixmap::fromImage(image->scaled(previewImage->width(), previewImage->height(), Qt::KeepAspectRatio)));
        //update the imageShow value
        imageShow = i;
        imageDescription->setText(description);
        updateButtonsState();
    }

}

void AnalysisDialog::showNextImage()
{
    if(imageShow >= 0 && imageShow <= images.size()-1) {
        imageShow++;
        showImage(imageShow);
    }
}

void AnalysisDialog::showPreviousImage()
{
    if(imageShow > 0) {
        imageShow--;
        showImage(imageShow);
    }
}

void AnalysisDialog::updateButtonsState()
{
    //update the nextButton state
    if(imageShow == -1 || imageShow == images.size() -1)
        nextButton -> setEnabled(false);
    else
        if(imageShow != -1 && imageShow <= images.size() -1)
            nextButton -> setEnabled(true);

    //update the previousButton state
    if( imageShow <= 0)
        previousButton -> setEnabled(false);
    else
        if(imageShow > 0)
        previousButton -> setEnabled(true);
}

AnalysisDialog::~AnalysisDialog()
{
    for(QVector<QImage*>::const_iterator it = images.constBegin(); it != images.constEnd(); ++it) {
        QImage *image = *it;
        delete image;
    }
}

void AnalysisDialog::setImageDescription(const QString& txt)
{
    imageDescription->clear();
    imageDescription->setText(txt);
}

void AnalysisDialog::incrementCurrentSubject()
{
    currentSubject++;
    QString subjectNumber = QString("Subject ");
    subjectNumber.append(QString::number(currentSubject));
    subjectNumber.append(" di ");
    subjectNumber.append(QString::number(totalSubjects));
    numberSubjects->setText(subjectNumber);
}
