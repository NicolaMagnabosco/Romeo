#include "afeature.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"

using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::Video;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::Video3D;
using Romeo::Model::Core::RomeoObject;


AFeature::AFeature(const QString &featureName, int idFeat): name(featureName), id(idFeat) {}

AFeature::~AFeature(){}

QString AFeature::getName() const
{
    return name;
}

int AFeature::getId() const {
    return id;
}

void AFeature::setId(int i) {
    id = i;
}
