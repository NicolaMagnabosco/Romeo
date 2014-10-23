#include "rgbimage2d.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkTestingComparisonImageFilter.h"

using Romeo::Model::Core::RGBImage2D;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Util::ReaderModel::ImageReader;


// Initialization of static member 'duplicator'
RGBImage2D::DuplicatorType::Pointer RGBImage2D::rgbDuplicator = RGBImage2D::DuplicatorType::New();

// Initialization of static member 'reader'
ImageReader* RGBImage2D::reader = new ImageReader();

// Default constructor
RGBImage2D::RGBImage2D() {}


RGBImage2D::RGBImage2D(const QString& fileN, const QString &mask, bool hasMask)
    : fileName(fileN), maskFileName(mask), imageHasMask(hasMask)
{
    // construct the original image (colored)
    originalImage = reader->readFile2D(fileName).first();
    // if image has a mask
    if(imageHasMask){
        maskImage(mask);
    }

    // intitialize red, green and blue whit the same dimension of the originalImage
    redImage = new InternalData2D(getXSize(), getYSize());
    greenImage = new InternalData2D(getXSize(), getYSize());
    blueImage = new InternalData2D(getXSize(), getYSize());

    // now we fill the three image
    RGBExtracter();
}

bool RGBImage2D::isRGB()const{
    if(!redImage->compareImage(greenImage->getImage()) ||
            !redImage->compareImage(blueImage->getImage()) ||
            !greenImage->compareImage(blueImage->getImage()))
        return false;
    return true;
}

QString RGBImage2D::getMaskFileName()const{
    return maskFileName;
}

bool RGBImage2D::isMasked()const{
    return imageHasMask;
}

// Deep-copy constructor
RGBImage2D::RGBImage2D(const RGBImage2D& img)
    : fileName(img.fileName), maskFileName(img.getMaskFileName()), imageHasMask(img.isMasked())
{

    // construct the original image (colored)
    originalImage = reader->readFile2D(fileName).first();
    // if image has a mask
    if(isMasked()){
        maskImage(maskFileName);
    }

    // intitialize red, green and blue with the same dimension of the originalImage
    redImage = new InternalData2D(getXSize(), getYSize());
    greenImage = new InternalData2D(getXSize(), getYSize());
    blueImage = new InternalData2D(getXSize(), getYSize());

    // now we fill the three image
    RGBExtracter();
}

RGBImage2D::RGBImage2D(InternalData2D* img){
    typedef itk::Image<float,2>ImageType;
    typedef itk::CastImageFilter<ImageType, RGBImageType > CastFilterType;
      CastFilterType::Pointer castFilter = CastFilterType::New();
      castFilter->SetInput(img->getImage());
      castFilter->Update();
      RGBImageType::Pointer newImage = RGBImageType::New();
      newImage=castFilter->GetOutput();
      originalImage=newImage;
      castFilter=NULL;
      redImage=0;
      greenImage=0;
      blueImage=0;
}


// Definition of deep assignment
RGBImage2D& RGBImage2D::operator= (const RGBImage2D& img)
{
    if(this != &img){
        originalImage=NULL;
        delete redImage;
        delete greenImage;
        delete blueImage;

        originalImage = copyImage(img.originalImage);
        redImage = img.redImage;
        greenImage = img.greenImage;
        blueImage = img.blueImage;
    }
    return *this;
}

// Definition of statid method copyImage
RGBImage2D::RGBImageType::Pointer RGBImage2D::copyImage(RGBImageType::Pointer img)
{
    rgbDuplicator->SetInputImage(img);
    rgbDuplicator->Update();
    return rgbDuplicator->GetOutput();
}

int RGBImage2D::getXSize() const
{
    RGBImageType::RegionType region = originalImage->GetLargestPossibleRegion();
    return region.GetSize()[0];
}

int RGBImage2D::getYSize() const
{
    RGBImageType::RegionType region = originalImage->GetLargestPossibleRegion();
    return region.GetSize()[1];
}

InternalData* RGBImage2D::getRedImage()
{
    return redImage;
}

InternalData* RGBImage2D::getGreenImage()
{
    return greenImage;
}

InternalData* RGBImage2D::getBlueImage()
{
    return blueImage;
}

void RGBImage2D::RGBExtracter()
{
    RegionIteratorType1 originalIt(this->originalImage, this->originalImage->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType redIt(redImage->getImage(), originalImage->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType greenIt(greenImage->getImage(), greenImage->getImage()->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType blueIt(blueImage->getImage(), blueImage->getImage()->GetRequestedRegion());

    for(originalIt.GoToBegin(), redIt.GoToBegin(), greenIt.GoToBegin(), blueIt.GoToBegin();
        !originalIt.IsAtEnd();
        ++originalIt, ++redIt, ++greenIt, ++blueIt)
    {
        RGBPixel onePixel = originalIt.Get();
        RGBPixel::ValueType red = onePixel.GetRed();
        RGBPixel::ValueType green = onePixel.GetGreen();
        RGBPixel::ValueType blue = onePixel.GetBlue();
        redIt.Set(red);
        greenIt.Set(green);
        blueIt.Set(blue);

    }
}

void RGBImage2D::RGBMerger()
{
    RegionIteratorType1 originalIt(this->originalImage, this->originalImage->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType redIt(redImage->getImage(), redImage->getImage()->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType greenIt(greenImage->getImage(), greenImage->getImage()->GetRequestedRegion());
    InternalData2D::RegionIteratorInternalType blueIt(blueImage->getImage(), blueImage->getImage()->GetRequestedRegion());

    for(originalIt.GoToBegin(), redIt.GoToBegin(), greenIt.GoToBegin(), blueIt.GoToBegin();
        !originalIt.IsAtEnd();
        ++originalIt, ++redIt, ++greenIt, ++blueIt)
    {
        RGBPixel onePixel;
        RGBPixel::ValueType red = redIt.Get();
        onePixel.SetRed(red);
        RGBPixel::ValueType green = greenIt.Get();
        onePixel.SetGreen(green);
        RGBPixel::ValueType blue = blueIt.Get();
        onePixel.SetBlue(blue);
        originalIt.Set(onePixel);
    }
}

RGBImage2D::RGBImageType::Pointer RGBImage2D::getImage()
{
    return this->originalImage;
}

RGBImage2D::ImageType::Pointer RGBImage2D::getGreyscaleImage()
{
    RGBImage2D::GrayscaleConverterType::Pointer converter=GrayscaleConverterType::New();
    converter->SetInput(originalImage);
    converter->Update();
    return converter->GetOutput();
}

void RGBImage2D::setImage(RGBImageType::Pointer newImage)
{
    originalImage = 0;
    originalImage = newImage;
}

void RGBImage2D::maskImage(const QString &mask)
{
    MaskImageFilterType::Pointer maskFilter = MaskImageFilterType::New();
    maskFilter->SetCoordinateTolerance(10);
    maskFilter->SetDirectionTolerance(10);

    RGBImageType::Pointer maskImage = reader->readFile2D(mask).first();
    maskFilter->SetInput(originalImage);
    maskFilter->SetMaskImage(maskImage);
    maskFilter->Update();
    originalImage = maskFilter->GetOutput();

}

QString RGBImage2D::getFileName() const{
    return fileName;
}


void RGBImage2D::setFileName(QString newFileName)
{
    fileName=newFileName;
}

void RGBImage2D::setMaskFileName(QString newMaskFileName)
{
    maskFileName=newMaskFileName;
}

void RGBImage2D::setImageHasMask(bool newImageHasMask)
{
    imageHasMask=newImageHasMask;
}

RGBImage2D::~RGBImage2D()
{

    originalImage = NULL;

    if(redImage)
        delete redImage;
    if(greenImage)
            delete greenImage;
    if(blueImage)
        delete blueImage;
}
