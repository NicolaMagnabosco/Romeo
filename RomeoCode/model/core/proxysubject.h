#ifndef ROMEO_MODEL_CORE_PROXYSUBJECT_H
#define ROMEO_MODEL_CORE_PROXYSUBJECT_H

#include "model/core/asubject.h"
#include "model/core/realsubject.h"
#include <QString>
#include <QDateTime>

using Romeo::Model::Core::RealSubject;
using Romeo::Model::Core::ASubject;

/*!
 *\file proxysubject.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-03-10
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                         Changes                      +       Description         |
*+----------+------------+-----------------+------------------------------------------------------+---------------------------+                                                                                                    |
*|   0.0.1  | 2013-03-10 |   Adami Alberto |              Romeo::Model::Core::ASubjct             |   First version of class  |
*|                                                                                                                            |
*|   0.1.0  | 2013-04-13 |   Adami Alberto |      Romeo::Model::Core::ASubject::getRealSubject()  | Fixed segmentation fault  |
*|                                                                                                                            |
*|   1.0.0  | 2013-04-15 |  Adami Albrerto |              Romeo::Model::Core::ASubject            |Definitive version of class|
*+----------+------------+-----------------+------------------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            /*!
             * \brief The ProxySubject class represent a proxy for a RealSubject
             * object.
             * This class is implemented with the proxy pattern.
             */
            class ProxySubject: public ASubject
            {
            private:
                /*!
                 * \brief realSubject represent a pointer to a RealSubject object.
                 */
                RealSubject *realSubject;
            protected:
                /*!
                 * \brief Method that return an instance of RealSubject. If it doesn't exists, getRealSubject() created it.
                 * \return Return a RealSubject's object that represent the RealSubject.
                 */
                RealSubject *getRealSubject();
            public:
                /*!
                 * \brief Constructs a RealSubject with the given parameters.
                 * \param subjectName reprsent the name of the subject.
                 * \param subjectImage represent the path of the subject.
                 * \param type represent the type of the subject (2D, 2D-t, 3D, 3D-t)
                 * \param subjectMask represent the mask of the subject.
                 */
                ProxySubject(const QString& subjectName, const QString& subjectImage, const QString& type, const QString& subjectMask="", const QDateTime& dateTime = QDateTime());
                /*!
                 * \brief Method that return the RomeoObject's object for the image of the subject.
                 * \return Return a RomeoObject's object containing all the information.
                 */
                RomeoObject *getImageFormat();
                /*!
                 * \brief Destructs the ProxySubject.
                 */
                virtual ~ProxySubject();
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_PROXYSUBJECT_H
