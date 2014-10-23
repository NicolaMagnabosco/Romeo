#ifndef ROMEO_MODEL_UTIL_READERMODEL_READER_H
#define ROMEO_MODEL_UTIL_READERMODEL_READER_H

#include <QString>
#include <QDir>
#include <QVector>
#include <itkDataObject.h>
#include <itkObject.h>
#include <itkImageFileReader.h>
#include <itkRGBPixel.h>
/*!
 *\file reader.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-02-20 |  Scapin Davide  |  Romeo::Model::Core::Util::ReaderModel::Reader      |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Util {

            namespace ReaderModel {

                class Reader
                {
                public:
                    typedef itk::RGBPixel<unsigned char> RGBPixelType;
                    typedef itk::Image<RGBPixelType,2> RGBImage2DType;
                    typedef itk::Image<float,2> Image2DType;
                    typedef itk::Image<float,3> Image3DType;
                    typedef itk::Image<RGBPixelType,3>RGBImage3DType;

                    virtual QVector<Reader::RGBImage2DType::Pointer> readFile2D(const QString& readFile) const=0;
                    virtual RGBImage3DType::Pointer readFile3D(const QString& readFile) const=0;

                public:
                    Reader();
                };

            } // namespace ReaderModel
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_READERMODEL_READER_H
