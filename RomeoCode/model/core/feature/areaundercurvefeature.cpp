#include "areaundercurvefeature.h"

using Romeo::Model::Core::Feature::DynamicFeature;
using Romeo::Model::Core::Feature::AreaUnderCurveFeature;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::Video2D;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::Video3D;
using Romeo::Model::Core::RGBImage3D;


AreaUnderCurveFeature::AreaUnderCurveFeature(int idFeat) : DynamicFeature(Utils::FEATURE_AREA_UNDER_CURVE,idFeat){

}

AreaUnderCurveFeature::AreaUnderCurveFeature(const QStringList& parameters, int idFeat)
    :DynamicFeature(Utils::FEATURE_AREA_UNDER_CURVE,parameters, idFeat){
}


RGBImage2D* AreaUnderCurveFeature:: execute2DAnalysis(Video2D *video)
{

    if (getEndFrame() >= video->getNumberOfFrames())
        setEndFrame(video->getNumberOfFrames()-1);
    if (getInitialFrame() >= getEndFrame()) {
        initialFrame=0;
        endFrame=video->getNumberOfFrames()-1;
    }

    int xSize= video->getXSize();
    int ySize=video->getYSize();


    InternalData2D *output =new InternalData2D(xSize,ySize);


    InternalData2D::RegionIteratorInternalType outputIt(output->getImage(),output->getImage()->GetRequestedRegion());
    outputIt.GoToBegin();

    int max=INT_MIN;
    int array [ySize][xSize];

    InternalData2D::ImageType::IndexType pixelIndex= {{0,0}};
    for(int y=0;y<ySize;y++){
        for (int x=0;x<xSize;x++,++outputIt){
            pixelIndex[0]=x;
            pixelIndex[1]=y;
            int x1=-1;
            int x2=-1;
            int auc=0;

            for(int i=getInitialFrame(); i<getEndFrame();i++){
                x1=x2;
                x2=video->getFrame(i)->getImage()->GetPixel(pixelIndex);
                if (x1>-1){
                    auc=auc+((x1+x2)/2);
                }
            }
            if (auc>max)
                max=auc;
            if(auc<0)
                auc=0;
        array[y][x]=auc;

        }
    }


    for(int y=0;y<ySize;y++) {
        pixelIndex[1]=y;
        for(int x=0;x<xSize;x++){
            pixelIndex[0]=x;

            outputIt.SetIndex(pixelIndex);
            outputIt.Set(array[y][x]*255/max);
        }
    }


    //convert in RGBImage
    RGBImage2D* out=new RGBImage2D(output);
    //Objects deallocation
    delete output;

    return out;

}

RGBImage3D* AreaUnderCurveFeature::execute3DAnalysis(Video3D* video)
{

    if (getEndFrame() >= video->getNumberOfFrames())
        setEndFrame(video->getNumberOfFrames()-1);
    if (getInitialFrame() >= getEndFrame()) {
        initialFrame=0;
        endFrame=video->getNumberOfFrames()-1;
    }

    int xSize= video->getXSize();
    int ySize=video->getYSize();
    int zSize=video->getZSize();


    InternalData3D *output =new InternalData3D(xSize,ySize,zSize);


    InternalData3D::RegionIteratorInternalType outputIt(output->getImage(),output->getImage()->GetRequestedRegion());
    outputIt.GoToBegin();

    int max=INT_MIN;
    int array [zSize][ySize][xSize];

    InternalData3D::ImageType::IndexType pixelIndex= {{0,0,0}};
    for(int z=0;z<zSize;z++){
        pixelIndex[2]=z;
        for(int y=0;y<ySize;y++){
            pixelIndex[1]=y;
            for (int x=0;x<xSize;x++){
                pixelIndex[0]=x;

                int x1=-1;
                int x2=-1;
                int auc=0;

                for(int i=getInitialFrame(); i<getEndFrame();i++){
                    x1=x2;
                    x2=video->getFrame(i)->getImage()->GetPixel(pixelIndex);
                    if (x1>-1){
                        auc=auc+((x1+x2)/2);
                    }
                }
                if (auc>max)
                    max=auc;
                if(auc<0)
                    auc=0;
            array[z][y][x]=auc;

            }
        }
    }
    for (int z=0;z<zSize;z++){
        pixelIndex[2]=z;
        for(int y=0;y<ySize;y++) {
            pixelIndex[1]=y;
            for(int x=0;x<xSize;x++){
                pixelIndex[0]=x;

                outputIt.SetIndex(pixelIndex);
                outputIt.Set(array[z][y][x]*255/max);

            }
        }
    }

    //convert in RGBImage
    RGBImage3D* out=new RGBImage3D(output);
    //Objects deallocation
    delete output;

    return out;
}

AreaUnderCurveFeature::~AreaUnderCurveFeature(){

}

