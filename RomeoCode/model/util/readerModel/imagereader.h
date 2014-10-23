#ifndef ROMEO_MODEL_UTIL_READERMODEL_IMAGEREADER_H
#define ROMEO_MODEL_UTIL_READERMODEL_IMAGEREADER_H

#include "model/util/readerModel/reader.h"
#include "itkNiftiImageIO.h"
#include <QString>
/*!
 *\file imagereader.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-02-20 |  Scapin Davide  |        Romeo::Model::Core::ReaderModel::ImageReader          |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Util {
            namespace ReaderModel {

                class ImageReader : public Reader
                {
                public:
                    ImageReader();
                    virtual QVector<Reader::RGBImage2DType::Pointer> readFile2D(const QString &readFile) const ;
                    virtual RGBImage3DType::Pointer readFile3D(const QString &readFile) const ;
                };

            } // namespace ReaderModel
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_READERMODEL_IMAGEREADER_H
