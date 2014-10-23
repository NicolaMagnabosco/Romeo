#include "secondorderfeature.h"

using Romeo::Model::Core::Feature::SecondOrderFeature;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::RomeoObject;

SecondOrderFeature::SecondOrderFeature(const QString &name, int idFeat)
    : AFeature(name, idFeat),type(Utils::FEATURE_SECOND_ORDER){

}

SecondOrderFeature::SecondOrderFeature(const QString& name, const QStringList& parameters, int idFeat)
    : AFeature(name, idFeat),type(Utils::FEATURE_SECOND_ORDER),GLCMSize(4){
    setParemeters(parameters);
}

RomeoObject *SecondOrderFeature::executeAnalysis(RomeoObject *image)
{
    if (dynamic_cast<RGBImage2D*>(image))
        return execute2DAnalysis(dynamic_cast<RGBImage2D*>(image));
    if (dynamic_cast<RGBImage3D*>(image))
        return execute3DAnalysis(dynamic_cast<RGBImage3D*>(image));
    return image;//se non corrisponde a nessun tipo,restituisce l'immagine di partenza
}

RGBImage2D* SecondOrderFeature::execute2DAnalysis(RGBImage2D* image)
{
    RGBImage2D* output=new RGBImage2D(*image);

    InternalData2D* red = dynamic_cast<InternalData2D*>(output->getRedImage());
    InternalData2D* green = dynamic_cast<InternalData2D*>(output->getGreenImage());
    InternalData2D* blue = dynamic_cast<InternalData2D*>(output->getBlueImage());

    if(red && green && blue){
       red->setImage(singleChannelEXecution2D(red)->getImage());
       green->setImage(singleChannelEXecution2D(green)->getImage());
       blue->setImage(singleChannelEXecution2D(blue)->getImage());
   }

    output->RGBMerger();

    return output;

}

RGBImage3D* SecondOrderFeature::execute3DAnalysis(RGBImage3D *image)
{
    InternalData3D* greyImage = image->getGreyScaleImage();
    RGBImage3D* output = new RGBImage3D(singleChannelEXecution3D(greyImage));

    return output;
}

int SecondOrderFeature::getWindowSize() const
{
    return windowSize;
}

int SecondOrderFeature::getGLCMDistance() const
{
    return GLCMDistance;
}

int SecondOrderFeature::getGLCMSize() const
{
    return GLCMSize;
}

QStringList SecondOrderFeature::getParameters() const
{
    QStringList parameters;
    parameters.append(QString::number(windowSize));
    parameters.append(QString::number(GLCMDistance));
    return parameters;
}

QString SecondOrderFeature::getType() const
{
    return type;
}

void SecondOrderFeature::setParemeters(const QStringList& params)
{
    windowSize = params.at(0).toInt();
    GLCMDistance = params.at(1).toInt();

}

InternalData2D::ImageToGlcmType::Pointer SecondOrderFeature::buildGLCMgenerator2D()
{
    //build glcm generator object
    InternalData2D::ImageToGlcmType::Pointer glcmGenerator=InternalData2D::ImageToGlcmType::New();

    //set offset values for 2D GLCM matrix
    typedef InternalData2D::ImageToGlcmType::OffsetVector OffsetVectorType;
    OffsetVectorType::Pointer points=OffsetVectorType::New();
    InternalData2D::OffsetType offset;
    offset[0]=GLCMDistance; //column
    offset[1]=0; //row
    InternalData2D::OffsetType offset1;
    offset1[0]=0;
    offset1[1]=GLCMDistance;
    points->InsertElement(0,offset);
    points->InsertElement(1,offset1);
    glcmGenerator->SetOffsets(points);

    //set the size of the GLCM matrix
    glcmGenerator->SetNumberOfBinsPerAxis(getGLCMSize()); //reasonable number of bins 32
    glcmGenerator->SetPixelValueMinMax(0, 255); //for input UCHAR pixel type 255

    return glcmGenerator;

}

InternalData3D::ImageToGlcmType::Pointer SecondOrderFeature::buildGLCMgenerator3D()
{
    //build glcm generator object
    InternalData3D::ImageToGlcmType::Pointer glcmGenerator=InternalData3D::ImageToGlcmType::New();

    //set offset values for 3D GLCM matrix
    typedef InternalData3D::ImageToGlcmType::OffsetVector OffsetVectorType;
    OffsetVectorType::Pointer points=OffsetVectorType::New();
    InternalData3D::OffsetType offset;
    offset[0]=GLCMDistance; //column
    offset[1]=0; //row
    offset[2]=0;//z
    InternalData3D::OffsetType offset1;
    offset1[0]=0;
    offset1[1]=GLCMDistance;
    offset1[2]=0;
    InternalData3D::OffsetType offset2;
    offset2[0]=0;
    offset2[1]=0;
    offset2[2]=GLCMDistance;
    points->InsertElement(0,offset);
    points->InsertElement(1,offset1);
    points->InsertElement(2,offset2);
    glcmGenerator->SetOffsets(points);

    //set the size of the GLCM matrix (default 4)
    glcmGenerator->SetNumberOfBinsPerAxis(getGLCMSize());
    glcmGenerator->SetPixelValueMinMax(0, 255); //for input UCHAR pixel type 255

    return glcmGenerator;
}

InternalData2D::roiType::Pointer SecondOrderFeature::buildRegionOfInterest2D(InternalData2D::ImageType::Pointer image,InternalData2D::ImageType::RegionType & window)
{
    //build 2D region of interest object
    InternalData2D::roiType::Pointer roi=InternalData2D::roiType::New();
    roi->SetInput(image);
    InternalData2D::ImageType::RegionType::SizeType size;
    //set the size of the window
    size.Fill(getWindowSize());
    window.SetSize(size);
    return roi;
}

InternalData3D::roiType::Pointer SecondOrderFeature::buildRegionOfInterest3D(InternalData3D::ImageType::Pointer image,InternalData3D::ImageType::RegionType & window)
{
    //build 3D region of interest object
    InternalData3D::roiType::Pointer roi=InternalData3D::roiType::New();
    roi->SetInput(image);
    InternalData3D::ImageType::RegionType::SizeType size;
    //set the size of the window
    size.Fill(getWindowSize());
    window.SetSize(size);
    return roi;
}

SecondOrderFeature::~SecondOrderFeature(){

}


