#include "videoreader.h"
#include "itkExtractImageFilter.h"

using itk::ExtractImageFilter;
using Romeo::Model::Util::ReaderModel::VideoReader;
using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Util::ReaderModel::Reader;

VideoReader::VideoReader()
{

}

QVector<Reader::RGBImage2DType::Pointer> VideoReader::readFile2D(const QString &readFile) const {
    cv::VideoCapture vidCap( readFile.toStdString() );
    cv::Mat frame;
    QVector<Reader::RGBImage2DType::Pointer> video;
    while( vidCap.read(frame) ) {
        video.append(itk::OpenCVImageBridge::CVMatToITKImage< Reader::RGBImage2DType >( frame ));
    }
    return video;
}

QVector<Reader::Image2DType::Pointer> VideoReader::read2D(const QString &readFile)
{
    cv::VideoCapture vidCap( readFile.toStdString() );
    cv::Mat frame;
    QVector<Reader::Image2DType::Pointer> video;
    while( vidCap.read(frame) ) {
        video.append(itk::OpenCVImageBridge::CVMatToITKImage< Reader::Image2DType >( frame ));
    }
    return video;
}


VideoReader::RGBImage3DType::Pointer VideoReader::readFile3D(const QString &readFile)  const
{

       return 0;
}

QVector<Reader::Image3DType::Pointer> VideoReader::read3D(const QString &readFile) const
{
    typedef itk::Image<float, 4> ImageTypeVideo;
    typedef itk::ImageFileReader<ImageTypeVideo> ReaderType;
    typedef itk::Image<float, 3> ImageType3D;
    typedef itk::ExtractImageFilter<ImageTypeVideo,ImageType3D> ExtractType;

    //read video in 4 dimension Image
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(readFile.toStdString().c_str());//./PET_FLT_73_fast.niiT1_brain.nii
    reader->Update();

    ImageTypeVideo::Pointer video = reader->GetOutput();
    ImageTypeVideo::RegionType inputRegion=video->GetLargestPossibleRegion();
    int numberOfFrame =inputRegion.GetSize()[3];
    QVector<ImageType3D::Pointer> vector;
    for(int i=0;i<numberOfFrame;i++){

        ExtractType::Pointer extractor=ExtractType::New();
        extractor->InPlaceOn();
        extractor->SetDirectionCollapseToSubmatrix();


        ImageTypeVideo::SizeType size = inputRegion.GetSize();
        size[3] = 0;
        ImageTypeVideo::IndexType start = inputRegion.GetIndex();
        start[3] = i;
        ImageTypeVideo::RegionType desiredRegion;
        desiredRegion.SetSize(  size  );
        desiredRegion.SetIndex( start );
        extractor->SetExtractionRegion( desiredRegion );
        extractor->SetInput( video );
        extractor->Update();
        vector.append(extractor->GetOutput());
    }
    return vector;
}
