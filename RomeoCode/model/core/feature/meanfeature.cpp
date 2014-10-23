#include "meanfeature.h"
#include "model/core/rgbimage.h"
#include "model/core/rgbimage2d.h"
#include "model/core/rgbimage3d.h"
#include "itkRescaleIntensityImageFilter.h"

using Romeo::Model::Core::Feature::MeanFeature;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::RGBImage;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;

MeanFeature::MeanFeature(int idFeat): FirstOrderFeature(Utils::FEATURE_MEAN, idFeat) {

}

MeanFeature::MeanFeature(const QStringList& parameters, int idFeat)
    : FirstOrderFeature(Utils::FEATURE_MEAN, parameters, idFeat)
{}

InternalData2D* MeanFeature::singleChannelEXecution2D(InternalData2D* channel)
{

    InternalData2D::ImageType::Pointer image = channel->getImage();
    InternalData2D* workingChannel = new InternalData2D(channel->getXSize(),channel->getYSize());
    InternalData2D::ImageType::Pointer workingChannelImage = workingChannel->getImage();


    InternalData2D::NeighborhoodIteratorInternalType::RadiusType radius;
    radius.Fill(getWindowSize()/2);

    InternalData2D::NeighborhoodIteratorInternalType it(radius, image, image->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType outputIt(workingChannelImage, workingChannelImage->GetRequestedRegion());
    int size = pow(getWindowSize(),2.0);
    for(it.GoToBegin(), outputIt.GoToBegin(); !it.IsAtEnd(); ++it, ++outputIt)
    {
        float sum = 0;
        for(int i=0; i<size; ++i){
            sum = sum + it.GetPixel(i);
        }
        float val = sum / size;
        outputIt.Set(val);

    }
    return workingChannel;
}

InternalData3D* MeanFeature::singleChannelEXecution3D(InternalData3D* channel)
{
    InternalData3D::ImageType::Pointer image = channel->getImage();
    InternalData3D* workingChannel = new InternalData3D(channel->getXSize(),channel->getYSize(), channel->getZSize());
    InternalData3D::ImageType::Pointer workingChannelImage = workingChannel->getImage();


    InternalData3D::NeighborhoodIteratorInternalType::RadiusType radius;
    radius.Fill(getWindowSize()/2);

    InternalData3D::NeighborhoodIteratorInternalType it(radius, image, image->GetRequestedRegion());
    InternalData3D::RegionIteratorInternalType outputIt(workingChannelImage, workingChannelImage->GetRequestedRegion());
    int size = pow(getWindowSize(),3.0);
    for(it.GoToBegin(), outputIt.GoToBegin(); !it.IsAtEnd(); ++it, ++outputIt)
    {
        float sum = 0;
        for(int i=0; i<size; ++i){
            sum = sum + it.GetPixel(i);
        }
        float val = sum / size;
        outputIt.Set(val);

    }

    //delete channel;
    return workingChannel;
}

MeanFeature::~MeanFeature()
{

}
