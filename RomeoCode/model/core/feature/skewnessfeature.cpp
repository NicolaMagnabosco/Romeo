#include "skewnessfeature.h"

using Romeo::Model::Core::Feature::SkewnessFeature;
using Romeo::Model::Core::Feature::StandardDeviationFeature;
using Romeo::Model::Core::Feature::FirstOrderFeature;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::Feature::MeanFeature;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;

SkewnessFeature::SkewnessFeature(int idFeat) : FirstOrderFeature(Utils::FEATURE_SKEWNESS, idFeat){

}

SkewnessFeature::SkewnessFeature(const QStringList& parameters, int idFeat)
    : FirstOrderFeature(Utils::FEATURE_SKEWNESS, parameters, idFeat)
{
}

InternalData2D* SkewnessFeature::singleChannelEXecution2D(InternalData2D* channel)
{
    InternalData2D::ImageType::Pointer image = channel->getImage();

    MeanFeature meanFeature(getParameters());
    InternalData2D::ImageType::Pointer meanImg = meanFeature.singleChannelEXecution2D(channel)->getImage();


    StandardDeviationFeature stdDeviation(getParameters());
    InternalData2D::ImageType::Pointer stdImg = stdDeviation.singleChannelEXecution2D(channel)->getImage();


    InternalData2D* output = new InternalData2D(channel->getXSize(), channel->getYSize());
    InternalData2D::ImageType::Pointer outputImg = output->getImage();

    InternalData2D::NeighborhoodIteratorInternalType::RadiusType radius;
    radius.Fill(getWindowSize()/2);

    InternalData2D::NeighborhoodIteratorInternalType it(radius, image, image->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType outIt(outputImg, outputImg->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType meanIt(meanImg, meanImg->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType stdIt(stdImg, stdImg->GetRequestedRegion());

    int size = pow(getWindowSize(),2.0);
        for(it.GoToBegin(), outIt.GoToBegin(), meanIt.GoToBegin(), stdIt.GoToBegin();
            !it.IsAtEnd(); ++it, ++outIt, ++meanIt,++stdIt)
        {
            // skewness
            float sum3 = 0;
            for(int i=0; i<size; ++i){
                float meanValue = meanIt.Value();
                float x = it.GetPixel(i) - meanValue;
                float y = pow(x,3.0);
                sum3 += y;
            }
            float stdValue = stdIt.Value();
            float val3 = sum3 / size;
            float stdValueAllaTerza = pow(stdValue,3.0);
            outIt.Set(val3/stdValueAllaTerza);
        }
        //delete channel;
        return output;
}

InternalData3D* SkewnessFeature::singleChannelEXecution3D(InternalData3D* channel)
{
    InternalData3D::ImageType::Pointer image = channel->getImage();

    MeanFeature meanFeature(getParameters());
    InternalData3D::ImageType::Pointer meanImg = meanFeature.singleChannelEXecution3D(channel)->getImage();


    StandardDeviationFeature stdDeviation(getParameters());
    InternalData3D::ImageType::Pointer stdImg = stdDeviation.singleChannelEXecution3D(channel)->getImage();


    InternalData3D* output = new InternalData3D(channel->getXSize(), channel->getYSize(), channel->getZSize());
    InternalData3D::ImageType::Pointer outputImg = output->getImage();

    InternalData3D::NeighborhoodIteratorInternalType::RadiusType radius;
    radius.Fill(getWindowSize()/2);

    InternalData3D::NeighborhoodIteratorInternalType it(radius, image, image->GetRequestedRegion());
    InternalData3D::RegionIteratorInternalType outIt(outputImg, outputImg->GetRequestedRegion());
    InternalData3D::RegionIteratorInternalType meanIt(meanImg, meanImg->GetRequestedRegion());
    InternalData3D::RegionIteratorInternalType stdIt(stdImg, stdImg->GetRequestedRegion());

    int size = pow(getWindowSize(),3.0);
        for(it.GoToBegin(), outIt.GoToBegin(), meanIt.GoToBegin(), stdIt.GoToBegin();
            !it.IsAtEnd(); ++it, ++outIt, ++meanIt,++stdIt)
        {
            // skewness
            float sum3 = 0;
            for(int i=0; i<size; ++i){
                float meanValue = meanIt.Value();
                float x = it.GetPixel(i) - meanValue;
                float y = pow(x,3.0);
                sum3 += y;
            }
            float stdValue = stdIt.Value();
            float val3 = sum3 / size;
            float stdValueAllaTerza = pow(stdValue,3.0);
            outIt.Set(val3/stdValueAllaTerza);
        }
        //delete channel;
        return output;
}

SkewnessFeature::~SkewnessFeature()
{

}
