#include "realsubjectvideo.h"
#include "utils.h"

using Romeo::Model::Core::RealSubjectVideo;
using Utils::ROMEO_IMAGE_TYPE_2Dt;
using Utils::ROMEO_IMAGE_TYPE_3Dt;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::Video3D;

RealSubjectVideo::RealSubjectVideo(const QString &type, const QString &image, const QString &mask) : RealSubject()
{
    bool hasMask = !mask.isEmpty();
    if(type == ROMEO_IMAGE_TYPE_2Dt)
        imageFormat = new Video2D(image, mask,hasMask);
    else
        if(type == ROMEO_IMAGE_TYPE_3Dt)
            imageFormat = new Video3D(image, mask, hasMask);


}
