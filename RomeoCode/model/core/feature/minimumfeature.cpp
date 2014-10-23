#include "minimumfeature.h"

using Romeo::Model::Core::Feature::DynamicFeature;
using Romeo::Model::Core::Feature::MinimumFeature;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::Video3D;
using Romeo::Model::Core::RGBImage3D;

MinimumFeature::MinimumFeature(int idFeat) : DynamicFeature(Utils::FEATURE_MINIMUM,idFeat){

}

MinimumFeature::MinimumFeature(const QStringList& parameters, int idFeat)
    :DynamicFeature(Utils::FEATURE_MINIMUM,parameters, idFeat){
}


RGBImage2D* MinimumFeature:: execute2DAnalysis(Video2D *video)
{
    if (getEndFrame() >= video->getNumberOfFrames())
        setEndFrame(video->getNumberOfFrames()-1);
    if (initialFrame >= endFrame) {
        initialFrame=0;
        endFrame=video->getNumberOfFrames()-1;
    }
    int xSize= video->getXSize();
    int ySize=video->getYSize();

    InternalData2D *output =new InternalData2D(xSize,ySize);


    InternalData2D::RegionIteratorInternalType outputIt(output->getImage(),output->getImage()->GetRequestedRegion());
    outputIt.GoToBegin();

    InternalData2D::ImageType::IndexType pixelIndex= {{0,0}};
    for(int y=0;y<ySize;y++){
        for (int x=0;x<xSize;x++,++outputIt){
            pixelIndex[0]=x;
            pixelIndex[1]=y;
            int min=INT_MAX;
            int val=0;

            for(int i=getInitialFrame(); i<getEndFrame();i++){
                val=video->getFrame(i)->getImage()->GetPixel(pixelIndex);
                if (val<min){
                    min=val;
                }
            }
        outputIt.Set(min);
        }
    }
    RGBImage2D* out=new RGBImage2D(output);

    //Objects deallocation
    delete output;

    return out;

}

RGBImage3D* MinimumFeature:: execute3DAnalysis(Video3D *video)
{

    if (getEndFrame() >= video->getNumberOfFrames())
        setEndFrame(video->getNumberOfFrames()-1);
    if (initialFrame >= endFrame) {
        initialFrame=0;
        endFrame=video->getNumberOfFrames()-1;
    }

    int xSize= video->getXSize();
    int ySize=video->getYSize();
    int zSize=video->getZSize();

    InternalData3D *output =new InternalData3D(xSize,ySize,zSize);


    InternalData3D::RegionIteratorInternalType outputIt(output->getImage(),output->getImage()->GetRequestedRegion());

    outputIt.GoToBegin();

    InternalData3D::ImageType::IndexType pixelIndex= {{0,0,0}};
    for(int z=0;z<zSize;z++){
        for(int y=0;y<ySize;y++){
            for (int x=0;x<xSize;x++,++outputIt){
                pixelIndex[0]=x;
                pixelIndex[1]=y;
                pixelIndex[2]=z;
                int min=INT_MAX;
                int val=0;

                for(int i=getInitialFrame(); i<getEndFrame();i++){
                    val=video->getFrame(i)->getImage()->GetPixel(pixelIndex);
                    if (val<min){
                        min=val;
                    }
                }
            outputIt.Set(min);
            }
        }
    }
    RGBImage3D* out=new RGBImage3D(output);

    //Objects deallocation
    delete output;

    return out;

}




MinimumFeature::~MinimumFeature(){

}
