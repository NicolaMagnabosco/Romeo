#include "realsubjectimage.h"
#include "model/core/rgbimage2d.h"
#include "model/core/rgbimage3d.h"
#include "model/core/rgbimage.h"
#include "utils.h"

using Utils::ROMEO_IMAGE_TYPE_2D;
using Utils::ROMEO_IMAGE_TYPE_3D;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RealSubjectImage;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RomeoObject;

RealSubjectImage::RealSubjectImage(const QString &type, const QString &image, const QString &mask) : RealSubject()
{
    bool hasMask = !mask.isEmpty();
    if(type == ROMEO_IMAGE_TYPE_2D)
        imageFormat = new RGBImage2D(image, mask,hasMask);
    else
        if(type == ROMEO_IMAGE_TYPE_3D)
            imageFormat = new RGBImage3D(image, mask, hasMask);

}
