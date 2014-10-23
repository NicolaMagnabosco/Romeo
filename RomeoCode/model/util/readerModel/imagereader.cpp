#include "imagereader.h"

using Romeo::Model::Util::ReaderModel::Reader;
using Romeo::Model::Util::ReaderModel::ImageReader;


ImageReader::ImageReader(): Reader()
{

}

QVector<Reader::RGBImage2DType::Pointer> ImageReader::readFile2D(const QString &readFile) const
{
    QVector<Reader::RGBImage2DType::Pointer> image;
    typedef itk::ImageFileReader<RGBImage2DType> ReaderType;

    ReaderType::Pointer reader = ReaderType::New();

    reader->SetFileName(readFile.toStdString().c_str());

    try{
        reader->Update();
    } catch(itk::ExceptionObject& exc){
    }


    image.append(reader->GetOutput());

    return image;
}

Reader::RGBImage3DType::Pointer ImageReader::readFile3D(const QString &readFile) const {

    typedef itk::ImageFileReader<RGBImage3DType> ReaderType;
    ReaderType::Pointer reader = ReaderType::New();

    reader->SetFileName(readFile.toStdString().c_str());
    try{
        reader->Update();
    }catch(itk::ExceptionObject& exc){
    }

    RGBImage3DType::Pointer image = reader->GetOutput();

    return image;
}
