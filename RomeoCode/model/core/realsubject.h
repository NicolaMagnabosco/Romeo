#ifndef ROMEO_MODEL_CORE_REALSUBJECT_H
#define ROMEO_MODEL_CORE_REALSUBJECT_H

#include "model/core/isubject.h"
#include "model/core/romeoobject.h"
#include <QString>

using Romeo::Model::Core::ISubject;
using Romeo::Model::Core::RomeoObject;

/*!
 *\file proxysubject.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-03-15
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------+-----------------------------+
*|  Version +    Date    +   Programmer    +                         Changes                      +       Description           |
*+----------+------------+-----------------+------------------------------------------------------+-----------------------------+                                                                                                    |
*|   0.0.1  | 2013-03-15 |   Adami Alberto |              Romeo::Model::Core::RealSubject         |   First version of class    |
*|                                                                                                                              |
*|   0.1.0  | 2013-04-13 |   Adami Alberto |   Romeo::Model::Core::RealSubject::getImageFormat()  | Mark the method as concrete |
*|                                                                                                                              |
*|   1.0.0  | 2013-04-15 |  Adami Albrerto |              Romeo::Model::Core::RealSubject         | Definitive version of class |
*+----------+------------+-----------------+------------------------------------------------------+-----------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The RealSubject class represent a Real Subject in the Romeo system.
             * This is an abstract class.
             */
            class RealSubject: public ISubject
            {
            protected:
                /*!
                 * \brief imageFormat represents the rappresentation of the Subject's image.
                 */
                RomeoObject *imageFormat;
                /*!
                 * \brief Construct a RealSubject object.
                 */
                RealSubject();
            public:
                /*!
                 * \brief Method that return the image rappresentation of the subject.
                 * \return Return a RomeoObject that represent the image in the Romeo's System.
                 */
                virtual RomeoObject *getImageFormat();
                /*!
                 * \brief Destroy the RealSubject's object.
                 */
                virtual ~RealSubject();
            };

        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_REALSUBJECT_H
