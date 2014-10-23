#include "rgbimage3d.h"
#include "itkSliceBySliceImageFilter.h"
#include "itkCastImageFilter.h"

using Romeo::Model::Core::RGBImage3D;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Util::ReaderModel::ImageReader;

// Initialization of static member 'reader'
ImageReader* RGBImage3D::reader = new ImageReader();

RGBImage3D::RGBImage3D() {}

RGBImage3D::RGBImage3D(const QString &fileN, const QString &fileMask, bool hasMask)
    : fileName(fileN), maskFileName(fileMask), imageHasMask(hasMask)
{
    // construct the original image (colored)
    originalImage = reader->readFile3D(fileName);
    if(hasMask)
        maskImage(fileMask);
}

RGBImage3D::RGBImage3D(InternalData3D* img)
{
    typedef itk::Image<float,3>ImageType;
    typedef itk::CastImageFilter<ImageType, RGBImageType > CastFilterType;
      CastFilterType::Pointer castFilter = CastFilterType::New();
      castFilter->SetInput(img->getImage());
      castFilter->Update();
      RGBImageType::Pointer newImage = RGBImageType::New();
      newImage=castFilter->GetOutput();
      originalImage=newImage; 
      castFilter=NULL;
}

// Deep-copy constructor
RGBImage3D::RGBImage3D(const RGBImage3D& img)
    : fileName(img.fileName), maskFileName(img.maskFileName), imageHasMask(img.imageHasMask)
{

    // construct the original image (colored)
    originalImage = reader->readFile3D(fileName);
    // if image has a mask
    if(imageHasMask){
        maskImage(maskFileName);
    }

    // intitialize red, green and blue with the same dimension of the originalImage
    redImage = new InternalData3D(getXSize(), getYSize(),getZSize());
    greenImage = new InternalData3D(getXSize(), getYSize(),getZSize());
    blueImage = new InternalData3D(getXSize(), getYSize(),getZSize());

    // now we fill the three image
    RGBExtracter();
}

int RGBImage3D::getXSize() const
{
    RGBImageType::RegionType region = originalImage->GetLargestPossibleRegion();
    return region.GetSize()[0];
}

int RGBImage3D::getYSize() const
{
    RGBImageType::RegionType region = originalImage->GetLargestPossibleRegion();
    return region.GetSize()[1];
}

int RGBImage3D::getZSize() const
{
    RGBImageType::RegionType region = originalImage->GetLargestPossibleRegion();
    return region.GetSize()[2];
}

InternalData* RGBImage3D::getRedImage()
{
    return redImage;
}

InternalData* RGBImage3D::getGreenImage()
{
    return greenImage;
}

InternalData* RGBImage3D::getBlueImage()
{
    return blueImage;
}

void RGBImage3D::RGBExtracter()
{

}

void RGBImage3D::RGBMerger()
{

}

void RGBImage3D::maskImage(const QString &mask)
{
    RGBImageType::Pointer maskImage = reader->readFile3D(mask);
    RGBImage3D::RegionIteratorType originalIt (originalImage, originalImage->GetLargestPossibleRegion());
    RGBImage3D::RegionIteratorType maskIt (maskImage, maskImage->GetLargestPossibleRegion());
    for(originalIt.GoToBegin(), maskIt.GoToBegin(); !originalIt.IsAtEnd(), !maskIt.IsAtEnd();
        ++originalIt, ++maskIt){
        RGBPixel maskPixel = maskIt.Get();
        if(maskPixel.GetScalarValue() == 0){
            RGBPixel pixel;
            pixel.Set(0,0,0);
            originalIt.Set(pixel);
        }
    }
    maskImage = 0;
}

RGBImage3D::RGBImageType::Pointer RGBImage3D::getImage()
{
    return originalImage;
}

RGBImage3D::~RGBImage3D()
{
    originalImage = 0;
}

void RGBImage3D::setImage(RGBImageType::Pointer image){

    originalImage = 0;
    originalImage=image;
}

void RGBImage3D::setImage(ImageType::Pointer image){

    typedef itk::Image<float,3>ImageType;
    typedef itk::CastImageFilter<ImageType, RGBImageType > CastFilterType;
    CastFilterType::Pointer castFilter = CastFilterType::New();
    castFilter->SetInput(image);
    castFilter->Update();
    originalImage=castFilter->GetOutput();

}

QString RGBImage3D::getFileName() const{
    return fileName;
}

QString RGBImage3D::getMaskFileName() const{
    return maskFileName;
}

InternalData3D* RGBImage3D::getGreyScaleImage(){
    RGBImage3D::GrayscaleConverterType::Pointer converter=GrayscaleConverterType::New();
    converter->SetInput(originalImage);
    converter->Update();
    InternalData3D* output = new InternalData3D();
    output->setImage(converter->GetOutput());
    return output;
}

bool RGBImage3D::isMasked() const{
    return imageHasMask;
}

void RGBImage3D::setFileName(QString newFileName)
{
    fileName=newFileName;
}

void RGBImage3D::setMaskFileName(QString newMaskFileName)
{
    maskFileName=newMaskFileName;
}

void RGBImage3D::setImageHasMask(bool newImageHasMask)
{
    imageHasMask=newImageHasMask;
}
