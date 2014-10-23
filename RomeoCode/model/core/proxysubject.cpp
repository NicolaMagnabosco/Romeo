#include "proxysubject.h"
#include "utils.h"
#include "model/core/realsubjectimage.h"
#include "model/core/realsubjectvideo.h"

using Romeo::Model::Core::ProxySubject;
using Romeo::Model::Core::RealSubject;
using Romeo::Model::Core::RealSubjectImage;
using Romeo::Model::Core::RealSubjectVideo;

ProxySubject::ProxySubject(const QString &subjectName, const QString &subjectImage, const QString &type, const QString &subjectMask, const QDateTime& dateTime): ASubject(subjectName, subjectImage, type, subjectMask, dateTime), realSubject(0)
{
}

RealSubject * ProxySubject::getRealSubject()
{
    //check if realSubject already exists.
    if(!realSubject) {

        QString type = getType();
        QString image = getImage();
        QString mask = getMask();
        if(type == Utils::ROMEO_IMAGE_TYPE_2D || type == Utils::ROMEO_IMAGE_TYPE_3D) {
            realSubject = new RealSubjectImage(type, image, mask);
        }
        else
            if(type == Utils::ROMEO_IMAGE_TYPE_2Dt || type == Utils::ROMEO_IMAGE_TYPE_3Dt) {
                realSubject = new RealSubjectVideo(type, image, mask);
            }

    }
    //return the instance
    return realSubject;
}

Romeo::Model::Core::RomeoObject *ProxySubject::getImageFormat()
{

    //obtain the realSubject instance (create it if doesn't already exists)
    RealSubject *realSubject = getRealSubject();
    //call the method on the instance
    return realSubject->getImageFormat();
}

ProxySubject::~ProxySubject()
{
    //it the realSubject exists, it have to be deallocated
    if(realSubject)
        delete realSubject;
}
