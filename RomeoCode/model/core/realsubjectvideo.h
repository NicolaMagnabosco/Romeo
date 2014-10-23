#ifndef ROMEO_MODEL_CORE_REALSUBJECTVIDEO_H
#define ROMEO_MODEL_CORE_REALSUBJECTVIDEO_H

#include <QString>
#include "model/core/realsubject.h"
#include "model/core/romeoobject.h"
#include "model/core/video2d.h"
#include "model/core/video3d.h"

/*!
 *\file realsubjectvideo.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-05-10
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                         Changes                      +       Description         |
*+----------+------------+-----------------+------------------------------------------------------+---------------------------+                                                                                                    |
*|   0.0.1  | 2013-05-10 |   Adami Alberto |          Romeo::Model::Core::RealSubjectVideo        |   First version of class  |
*|                                                                                                                            |
*|   1.0.0  | 2013-05-20 |  Adami Albrerto |          Romeo::Model::Core::RealSubjectVideo        |Definitive version of class|
*+----------+------------+-----------------+------------------------------------------------------+---------------------------+
*/

using Romeo::Model::Core::RealSubject;
using Romeo::Model::Core::RomeoObject;

namespace Romeo {

    namespace Model {

        namespace Core {   
            /*!
             * \brief The RealSubjectImage class represent a RealSubject for a video(2D-t, 3D-t).
             * It's a concrete class.
             */
            class RealSubjectVideo : public RealSubject
            {
            public:
                /*!
                 * \brief Constructs a RealSubject object with the given type, image and mask.
                 * \param type represent the type of the Subject (2D-t, 3D-t in this case).
                 * \param image represent the path of the image.
                 * \param mask represent the path of the subject's mask.
                 * If the subject has not a mask, the mask object is an empty string("").
                 */
                RealSubjectVideo(const QString &type, const QString &image, const QString& mask="");
            };

        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_REALSUBJECT3D_H
