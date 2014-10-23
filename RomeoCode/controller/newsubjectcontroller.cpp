#include "newsubjectcontroller.h"
#include "model/util/dao/subjectdao.h"
#include "model/core/proxysubject.h"
#include <QFileInfo>

using Romeo::Model::Util::DAO::SubjectDAO;
using Romeo::Controller::NewSubjectController;
using Romeo::Model::Core::ProxySubject;
using Romeo::View::Dialog::Dialog;

NewSubjectController::NewSubjectController(NewSubjectView *view, QObject *parent): AController(view,parent)
 {

    createConnections();
}

void NewSubjectController::createConnections() const
{

    //cast the view to a NewSubjectView's object.
    NewSubjectView *subjectView=qobject_cast<NewSubjectView*>(view);
    connect(subjectView, SIGNAL(addImage()), this, SLOT(slotAddImage()));
    connect(subjectView, SIGNAL(addMask()), this, SLOT(slotAddMask()));
    connect(subjectView, SIGNAL(nameTextChanged(QString)),this, SLOT(slotChangeSubjectName(QString)));
    connect(subjectView, SIGNAL(imageTextChanged(QString)), this, SLOT(slotChangeSubjectImage(QString)));
    connect(subjectView, SIGNAL(maskTextChanged(QString)), this, SLOT(slotChangeSubjectMask(QString)));
    connect(subjectView, SIGNAL(saveObject()), this, SLOT(slotSaveSubject()));
    connect(subjectView, SIGNAL(typeSelectionChanged(QString)), this, SLOT(slotChangeType(QString)));
}

void NewSubjectController::slotAddImage()
{
    NewSubjectView *newSubjectView = qobject_cast<NewSubjectView*>(view);
    QString type = newSubjectView->getTypeSelected();

    //obtain the home directory of the system
    QDir home = QDir::home();
    QString filters = "";

    if(type == Utils::ROMEO_IMAGE_TYPE_2D)
        filters = "2D (*.png *.bmp *.jpg *.tif)";
    else if(type == Utils::ROMEO_IMAGE_TYPE_2Dt)
        filters = "2D-t (*.avi *.mpg)";
    else if(type == Utils::ROMEO_IMAGE_TYPE_3D)
        filters = "3D (*.nii)";
    else if(type == Utils::ROMEO_IMAGE_TYPE_3Dt)
        filters = "3D-t (*.nii)";
    else
        filters = "2D (*.png *.bmp *.jpg *.tif)";

    //obtain the fileName selected by the user
    QString fileName = QFileDialog::getOpenFileName(view, tr("Select the image for the Subject"), home.absolutePath(), filters);
    if(!fileName.isEmpty()){
        newSubjectView->setImagePath(fileName);
    }

}


void NewSubjectController::slotAddMask()
{
    NewSubjectView *newSubjectView = qobject_cast<NewSubjectView*>(view);
    QString type = newSubjectView->getTypeSelected();

    //obtain hte home directory of the system
    QDir home =QDir::home();
    QString filters = "";

    if(type == Utils::ROMEO_IMAGE_TYPE_2D)
        filters = "2D (*.png *.bmp *.jpg *.tif)";
    else if(type == Utils::ROMEO_IMAGE_TYPE_2Dt)
        filters = "2D-t (*.png *.bmp *.jpg *.tif)";
    else if(type == Utils::ROMEO_IMAGE_TYPE_3D)
        filters = "3D (*.nii)";
    else if(type == Utils::ROMEO_IMAGE_TYPE_3Dt)
        filters = "3D-t (*.nii)";
    else
        filters = "2D (*.png *.bmp *.jpg *.tif)";

    QString fileName = QFileDialog::getOpenFileName(view, tr("Select the mask for the Subject"), home.absolutePath(), filters);
    if(!fileName.isEmpty()) {

        NewSubjectView *newSubjectView = qobject_cast<NewSubjectView*>(view);
        newSubjectView->setMaskPath(fileName);
    }
}

void NewSubjectController::slotSaveSubject()
{
    int maxChar = 200;
    //cast the view
    NewSubjectView *subjectView = qobject_cast<NewSubjectView*>(view);
    subjectView->removeResultMessageWidget();
    //obtain all the info
    QString name = subjectView->getSubjectName();
    QFileInfo imagePath(subjectView->getImagePath());
    QString image = imagePath.fileName();
    QFileInfo maskPath(subjectView->getMaskPath());
    QString mask = maskPath.fileName();
    QString type = subjectView->getTypeSelected();

    if(!name.isEmpty() && !image.isEmpty() && !type.isEmpty()) {
        if(name.size()>maxChar) {
         subjectView->addResultMessageWidget("The name of the Subject must not exceed "+QString::number(maxChar)+" characters.", false);
         return;
        }
        if(image.size()>maxChar || mask.size()>maxChar) {
         subjectView->addResultMessageWidget("The name of the image or of the mask must not exceed "+QString::number(maxChar)+" characters including the extension.", false);
         return;
        }
        if(type == Utils::ROMEO_IMAGE_TYPE_3D){
            if(check3DVideo(imagePath.absoluteFilePath())) {
                subjectView->addResultMessageWidget("The file can not be a video.", false);
                return;
            }
        }
        else if(type == Utils::ROMEO_IMAGE_TYPE_3Dt){
            if(!check3DVideo(imagePath.absoluteFilePath())) {
                subjectView->addResultMessageWidget("The file must be a video.", false);
                return;
            }
        }

        ProxySubject subject(name, image, type, mask);
        //insert to db.
        SubjectDAO dao;
        if(dao.createSubject(subject))
            creationDone(name, imagePath, image, mask, maskPath);
        else
            subjectView->addResultMessageWidget("Subject name already exists", false);
    }
    else
        subjectView->addResultMessageWidget("Name, Type and Image File are Required", false);
}

void NewSubjectController::creationDone(QString &name, QFileInfo &imagePath, QString &image, QString &mask, QFileInfo &maskPath)
{
    NewSubjectView *subjectView = qobject_cast<NewSubjectView*>(view);

    QString path(Utils::SAVING_SUBJECT_PATH+"/"+name);
    checkPathExistsFromHome(path);

    QFile::copy(imagePath.absoluteFilePath(), path+"/"+image);
    if (image.endsWith(".hdr")){
        QString imgFilePath=image;
        imgFilePath.chop(4);
        QFile::copy(imagePath.absoluteFilePath(), path+"/"+imgFilePath.append(".img"));
    }
    if(!mask.isEmpty()){
        QFile::copy(maskPath.absoluteFilePath(), path+"/"+mask);
        if(mask.endsWith(".hdr")){
            QString maskFilePath=mask;
            maskFilePath.chop(4);
            QFile::copy(maskPath.absoluteFilePath(), path+"/"+maskFilePath.append(".img"));
        }
    }

    subjectView->resetFields();
    MainWindow::getMainWindow()->writeStatusBar("Subject "+name+" inserted", 10000);

    subjectView->addResultMessageWidget("Subject "+name+" inserted", true);
}

void NewSubjectController::slotChangeSubjectName(const QString &newName)
{

    NewSubjectView *subjectView = qobject_cast<NewSubjectView*>(view);
    subjectView->setSubjectName(newName);
}

void NewSubjectController::slotChangeSubjectImage(const QString &newImage)
{

    NewSubjectView *subjectView = qobject_cast<NewSubjectView*>(view);
    subjectView->setImagePath(newImage);
}

void NewSubjectController::slotChangeSubjectMask(const QString &newMask)
{

    NewSubjectView *subjectView = qobject_cast<NewSubjectView*>(view);
    subjectView->setMaskPath(newMask);
}

void NewSubjectController::slotChangeType(const QString &selection)
{
    NewSubjectView *subjectView = qobject_cast<NewSubjectView*>(view);
    subjectView->setTypeSelection(selection);

    if(selection == Utils::ROMEO_SELECT_TYPE) subjectView->disableSearchFile();
    else subjectView->enableSearchFile();
}
