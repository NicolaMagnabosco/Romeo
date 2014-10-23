#include "internaldata2d.h"



using Romeo::Model::Core::InternalData2D;



// Initialization of static member 'duplicator'
InternalData2D::DuplicatorType::Pointer InternalData2D::duplicator = InternalData2D::DuplicatorType::New();

// Definition of static method
InternalData2D::ImageType::Pointer InternalData2D::copyImage(ImageType::Pointer img)
{
    return img->Clone();
}

// Default Constructor
InternalData2D::InternalData2D()
    : image(ImageType::New()){}

// Constructor with size parameters
InternalData2D::InternalData2D(int xsize, int ysize)
    : image(ImageType::New())
{
    ImageType::IndexType index;
    index[0] = 0; // x-axis
    index[1] = 0; // y-axis

    ImageType::SizeType size;
    size[0] = xsize;
    size[1] = ysize;

    ImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(index);

    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);
}

// Deep-copy constructor
InternalData2D::InternalData2D(const InternalData2D& imageToCopy)
    : image(copyImage(imageToCopy.image)){}

// Definition of deep assignment
InternalData2D& InternalData2D::operator= (const InternalData2D& img)
{
    // check if we're not in the case of an "X=X" assignement
    if(this != &img){
        image->Delete();
        image = copyImage(img.image);
    }
    return *this;
}

int InternalData2D::getXSize() const
{
    ImageType::RegionType region = image->GetLargestPossibleRegion();
    return region.GetSize()[0];
}

int InternalData2D::getYSize() const
{
    ImageType::RegionType region = image->GetLargestPossibleRegion();
    return region.GetSize()[1];
}

void InternalData2D::fillBuffer(int value)
{
    image->FillBuffer(value);
}

bool InternalData2D::compareImage(ImageType::Pointer img)
{
    // control if the two images have the same size
    ImageType::RegionType this_region = getImage()->GetLargestPossibleRegion();
    ImageType::SizeType this_size = this_region.GetSize();
    ImageType::RegionType comp_region = img->GetLargestPossibleRegion();
    ImageType::SizeType comp_size = comp_region.GetSize();

    if(this_size[0] != comp_size[0] || this_size[1] != comp_size[1] ){
        // images have not the same size!
        return false;
    }

    // iterator to image represented by class
    LinearIteratorIndexType this_it(getImage(),getImage()->GetLargestPossibleRegion());

    // iterator to the image to compare
    LinearIteratorIndexType comp_it(img, img->GetLargestPossibleRegion());

    bool isEqual = true;
    if(getImage().GetPointer() != img.GetPointer()){
        for(this_it.GoToBegin(), comp_it.GoToBegin();
            !this_it.IsAtEnd(), !comp_it.IsAtEnd(), isEqual;
            ++this_it, ++comp_it){
            if(this_it.Get() != comp_it.Get())
                isEqual = false;
        }
    }
    if(isEqual)
        return true;

    else
        return false;
}

InternalData2D::~InternalData2D()
{
    image = NULL;
}


InternalData2D::ImageType::Pointer& InternalData2D::getImage()
{
    return this->image;
}

void InternalData2D::setImage(ImageType::Pointer img)
{
    image = 0;
    image = img;
}

InternalData2D::RGBImageType * InternalData2D::convertToRGB() const
{
    typedef itk::CastImageFilter<ImageType, RGBImageType > CastFilterType;
      CastFilterType::Pointer castFilter = CastFilterType::New();
      castFilter->SetInput(image);
      castFilter->Update();
      return castFilter->GetOutput();
}

