#ifndef ROMEO_MODEL_UTIL_READERMODEL_VIDEOREADER_H
#define ROMEO_MODEL_UTIL_READERMODEL_VIDEOREADER_H

#include "model/core/internaldata2d.h"
#include "model/core/internaldata3d.h"
#include "model/util/readerModel/reader.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <itkOpenCVImageBridge.h>
#include <QVector>
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
*|   0.0.1  | 2013-02-20 |  Scapin Davide  | Romeo::Model::Core::Util::ReaderModel::Reader       |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/


namespace Romeo {

    namespace Model {

        namespace Util {

            namespace ReaderModel {

                class VideoReader : public Reader
                {
                public:
                    VideoReader();
                    QVector<Reader::Image2DType::Pointer> read2D(const QString &readFile);
                    virtual QVector<Reader::RGBImage2DType::Pointer> readFile2D(const QString &readFile) const;
                    virtual RGBImage3DType::Pointer readFile3D(const QString &readFile) const ;
                    virtual QVector<Reader::Image3DType::Pointer> read3D(const QString &readFile) const ;
                };

            } // namespace ReaderModel

        } // namespace Util

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_READERMODEL_VIDEOREADER_H
