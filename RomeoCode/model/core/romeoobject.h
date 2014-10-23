#ifndef ROMEO_MODEL_CORE_ROMEOOBJECT_H
#define ROMEO_MODEL_CORE_ROMEOOBJECT_H

#include <QString>

/*!
 *\file romeoobject.h
 *\author Feltre Beatrice (beatrice.feltre@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-20 | Feltre Beatrice |   Romeo::Model::Core::RomeoObject   |    First version of class     |
*|                                                                                                               |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Core {
        /*!
         * \brief The RomeoObject class represents the base class for all the Romeo images and videos.
         */
        class RomeoObject
        {
        public:
            /*!
             * \brief getXSize returns width size of the data.
             * \return the wide size of data.
             */
            virtual int getXSize() const = 0;
            /*!
             * \brief getYSize gets height size of the data.
             * \return height size of data.
             */
            virtual int getYSize() const = 0;
            /*!
             * \brief maskImage sets a mask image for the data.
             * \param mask is the mask to set.
             */
            virtual void maskImage(const QString &mask) = 0;
            /*!
             * \brief ~RomeoObject delete RomeoObject.
             */
            virtual ~RomeoObject();
        };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_ROMEOOBJECT_H
