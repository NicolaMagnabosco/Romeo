#include "subjectscontroller.h"

using Romeo::Controller::SubjectsController;
using Romeo::Model::QtModel::SubjectTableModel;
using Romeo::Model::Core::ASubject;
using Romeo::Model::Util::DAO::SubjectDAO;
using Romeo::Controller::MainWindowController;
using Romeo::View::Dialog::Dialog;

SubjectsController::SubjectsController(SubjectsView *view, QObject *parent) : AController(view, parent)
{
    createConnections();
}

void SubjectsController::createConnections() const
{
    SubjectsView *subjectsView=qobject_cast<SubjectsView*>(view);

    connect(subjectsView, SIGNAL(itemSelected(QModelIndex)), this, SLOT(slotItemSelected(QModelIndex)));
    connect(subjectsView, SIGNAL(ImageDoubleClicked(QString)), this, SLOT(SlotImageDoubleClicked(QString)));
    connect(subjectsView, SIGNAL(MaskDoubleClicked(QString)), this, SLOT(SlotImageDoubleClicked(QString)));
}

void SubjectsController::slotItemSelected(const QModelIndex &index)
{
    SubjectsView *subjectsView=qobject_cast<SubjectsView*>(view);

    QString item = subjectsView->getTableView()->model()->index(index.row(), 0 ,index).data().toString();
    SubjectDAO db;
    ASubject *subject = db.getSubjectByName(item);
    QVector<QString> groups = db.getGroupsOfSubject(subject->getName());
    QImage image;
    QImage mask;
    QString pathI = "";
    QString pathM = "";

    checkPathExistsFromHome(Utils::SAVING_SUBJECT_PATH+"/"+subject->getName());

    if(subject->getType()==Utils::ROMEO_IMAGE_TYPE_2D) {
        loadImage2D(image, mask, pathI, pathM, subject);
        subjectsView->setSubjectImgs(image, mask, pathI, pathM);
    }
    else if(subject->getType()==Utils::ROMEO_IMAGE_TYPE_3D || subject->getType()==Utils::ROMEO_IMAGE_TYPE_2Dt || subject->getType()==Utils::ROMEO_IMAGE_TYPE_3Dt) {
        loadImage3D_Video(image, mask, pathI, pathM, subject);
        subjectsView->setSubjectImgs(image, mask, pathI, pathM);
    }

    //Deallocate the subject object
    delete subject;

    QString infoTxt = "The Subject is not part of any group";
    if(groups.size()>0) {
        infoTxt.clear();
        infoTxt.append(item+" is found in the following groups:\n\n");
        for(int i=0; i<groups.size(); i++) {
            infoTxt.append("\t"+groups.at(i)+"\n");
        }
    }
    subjectsView->setSubjectInfo(infoTxt);
}

void SubjectsController::loadImage2D(QImage &image, QImage &mask, QString &pathI, QString &pathM, ASubject *subject)
{
    if(!image.load(subject->getImage()))
        image.load(":/Romeo/imgError.png");
    else pathI = subject->getImage();

    if(subject->hasMask()){
        if(!mask.load(subject->getMask())){
            mask.load(":/Romeo/imgError.png");
        }
        else pathM = subject->getMask();
    }
    else {
        mask.load(":/Romeo/noMask.png");
    }
}

void SubjectsController::loadImage3D_Video(QImage &image, QImage &mask, QString &pathI, QString &pathM, ASubject *subject)
{
    QDir dir;
    if(!dir.exists(subject->getImage()))
        image.load(":/Romeo/imgError.png");
    else {
        pathI = subject->getImage();
        image = *getImage3DVideo(subject->getImage());
    }

    if(subject->hasMask()){
        if(!dir.exists(subject->getMask())){
            mask.load(":/Romeo/imgError.png");
        }
        else {
            pathM = subject->getMask();
            mask = *getImage3DVideo(subject->getMask());
        }
    }
    else mask.load(":/Romeo/noMask.png");
}

void SubjectsController::SlotImageDoubleClicked(const QString& path)
{
    QDir dir;
    if(dir.exists(path))
        QDesktopServices::openUrl(QUrl("file:///" + path));
    else Dialog::dialogCritical("IMAGE ERROR!", "Image not found!");
}
