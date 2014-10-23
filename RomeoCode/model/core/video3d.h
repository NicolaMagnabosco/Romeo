#ifndef ROMEO_MODEL_CORE_RGBVIDEO3D_H
#define ROMEO_MODEL_CORE_RGBVIDEO3D_H

#include "model/core/video.h"
#include "itkMaskImageFilter.h"
#include "model/core/internaldata3d.h"
#include "model/util/readerModel/videoreader.h"


using Romeo::Model::Core::InternalData3D;
using Romeo::Model::Core::Video;
using Romeo::Model::Util::ReaderModel::VideoReader;
/*!
 *\file video3d.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-03-01
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-03-01 | Martignago Jimmy      Romeo::Model::Core::Video3D     |    First version of class     |
*|                                                                                                               |
*|   0.0.2  | 2013-03-10 | Martignago Jimmy |    Romeo::Model::Core::Video3D     |    Complete the class         |
*|                                                                                                               |
*|   0.0.3  | 2013-03-30 | Martignago Jimmy |    Romeo::Model::Core::Video3D     |Definitive version of the class|
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
        /*!
             * \brief The Video3D class represents 3d video in Romeo.
             */
            class Video3D : public Video
            {
            private:
                /*!
                 * \brief originalVideo is a vector of 3D frames.
                 */
                QVector<InternalData3D*> originalVideo;

            public:
                typedef itk::Image<float,3> ImageType;
                typedef itk::MaskImageFilter<ImageType,ImageType> MaskImageFilterType;
                /*!
                 * \brief Video3D builds a video.
                 * \param fileN is the path of the video.
                 * \param mask is the mask path of the video.
                 * \param hasMask is true if the video has a mask.
                 */
                Video3D(const QString& fileN, const QString& mask="", bool hasMask=false);
                /*!
                 * \brief getXSize gets the width size of video frame.
                 * \return the width size of video frame.
                 */
                int getXSize() const;
                /*!
                 * \brief getYSize gets the height of video frame.
                 * \return the height of video frame.
                 */
                int getYSize() const;
                /*!
                 * \brief getZSize gets the deep size of the video.
                 * \return the deep size of the video.
                 */

                int getZSize() const;
                /*!
                 * \brief getNumberOfFrames gets the number of frames of the video.
                 * \return  number of frames of the video.
                 */
                int getNumberOfFrames() const;
                /*!
                 * \brief getFrame gets a frame of video.
                 * \param i is the number of the frame to get.
                 * \return a image frame.
                 */
                InternalData3D *getFrame(int i) const;
                /*!
                 * \brief maskImage set the image mask.
                 * \param mask is the path of the mask.
                 */
                virtual void maskImage(const QString &mask);
                /*!
                 * \brief ~Video3D delete Video 3D object.
                 */
                virtual ~Video3D();


            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_RGBVIDEO3D_H
