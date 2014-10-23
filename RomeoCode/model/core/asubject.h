#ifndef ROMEO_MODEL_CORE_ASUBJECT_H
#define ROMEO_MODEL_CORE_ASUBJECT_H

#include <QString>
#include "model/core/isubject.h"
#include "model/core/romeoobject.h"
#include <QDateTime>
#include "utils.h"

/*!
 *\file asubject.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-25
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description         |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|                                                                                                           |
*|   0.0.1  | 2013-02-25 |   Adami Alberto |  Romeo::Model::Core::ASubjct        |   First version of class  |
*|                                                                                                           |
*|   0.1.0  | 2013-03-10 |   Adami Alberto |  Romeo::Model::Core::ASubject       | Add some methods          |
*|                                                                                                           |
*|   1.0.0  | 2013-03-10 |  Adami Albrerto |  Romeo::Model::Core::ASubject       |Definitive version of class|
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*/

using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::ISubject;

namespace Romeo {

    namespace Model {

        namespace Core {

            /*!
             * \brief The ASubject class represent a generic subject in the system.
             * For exetend this class the programmer have to implement the getImageFormat method.
             */
            class ASubject : public ISubject
            {
            private:
                /*!
                 * \brief name represents the name of the subject.
                 */
                QString name;
                /*!
                 * \brief image represents the image of the subject.
                 */
                QString image;
                /*!
                 * \brief type represents the type of the subject. (2D, 2D-t, 3D, 3D-t)
                 */
                QString type;
                /*!
                 * \brief mask represents the mask of the subject.
                 */
                QString mask;
                /*!
                 * \brief creationDate reprsennts the date on which the subject has been created.
                 */

                QDateTime creationDate;
            public:
                /*!
                 * \brief Constructs an ASubject's object with the given name, image, type, mask and date.
                 * \param stringName represents the name of the subject.
                 * \param stringImage represents the image path.
                 * \param stringType represents the subject type (2D, 2D-t, 3D, 3D-t).
                 * \param stringMask represents the maks path
                 * \param dateTime the date on which the subject has been created for the first time.
                 */
                ASubject(const QString& stringName, const QString& stringImage, const QString& stringType, const QString& stringMask="", const QDateTime& dateTime = QDateTime());
                /*!
                 * \brief Return the name of the subject.
                 * \return  Return a QString object containing the name of the subject.
                 */
                QString getName() const;
                /*!
                 * \brief Return the image's path of the subject.
                 * \return Return a QString object containing the image's path of the subject.
                 */
                QString getImage() const;
                /*!
                 * \brief return the mask's path of the subject.
                 * \return  Return a QString object containing the mask's path of the subject.
                 */
                QString getMask() const;
                /*!
                 * \brief return the creation date of the subject.
                 * \return Return a QDateTime object contaaining the creation date of the subject.
                 */

                QDateTime getCreationDate() const;
                /*!
                 * \brief Method that returns if the subject has a maks or not.
                 * \return Return a bool that inidicates if the subject has the mask or not.
                 * True indicates that the subject has a mask.
                 * False indicates that the subject has not a mask.
                 */

                bool hasMask() const;
                /*!
                 * \brief return the type of the subject. (2D, 2D-t, 3D, 3D-t)
                 * \return a Qstring object containing the type of the subject.4
                 */
                QString getType() const;
                /*!
                 * \brief Return the RomeoObject for the image of the subject.
                 * \return Return a RomoObject containing all the information.
                 */
                virtual RomeoObject *getImageFormat()=0;
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ASUBJECT_H
