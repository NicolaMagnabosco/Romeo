#ifndef ROMEO_MODEL_CORE_INTERNALDATA_H
#define ROMEO_MODEL_CORE_INTERNALDATA_H

#include "QString"
#include "itkImage.h"
#include "itkImageRegionIterator.h"
#include "itkNeighborhoodIterator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "QVector"

/*!
 *\file internaldata.h
 *\author Feltre Beatrice (beatrice.feltre@gmail.com)
 *\date 2013-02-10
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-10 | Feltre Beatrice |      Romeo::Model::InternalData     |   First version of class      |
*|                                                                                                               |
*|   0.0.2  | 2013-02-12 | Feltre Beatrice |      Romeo::Model::InternalData     |   Complete the class          |
*|                                                                                                               |
*|   0.0.3  | 2013-02-15 | Feltre Beatrice |      Romeo::Model::InternalData     |Definitive version of the class|                                                                                                         |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The InternalData class represent a Image in Romeo.
             */
            class InternalData
            {   
            public:
                /*!
                 * \brief InternalData default builder.
                 */
                InternalData();
                /*!
                 * \brief getXSize gets the width size of the image.
                 * \return the width size of the image.
                 */
                virtual int getXSize() const = 0;
                /*!
                 * \brief getYSize gets the height of the image.
                 * \return the height size of the image.
                 */
                virtual int getYSize() const = 0;
                /*!
                 * \brief ~InternalData destroys the InternalData object.
                 */
                virtual ~InternalData();
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_INTERNALDATA_H
