#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "model/core/romeoobject.h"

using Romeo::Model::Core::RomeoObject;

/*!
 *\file isubject.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description         |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|                                                                                                           |
*|   0.0.1  | 2013-02-20 |   Adami Alberto |  Romeo::Model::Core::ISubject       |   First version of class  |
*|                                                                                                           |
*|   0.0.2  | 2013-02-20 |   Adami Alberto |  Romeo::Model::Core::ISubject       | Complete the docuemntation|                                                                                                     |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
             /*!
             * \brief The ISubject class represent the interface for a generic subject int the Romeo system,
             * The interface contain the methods for get the RomeoObject for the image.
             */
            class ISubject
            {
             public:
                /*!
                 * \brief Method that return the RomeoObject for the image of the subject.
                 * \return Return a RomeoObject's object containing all the information.
                 */
                virtual RomeoObject *getImageFormat()=0;
                /*!
                 * \brief Destruct the ISubject object.
                 */
                virtual ~ISubject();
            };
        }
    }
}
#endif // ISUBJECT_H
