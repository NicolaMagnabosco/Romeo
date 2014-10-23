#include "correlationfeature.h"

using Romeo::Model::Core::Feature::SecondOrderFeature;
using Romeo::Model::Core::Feature::CorrelationFeature;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;


CorrelationFeature::CorrelationFeature(int idFeat):SecondOrderFeature(Utils::FEATURE_CORRELATION,idFeat){

}

CorrelationFeature::CorrelationFeature(const QStringList& parameters, int idFeat)
    :SecondOrderFeature(Utils::FEATURE_CORRELATION,parameters, idFeat){
}

float* CorrelationFeature:: meanIndexI (const InternalData2D::HistogramType* GLCM,int size){
    float ct=0;
    float* array=new float[size];
    for (int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            ct = ct+ ((i+1) * GLCM->GetFrequency(size*j+i));
        }
        array[i] = ct;
        ct = 0;
    }
    return array;
}

float* CorrelationFeature::stdIndexI(const InternalData2D::HistogramType* GLCM,int size,float*m){
    float ct = 0;
    float* array=new float[size];
    for(int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            ct = ct + (GLCM->GetFrequency(size*j+i)* pow((i+1)-m[i],2));
        }
        array[i] = sqrt(ct);
        ct = 0;
    }
    return array;
}

float* CorrelationFeature:: meanIndexJ (const InternalData2D::HistogramType* GLCM,int size){
    float ct=0;
    float* array=new float[size];
    for (int j=0;j<size;j++){
        for(int i=0;i<size;i++){
            ct = ct+ ((j+1) * (GLCM->GetFrequency(size*j+i)));
        }
        array[j] = ct;
        ct = 0;
    }
    return array;
}

float* CorrelationFeature:: stdIndexJ(const InternalData2D::HistogramType* GLCM,int size,float*m){
    float ct = 0;
    float* array=new float[size];
    for(int j=0;j<size;j++){
        for (int i=0;i<size;i++){
            ct = ct + (GLCM->GetFrequency(size*j+i)* pow((j+1)-m[j],2));
        }
        array[j] = sqrt(ct);
        ct = 0;
    }
    return array;
}


InternalData2D* CorrelationFeature::singleChannelEXecution2D(InternalData2D* channel){

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

            //calculate Correlation pixel in "index" position
            float* Mi=meanIndexI(GLCM,size);
            float* Si=stdIndexI(GLCM,size,Mi);

            float* Mj=meanIndexJ(GLCM,size);
            float* Sj=stdIndexJ(GLCM,size,Mj);

            float ct1=0;
            float ct2=0;
            for (int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    ct1 = GLCM->GetFrequency(size*j+i) * ((i+1)-Mi[i])*((j+1)-Mj[j]);


                    if ((Si[i] * Sj[j])!=0)
                        ct2 =  ct2 + (ct1 / (Si[i] * Sj[j]));
                    else
                        ct2=ct2 + ct1;

                }
            }
            if (ct2>max)
                max=ct2;
            //array[y][x]=ct2;
            workingChannelImage->SetPixel(index,ct2);
            //delete unused arrays.
            delete Mi;
            delete Si;
            delete Mj;
            delete Sj;
        }

    }


   /* for(int y=0;y<ySize;y++) {
        index[1]=y;
        for(int x=0;x<xSize;x++){
            index[0]=x;
            workingChannelImage->SetPixel(index,array[y][x]*255/max);
        }
    }*/
    //Objects deallocation
    glcmGenerator=NULL;
    roi=NULL;


    //return Output InternalData2D image
    return workingChannel;

}
InternalData3D* CorrelationFeature::singleChannelEXecution3D(InternalData3D* channel)
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
    int max=INT_MIN;
    float array [zSize][ySize][xSize];

    // x axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
    for (int x=halfIntWindow; x<xSize; x++){
        index.SetElement(0,x);
        window.SetIndex(0,x-halfIntWindow);

        //y axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
        for (int y=halfIntWindow; y<ySize; y++){
            index.SetElement(1,y);
            window.SetIndex(1,y-halfIntWindow);

            //z axis iteration (iteration starts half windows before the begin and finishes after the end of the image)
            for (int z=halfIntWindow; z<zSize; z++){
                index.SetElement(2,z);
                window.SetIndex(2,z-halfIntWindow);
                //sets the windows slice of the image
                roi->SetRegionOfInterest(window);
                //calculate the GLCM of an image's slice
                glcmGenerator->SetInput(roi->GetOutput());
                glcmGenerator->Update();
                //return GLCM histogram
                const InternalData2D::HistogramType* GLCM=glcmGenerator->GetOutput();
                //calculate Correlation voxel in "index" position
                float* Mi=meanIndexI(GLCM,size);
                float* Si=stdIndexI(GLCM,size,Mi);

                float* Mj=meanIndexJ(GLCM,size);
                float* Sj=stdIndexJ(GLCM,size,Mj);

                float ct1=0;
                float ct2=0;
                for (int i=0;i<size;i++){
                    for(int j=0;j<size;j++){
                        ct1 = GLCM->GetFrequency(size*j+i) * ((i+1)-Mi[i])*((j+1)-Mj[j]);

                        if ((Si[i] * Sj[j])!=0)
                            ct2 =  ct2 + (ct1 / (Si[i] * Sj[j]));
                    }

                }
                if (ct2>max)
                    max=ct2;
                if(ct2<0)
                    ct2=0;
                array[z][y][x]=ct2;

                delete Mi;
                delete Si;
                delete Mj;
                delete Sj;
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
                workingChannelImage->SetPixel(index,array[z][y][x]*255/max);

            }
        }
    }
    //Objects deallocation
    glcmGenerator=NULL;
    roi=NULL;


    //return Output InternalData3D image
    return workingChannel;
}
CorrelationFeature::~CorrelationFeature()
{

}
