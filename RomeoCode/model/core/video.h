#ifndef ROMEO_MODEL_CORE_VIDEO_H
#define ROMEO_MODEL_CORE_VIDEO_H

#include <QString>
#include <QVector>
#include "model/core/internaldata.h"
#include "model/core/romeoobject.h"
#include "model/util/readerModel/videoreader.h"

using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::InternalData;
using Romeo::Model::Util::ReaderModel::VideoReader;

/*!
 *\file video.h
 *\author Martignago Jimmy (jimmy.jimmy@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-20 | Martignago Jimmy |       Romeo::Model::Core::Video    |    First version of class     |
*|                                                                                                               |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
             /*!
             * \brief The Video class represents videos in Romeo.
             */
            class Video : public RomeoObject
            {        
            protected:
                /*!
                 * \brief fileName is the file path of video.
                 */
                QString fileName;
                /*!
                 * \brief reader is the reader for videos.
                 */
                static VideoReader *reader;
            public:
                /*!
                 * \brief Video is one parameters constructor for video.
                 * \param name is the file path of video.
                 */
                Video(const QString &name);


            };

        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_VIDEO_H
