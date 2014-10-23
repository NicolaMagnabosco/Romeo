#include "internaldata3d.h"
#include "itkRGBToLuminanceImageFilter.h"

using Romeo::Model::Core::InternalData3D;


InternalData3D::ImageType::Pointer InternalData3D::copyImage(ImageType::Pointer img)
{
    return img->Clone();
}

// Default Constructor
InternalData3D::InternalData3D()
    : image(ImageType::New()) {}

InternalData3D::InternalData3D(int xsize, int ysize, int zsize)
    : image(ImageType::New())
{
    ImageType::IndexType index;
    index[0] = 0; // x-axis
    index[1] = 0; // y-axis
    index[2] = 0; // z-axis

    ImageType::SizeType size;
    size[0] = xsize;
    size[1] = ysize;
    size[2] = zsize;

    ImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(index);

    image->SetRegions(region);
    image->Allocate();
}

InternalData3D::InternalData3D(RGBImageType::Pointer rgb)
{
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image<float,3>ImageType;
    typedef itk::Image<RGBPixelType,3>RGBImageType;
    typedef itk::RGBToLuminanceImageFilter<RGBImageType, ImageType> CastFilterType;
    CastFilterType::Pointer castFilter= CastFilterType::New();
    castFilter->SetInput(rgb);
    castFilter->Update();
    image=castFilter->GetOutput();
}

// Deep-copy constructor
InternalData3D::InternalData3D(const InternalData3D& imageToCopy)
    : image(imageToCopy.image->Clone()){}

int InternalData3D::getXSize() const
{
    ImageType::RegionType region = image->GetLargestPossibleRegion();
    return region.GetSize()[0];
}

int InternalData3D::getYSize() const
{
    ImageType::RegionType region = image->GetLargestPossibleRegion();
    return region.GetSize()[1];
}

int InternalData3D::getZSize() const
{
    ImageType::RegionType region = image->GetLargestPossibleRegion();
    return region.GetSize()[2];
}

InternalData3D::ImageType::Pointer InternalData3D::getImage()
{
    return image;
}


InternalData3D::~InternalData3D()
{
    image=NULL;
}

void InternalData3D::setImage(ImageType::Pointer img)
{
    image=img;
}
