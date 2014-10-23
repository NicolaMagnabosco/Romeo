#include "entropyfeature.h"

using Romeo::Model::Core::Feature::SecondOrderFeature;
using Romeo::Model::Core::Feature::EntropyFeature;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;

EntropyFeature::EntropyFeature(int idFeat):SecondOrderFeature(Utils::FEATURE_ENTROPY,idFeat){

}

EntropyFeature::EntropyFeature(const QStringList& parameters, int idFeat)
    :SecondOrderFeature(Utils::FEATURE_ENTROPY,parameters, idFeat){
}

InternalData2D* EntropyFeature::singleChannelEXecution2D(InternalData2D* channel){

    //input image pointer
    InternalData2D::ImageType::Pointer image = channel->getImage();
    //build object to return
    InternalData2D* workingChannel = new InternalData2D(channel->getXSize(),channel->getYSize());
    //output image pointer
    InternalData2D::ImageType::Pointer workingChannelImage = workingChannel->getImage();
    //function that build object that calculate GLCM from a region of input image;
    InternalData2D::ImageToGlcmType::Pointer glcmGenerator = buildGLCMgenerator2D();
    //build the object that calculate the window size's large region of input image
    InternalData2D::ImageType::RegionType window;
    InternalData2D::roiType::Pointer roi=buildRegionOfInterest2D(image,window);
    //index of the pixel to build
    InternalData2D::ImageType::IndexType index;
    //The integer low value of window size / 2
    int halfIntWindow=getWindowSize()/2;
    //number of x and y pixel to iterate
    int xSize=(image->GetLargestPossibleRegion().GetSize(0))-halfIntWindow;
    int ySize=(image->GetLargestPossibleRegion().GetSize(1))-halfIntWindow;
    //the number of GLCM elements
    int size=getGLCMSize()*getGLCMSize();
    float frequency=0;
    int max=INT_MIN;
    //float array [ySize][xSize] ;

    // y axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
    for (int y=halfIntWindow; y<ySize; y++){
        index.SetElement(1,y);
        window.SetIndex(1,y-halfIntWindow);

        //x axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
        for (int x=halfIntWindow; x<xSize; x++){
            index.SetElement(0,x);
            window.SetIndex(0,x-halfIntWindow);

            //sets the windows slice of the image
            roi->SetRegionOfInterest(window);



            //calculate the GLCM of a image's slice
            glcmGenerator->SetInput(roi->GetOutput());

            glcmGenerator->Update();


            //return GLCM histogram
            const InternalData2D::HistogramType* GLCM=glcmGenerator->GetOutput();

            //calculate entropy pixel in "index" position
            float ct = 0;
            for(int i=0;i<size-1;i++){
                frequency=GLCM->GetFrequency(i);
                if(frequency != 0)
                     ct = ct+(frequency*log(frequency));
            }
            if (ct>max)
                max=ct;
            workingChannelImage->SetPixel(index,-ct);
            //array[y][x]=ct;

        }

    }


   /* for(int y=0;y<ySize;y++) {
        for(int x=0;x<xSize;x++){
            index[0]=x;
            index[1]=y;
            workingChannelImage->SetPixel(index,-array[y][x]*255/max);
        }
    }*/
    //Objects deallocation
    glcmGenerator=NULL;
    roi=NULL;

    //return Output InternalData2D image
    return workingChannel;

}
InternalData3D* EntropyFeature::singleChannelEXecution3D(InternalData3D* channel)
{

    //input image pointer
    InternalData3D::ImageType::Pointer image = channel->getImage();
    //build object to return
    InternalData3D* workingChannel = new InternalData3D(channel->getXSize(),channel->getYSize(),channel->getZSize());
    //output image pointer
    InternalData3D::ImageType::Pointer workingChannelImage = workingChannel->getImage();
    //function that build object that calculate GLCM from a region of input image;
    InternalData3D::ImageToGlcmType::Pointer glcmGenerator = buildGLCMgenerator3D();
    //build the object that calculate the window size's large region of input image
    InternalData3D::ImageType::RegionType window;
    InternalData3D::roiType::Pointer roi=buildRegionOfInterest3D(image,window);
    //index of the pixel to build
    InternalData3D::ImageType::IndexType index;
    //The integer low value of window size / 2
    int halfIntWindow=getWindowSize()/2;
    //number of x and y pixel to iterate
    int xSize=(image->GetLargestPossibleRegion().GetSize(0))-halfIntWindow;
    int ySize=(image->GetLargestPossibleRegion().GetSize(1))-halfIntWindow;
    int zSize=(image->GetLargestPossibleRegion().GetSize(2))-halfIntWindow;
    //the number of GLCM elements
    int size=pow(getGLCMSize(),3);
    float frequency=0;
    int max=INT_MIN;
    float array [zSize][ySize][xSize];

    // z axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
    for (int z=halfIntWindow; z<zSize; z++){
        index.SetElement(2,z);
        window.SetIndex(2,z-halfIntWindow);
        //y axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
        for (int y=halfIntWindow; y<ySize; y++){
            index.SetElement(1,y);
            window.SetIndex(1,y-halfIntWindow);
            //z axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
            for (int x=halfIntWindow; x<xSize; x++){
                index.SetElement(0,x);
                window.SetIndex(0,x-halfIntWindow);
                //sets the windows slice of the image
                roi->SetRegionOfInterest(window);
                //calculate the GLCM of an image's slice
                glcmGenerator->SetInput(roi->GetOutput());
                glcmGenerator->Update();
                //return GLCM histogram
                const InternalData2D::HistogramType* GLCM=glcmGenerator->GetOutput();

                //calculate entropy voxel in "index" position
                float ct = 0;
                for(int i=0;i<size-1;i++){
                    frequency=GLCM->GetFrequency(i);
                    if(frequency != 0)
                         ct = ct+(frequency*log(frequency));
                }
                if (ct>max)
                    max=ct;
                array[z][y][x]=ct;

            }
        }
    }
    //pixel normalization
    for(int z=0;z<zSize;z++){
        for(int y=0;y<ySize;y++) {
            for(int x=0;x<xSize;x++){
                index[0]=x;
                index[1]=y;
                index[2]=z;
                workingChannelImage->SetPixel(index,-array[z][y][x]*255/max);
            }
        }
    }
    //Objects deallocation
    glcmGenerator=NULL;
    roi=NULL;

    //return Output InternalData3D image
    return workingChannel;
}
EntropyFeature::~EntropyFeature()
{

}
