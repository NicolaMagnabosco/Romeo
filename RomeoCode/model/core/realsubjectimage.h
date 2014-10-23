#ifndef ROMEO_MODEL_CORE_REALSUBJECTIMAGE_H
#define ROMEO_MODEL_CORE_REALSUBJCTIMAGE_H

#include "model/core/realsubject.h"
#include "model/core/romeoobject.h"

using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::RealSubject;

/*!
 *\file realsubjectimage.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-03-20
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                         Changes                      +       Description         |
*+----------+------------+-----------------+------------------------------------------------------+---------------------------+                                                                                                    |
*|   0.0.1  | 2013-03-20 |   Adami Alberto |          Romeo::Model::Core::RealSubjectImage        |   First version of class  |
*|                                                                                                                            |
*|   1.0.0  | 2013-05-15 |  Adami Albrerto |          Romeo::Model::Core::RealSubjectImage        |Definitive version of class|
*+----------+------------+-----------------+------------------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The RealSubjectImage class represent a RealSubject for a image(2D, 3D).
             * It's a concrete class.
             */
            class RealSubjectImage : public RealSubject
            {
            public:
                /*!
                 * \brief Construct a RealSubject object with the given type, image and mask.
                 * \param type represent the type of the subject (in this case 2D, 3D).
                 * \param image represent the path of the subject's image.
                 * \param mask represent the path of the subject's mask. If the subject has not a mask
                 * the mask object is ana empty string("").
                 */
                RealSubjectImage(const QString &type, const QString &image, const QString& mask="");
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_REALSUBJECT2D_H
