#include "analysis.h"
#include "model/core/groupofsubject.h"
#include "model/core/asubject.h"
#include "model/core/romeoobject.h"
#include "model/core/algorithm/aalgorithm.h"
#include "model/util/exporterModel/exporter.h"
#include "model/util/exporterModel/exporter2d.h"
#include "model/util/exporterModel/exporter3d.h"
#include <QDir>
#include <QImage>
#include <utils.h>



using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Core::Analysis;
using Romeo::Model::Core::ASubject;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Util::ExporterModel::Exporter;
using Romeo::Model::Util::ExporterModel::Exporter2D;
using Romeo::Model::Util::ExporterModel::Exporter3D;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;

Analysis::Analysis(Dataset *datasetSelected, QVector<QString> subjects, QMap<int, bool> featShow, QMap<int, bool> featSave, const QDir &directory, int tId, const QDateTime& date, QObject *parent): QThread(parent), id(tId), dataset(datasetSelected), selectedSubject(subjects),
    featuresShow(featShow), featuresSave(featSave), saveDirectory(directory), completed(false), creationDate(date)
{

}

void Analysis::run()
{
    //obtain the group of subject
    GroupOfSubject *group = dataset->getGroup();
    //vector containing all the subject to analyze
    QVector<ASubject*> analysisSubject;
    if(group->subjectsCount() == selectedSubject.size())
        analysisSubject = group->getAllSubjects();
    else {
        //iterate for obtain all subject object that i need
        for(QVector<QString>::const_iterator it = selectedSubject.constBegin(); it != selectedSubject.constEnd(); ++it) {
            //obtain the name of the subject
            QString name = *it;
            ASubject *subject = group->getSubjectWithName(name);
            analysisSubject.append(subject);
        }
    }
    //start the anlysis
    for(QVector<ASubject*>::const_iterator it = analysisSubject.constBegin(); it != analysisSubject.constEnd(); ++it) {
        //obtain the subject
        ASubject *subject = *it;
        emit beginSubject();
        executeAnalysisOnSubject(*subject,true);
    }
    emit resultReady();
}

void Analysis::executeAnalysisOnSubject(ASubject &subject, bool save)
{
    QString ext;
    if(subject.getType() == Utils::ROMEO_IMAGE_TYPE_2D || subject.getType() == Utils::ROMEO_IMAGE_TYPE_2Dt)
        ext = "jpg";
    else
        ext = "nii";

    //get the representation of the subject's image


    // image will point to an RGBImage2D || RGBImage3D || Video2D || Video3D
    RomeoObject *image = subject.getImageFormat();
    showImage(subject.getImage(), subject.getName());
    QVector<Protocol*> protocols = dataset->getProtocols();


    for(QVector<Protocol*>::const_iterator it = protocols.constBegin(); it != protocols.constEnd(); ++it) {

        //obtain the protocol
        Protocol *protocol = *it;

        //obtain the features of the protocol
        QVector<AFeature*> features = protocol->getFeatures();




        QDir dir(QDir::homePath());

        for(QVector<AFeature*>::const_iterator it = features.constBegin(); it != features.constEnd(); ++it) {
            //obtain the feature pointed by it
            AFeature *feature = *it;
            RomeoObject* outputData=runFeature(feature, image, subject);


            QString pathInternal= Analysis::makeInternalPath(Utils::SAVING_ANALYSIS_PATH, QString::number(id), dataset->getName(), subject.getName(), protocol->getName());
            dir.mkpath(pathInternal);
            QString fileNameInternal= Analysis::makePathFileName(pathInternal, true, feature->getName(), QString::number(feature->getId()), ext);
            writeFeature(fileNameInternal, feature, outputData, subject, protocol);

            showFeature(feature, &subject, fileNameInternal);
            delete outputData;
        }

        //if the protocol has an algorithm execute it
        if(protocol->hasAlgorithm()) {
            AAlgorithm *algorithm = protocol->getAlgorithm();
            RomeoObject* outputData = runAlgorithm(algorithm, image, subject);
            QString pathInternal=Analysis::makeInternalPath(Utils::SAVING_ANALYSIS_PATH, QString::number(id), dataset->getName(), subject.getName(), protocol->getName());
            dir.mkpath(pathInternal);
            QString filenameInternal= Analysis::makePathFileName(pathInternal, false, algorithm->getName(), QString::number(algorithm->getId()), ext);
            writeAlgorithm(filenameInternal, algorithm, outputData, subject, protocol);
            QString description("Subject");
            description.append(subject.getName());
            description.append(" with algorithm ");
            description.append(algorithm->getName());
            showImage(filenameInternal, description);
            //delete outputData;//giusto ma se
        }




    }
    delete image;
}


RomeoObject* Analysis::runFeature(AFeature* feature,RomeoObject *image, ASubject &subject)
{
    if(image) {
        QString text("Executing Feature ");
        text.append(feature->getName());
        text.append(" on Subject ");
        text.append(subject.getName());
        emit resultUpdate(text);
        return feature->executeAnalysis(image);
    }
    return 0;
}

RomeoObject* Analysis::runAlgorithm(AAlgorithm *alg, RomeoObject *image, ASubject &subject)
{
    if(image) {
        QString text("Executing Algorithm ");
        text.append(alg->getName());
        text.append(" on Subject ");
        text.append(subject.getName());
        emit resultUpdate(text);
        return alg->executeAnalysis(image);
    }
    return 0;
}

void Analysis::writeFeature(const QString& pathInternal, AFeature* feature, RomeoObject *image, ASubject &subject, Protocol *protocol)
{
    if(!image)
        return;
    Exporter* writer = 0;
    QDir dir(QDir::homePath());

    QString ext;
    if(subject.getType() == Utils::ROMEO_IMAGE_TYPE_2D || subject.getType() == Utils::ROMEO_IMAGE_TYPE_2Dt)
        ext = "jpg";
    else
        ext = "nii";

    QString pathExternal= Analysis::makeExternalPath(saveDirectory.absolutePath(), Utils::SAVING_ANALYSIS_FOLDER, QString::number(id), dataset->getName(), subject.getName(), protocol->getName());
    QString filenameExternal= Analysis::makePathFileName(pathExternal, true, feature->getName(), QString::number(feature->getId()), ext);

    if(image) {

        if (dynamic_cast<RGBImage2D *>(image)){
            writer=new Exporter2D();
            writer->exportFile(pathInternal,dynamic_cast<RGBImage*>(image));
            if(featuresSave.value(feature->getId(),false)){
                dir.mkpath(pathExternal);
                if(QDir(pathExternal).exists()) {
                    writer->exportFile(filenameExternal,dynamic_cast<RGBImage *>(image));
                }
            }
        }
        else if(dynamic_cast<RGBImage3D *>(image)){
            writer=new Exporter3D();
            writer->exportFile(pathInternal,dynamic_cast<RGBImage *>(image));
            if(featuresSave.value(feature->getId(),false)){
                dir.mkpath(pathExternal);
                if(QDir(pathExternal).exists()) {
                    writer->exportFile(filenameExternal,dynamic_cast<RGBImage *>(image));
                }
            }
        }



    }

    delete writer;

}


void Analysis::writeAlgorithm(const QString& pathInternal, AAlgorithm *alg, RomeoObject *image, ASubject &subject, Protocol *protocol)
{
    if(!image)
        return;
    Exporter* writer = 0;
    QDir dir(QDir::homePath());

    QString ext;

    if(subject.getType() == Utils::ROMEO_IMAGE_TYPE_2D || subject.getType() == Utils::ROMEO_IMAGE_TYPE_2Dt)
        ext = "jpg";
    else
        ext = "nii";

    QString pathExternal=Analysis::makeExternalPath(saveDirectory.absolutePath(), Utils::SAVING_ANALYSIS_FOLDER, QString::number(id), dataset->getName(), subject.getName(), protocol->getName());
    dir.mkpath(pathExternal);
    QString filenameExternal=Analysis::makePathFileName(pathExternal, false, alg->getName(), QString::number(alg->getId()), ext);
    if(image) {
        if (dynamic_cast<RGBImage2D *>(image)){
            writer=new Exporter2D();
            writer->exportFile(pathInternal,dynamic_cast<RGBImage *>(image));
            writer->exportFile(filenameExternal,dynamic_cast<RGBImage *>(image));
        }
        else if (dynamic_cast<RGBImage3D *>(image)){
            writer=new Exporter3D();
            writer->exportFile(pathInternal,dynamic_cast<RGBImage *>(image));
            writer->exportFile(filenameExternal,dynamic_cast<RGBImage *>(image));
        }
    }

    delete writer;

}

void Analysis::showFeature(AFeature *feature, ASubject *subject, const QString &image)
{
    if(featuresShow.value(feature->getId(),false)) {
        QString description("Subject ");
        description.append(subject->getName());
        description.append(" with feature");
        description.append(feature->getName());
        showImage(image, description);
    }

}

void Analysis::showImage(const QString &image, const QString &description)
{
    QImage *newImage = 0;

    if(image.endsWith(".nii") || image.endsWith(".hdr") || image.endsWith(".avi") || image.endsWith(".mpg")) {
        QDir dir;
        if(dir.exists(image)) {
            newImage = getImage3DVideo(image);
        }
    }
    else {
        newImage = new QImage();
        if(!newImage->load(image)) {
           delete newImage;
            newImage = 0;
        }
    }

    if(newImage) {
        emit imageReady(newImage, description);
    }

}


void Analysis::setComplete(bool c)
{
    completed = c;
}

QDateTime Analysis::getCreationDate() const
{
    return creationDate;
}

int Analysis::getID() const {
    return id;
}

void Analysis::setID(int i)
{
    id = i;
}

bool Analysis::getComplete() const {
    return completed;
}

Dataset *Analysis::getDataset() const{
    return dataset;
}

int Analysis::getTotalSubjects() const
{
    return getDataset()->getGroup()->subjectsCount();
}

int Analysis::getSelectedSubjectCount() const
{
    return selectedSubject.size();
}

QVector<QString> Analysis::getSelectedSubject() const
{
    return selectedSubject;
}

QMap<int, bool> Analysis::getFeaturesShow() const
{
    return featuresShow;
}

QMap<int, bool> Analysis::getFeaturesSave() const
{
    return featuresSave;
}

void Analysis::setCreationDate(const QString& date)
{
    creationDate = QDateTime::fromString(date);
}

Analysis::~Analysis()
{
    delete dataset;
}

QString Analysis::makeInternalPath(const QString& path, const QString& id, const QString& datasetName, const QString& subjectName, const QString& protocolName)
{
    QString ret = path+"/D_"+id+"_"+datasetName+"/S_"+subjectName+"/P_"+protocolName;

    return ret;
}

QString Analysis::makeExternalPath(const QString& dir, const QString& folder, const QString& id, const QString& datasetName, const QString& subjectName, const QString& protocolName)
{
    QString ret = dir+"/"+folder+"/D_"+id+"_"+datasetName+"/S_"+subjectName+"/P_"+protocolName;

    return ret;
}

QString Analysis::makePathFileName(const QString &path, bool feature, const QString& objName, const QString& id, const QString& ext)
{
    QString ret = path;
    QString file = QString("/");

    if(feature)
        file.append(QString("F_"));
    else
        file.append(QString("A_"));

    file.append(objName+QString("_")+id+"."+ext);

    return ret.append(file);
}
