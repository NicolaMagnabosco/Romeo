#ifndef ROMEO_MODEL_CORE_VIDEO2D_H
#define ROMEO_MODEL_CORE_VIDEO2D_H

#include "model/core/video.h"
#include "itkMaskImageFilter.h"
#include "model/core/internaldata2d.h"


using Romeo::Model::Core::InternalData2D;
using Romeo::Model::Core::Video;

/*!
 *\file video2D.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-20 | Martignago Jimmy |     Romeo::Model::Core::Video2D    |    First version of class     |
*|                                                                                                               |
*|   0.0.2  | 2013-03-01 | Martignago Jimmy |     Romeo::Model::Core::Video2D    |    Complete the class         |
*|                                                                                                               |
*|   0.0.3  | 2013-03-30 | Martignago Jimmy |     Romeo::Model::Core::Video2D    |Definitive version of the class|
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The Video2D class represents 2D videos in Romeo.
             */
            class Video2D : public Video
            {
            private:
                /*!
                 * \brief originalVideo is a vector of 2D frames.
                 */
                QVector<InternalData2D*> originalVideo;

            public:
                typedef itk::Image<float,2> ImageType;
                typedef itk::MaskImageFilter<ImageType,ImageType> MaskImageFilterType;
                /*!
                 * \brief Video2D builds a video.
                 * \param fileN is the path of the video.
                 * \param mask is the mask path of the video.
                 * \param hasMask is true if the video has a mask.
                 */
                Video2D(const QString& fileN, const QString& mask="", bool hasMask=false);
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
                 * \brief getNumberOfFrames gets the number of frames of the video.
                 * \return  number of frames of the video.
                 */
                int getNumberOfFrames() const;
                /*!
                 * \brief getFrame gets a frame of video.
                 * \param i is the number of the frame to get.
                 * \return a image frame.
                 */
                InternalData2D *getFrame(int i) const;
                /*!
                 * \brief maskImage set the image mask.
                 * \param mask is the path of the mask.
                 */
                virtual void maskImage(const QString &mask);
                /*!
                 * \brief ~Video2D delete Video 2D object.
                 */
                virtual ~Video2D();


            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_VIDEO2D_H
