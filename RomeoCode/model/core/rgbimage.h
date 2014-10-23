#ifndef IMAGE_H
#define IMAGE_H

#include "model/util/readerModel/imagereader.h"
#include "model/core/internaldata.h"
#include "itkRGBPixel.h"
#include "model/core/romeoobject.h"

using Romeo::Model::Core::RomeoObject;
using Romeo::Model::Core::InternalData;
/*!
 *\file rgbimage.h
 *\author Feltre Beatrice (beatrice.feltre@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-20 | Feltre Beatrice |    Romeo::Model::Core::RGBImage     |    First version of class     |
*|                                                                                                               |
*|   0.0.2  | 2013-03-01 | Feltre Beatrice |    Romeo::Model::Core::RGBImage     |    Complete the class         |
*|                                                                                                               |
*|   0.0.3  | 2013-03-30 | Feltre Beatrice |    Romeo::Model::Core::RGBImage     |Definitive version of the class|
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/
namespace Romeo {

    namespace Model{

        namespace  Core {

            class RGBImage : public RomeoObject
            {
            public:
                /*!
                 * \brief It returns the red-based image of an RGB image.
                 * \return It returns a InternalData pointer to the extracted image.
                 */
                virtual InternalData* getRedImage() = 0;

                /*!
                 * \brief It returns the green-based image of an RGB image.
                 * \return It returns a InternalData pointer to the extracted image.
                 */
                virtual InternalData* getGreenImage() = 0;

                /*!
                 * \brief It returns blue-based image of an RGB image.
                 * \return It returns a InternalData pointer to the extracted image.
                 */
                virtual InternalData* getBlueImage() = 0;

                /*!
                 * \brief RGBExtracter extracts three different images from a RGB Image:
                 * the red-based one, the green-based one and the blue-based one.
                 */
                virtual void RGBExtracter() = 0;

                /*!
                 * \brief RGBMerger merges the red/green/blue image into a new RGB Image.
                 */
                virtual void RGBMerger() = 0;

                /*!
                 * \brief maskImage apply a mask to the image
                 * \param mask is the path of mask image
                 */
                virtual void maskImage(const QString &mask) = 0;

            };

        }

    }

}

#endif // IMAGE_H
