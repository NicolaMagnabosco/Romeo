#include "standarddeviationfeature.h"
#include "itkRescaleIntensityImageFilter.h"

using Romeo::Model::Core::Feature::StandardDeviationFeature;
using Romeo::Model::Core::Feature::FirstOrderFeature;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::Feature::MeanFeature;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;

StandardDeviationFeature::StandardDeviationFeature(int idFeat): FirstOrderFeature(Utils::FEATURE_STANDARD_DEVIATION, idFeat)
{
}

StandardDeviationFeature::StandardDeviationFeature(const QStringList& parameters, int idFeat)
    : FirstOrderFeature(Utils::FEATURE_STANDARD_DEVIATION, parameters, idFeat)
{

}

InternalData2D* StandardDeviationFeature::singleChannelEXecution2D(InternalData2D* channel)
{
    InternalData2D::ImageType::Pointer image = channel->getImage();

    MeanFeature meanFeature(getParameters());
    InternalData2D::ImageType::Pointer meanImg = meanFeature.singleChannelEXecution2D(channel)->getImage();

    InternalData2D* output = new InternalData2D(channel->getXSize(),channel->getYSize());
    InternalData2D::ImageType::Pointer outputImg = output->getImage();

    InternalData2D::NeighborhoodIteratorInternalType::RadiusType radius;
    radius.Fill(getWindowSize()/2);

    InternalData2D::NeighborhoodIteratorInternalType it(radius, image, image->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType outIt(outputImg, outputImg->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType meanIt(meanImg, meanImg->GetRequestedRegion());

    int size = pow(getWindowSize(),2.0);
        for(it.GoToBegin(), outIt.GoToBegin(), meanIt.GoToBegin();
            !it.IsAtEnd();
            ++it, ++outIt, ++meanIt)
        {
            float sum = 0;
            for(int i=0; i<size; ++i){
                float meanValue = meanIt.Value();
                float diff = it.GetPixel(i) - meanValue;
                sum += diff*diff;
            }
            float val2 = sqrt(sum/size);
            outIt.Set(val2);
        }
        //delete channel;
        return output;
}

InternalData3D* StandardDeviationFeature::singleChannelEXecution3D(InternalData3D* channel)
{
    InternalData3D::ImageType::Pointer image = channel->getImage();

    MeanFeature meanFeature(getParameters());
    InternalData3D::ImageType::Pointer meanImg = meanFeature.singleChannelEXecution3D(channel)->getImage();

    InternalData3D* output = new InternalData3D(channel->getXSize(),channel->getYSize(), channel->getZSize());
    InternalData3D::ImageType::Pointer outputImg = output->getImage();

    InternalData3D::NeighborhoodIteratorInternalType::RadiusType radius;
    radius.Fill(getWindowSize()/2);

    InternalData3D::NeighborhoodIteratorInternalType it(radius, image, image->GetRequestedRegion());
    InternalData3D::RegionIteratorInternalType outIt(outputImg, outputImg->GetRequestedRegion());
    InternalData3D::RegionIteratorInternalType meanIt(meanImg, meanImg->GetRequestedRegion());

    int size = pow(getWindowSize(),2.0);
        for(it.GoToBegin(), outIt.GoToBegin(), meanIt.GoToBegin();
            !it.IsAtEnd();
            ++it, ++outIt, ++meanIt)
        {
            float sum = 0;
            for(int i=0; i<size; ++i){
                float meanValue = meanIt.Value();
                float diff = it.GetPixel(i) - meanValue;
                sum += diff*diff;
            }
            float val2 = sqrt(sum/size);
            outIt.Set(val2);
        }
        //delete channel;
        return output;
}

StandardDeviationFeature::~StandardDeviationFeature()
{

}
