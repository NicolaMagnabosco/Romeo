#ifndef ROMEO_MODEL_CORE_INTERNALDATA2D_H
#define ROMEO_MODEL_CORE_INTERNALDATA2D_H

#include "model/core/internaldata.h"
#include "QString"
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkImageRegionIterator.h"
#include "itkNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"
#include "itkImageIterator.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkImageDuplicator.h"
#include "itkScalarImageToCooccurrenceMatrixFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "model/util/readerModel/imagereader.h"
#include <itkCastImageFilter.h>

using Romeo::Model::Core::InternalData;
using Romeo::Model::Util::ReaderModel::ImageReader;

/*!
 *\file internaldata2d.h
 *\author Nicola Magnabosco (nick.magnabosco@gmail.com)
 *\date 2013-03-12
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description         |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|                                                                                                           |
*|   0.0.1  | 2013-03-12 |Nicola Magnabosco|  Romeo::Model::Core::InternalData2D |   First version of class  |
*|                                                                                                           |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            class InternalData2D : public InternalData
            {
            public:
                typedef float PixelType;
                typedef itk::Image<PixelType,2> ImageType;
                typedef itk::RGBPixel<unsigned char> RGBPixelType;
                typedef itk::Image<RGBPixelType,2>RGBImageType;
                typedef itk::ImageDuplicator<ImageType> DuplicatorType;
                typedef itk::ImageIterator<ImageType> ImageIteratorType;
                typedef itk::ImageRegionIterator<ImageType> RegionIteratorInternalType;
                typedef itk::NeighborhoodIterator<ImageType> NeighborhoodIteratorInternalType;
                typedef itk::ImageLinearIteratorWithIndex<ImageType> LinearIteratorIndexType;
                typedef itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<ImageType> ImageToGlcmType;
                typedef ImageType::OffsetType OffsetType;
                typedef ImageToGlcmType::HistogramType HistogramType;
                typedef itk::RegionOfInterestImageFilter<ImageType,ImageType> roiType;
                /*!
                 * \brief InternalData2D is the default constructor.
                 */
                InternalData2D();

                /*!
                 * \brief InternalData2D constructs an empty 2D image with the given X and Y size.
                 * \param xsize
                 * \param ysize
                 */
                InternalData2D(int xsize, int ysize);

                /*!
                 * \brief InternalData2D is a deep-copy constructor.
                 */
                InternalData2D(const InternalData2D& );

                /*!
                 * \brief operator = redefines the assignment to make a deep-copy of an image.
                 * \return
                 */
                InternalData2D& operator=(const InternalData2D&);

                /*!
                 * \brief getXSize.
                 * \return horizontal image size.
                 */
                int getXSize() const;

                /*!
                 * \brief getYSize.
                 * \return vertical image size.
                 */
                int getYSize() const;
                /*!
                 * \brief fillBuffer fills all the image's pixels with a value.
                 * \param value is the value to set.
                 */
                void fillBuffer(int value);
                /*!
                 * \brief getImage is getter method.
                 * \return the a itk pointer to the image.
                 */
                ImageType::Pointer& getImage();
                /*!
                 * \brief setImage set an image to the pointer "image".
                 * \param img is a itk image.
                 */
                void setImage(ImageType::Pointer img);
                /*!
                 * \brief compareImage compares two images.
                 * \param img image to compare.
                 * \return true if the images are equals.
                 */
                bool compareImage(ImageType::Pointer img);
                /*!
                 * \brief convertToRGB converts image to RGBImage.
                 * \return a RGBImage.
                 */
                RGBImageType * convertToRGB() const;
                /*!
                 * \brief ~InternalData2D is a deep-destructor.
                 */
                virtual ~InternalData2D();
            private:
                /*!
                 * \brief image represents the itk image.
                 */
                ImageType::Pointer image;
                /*!
                 * \brief duplicator represents the duplicator image object.
                 */
                static DuplicatorType::Pointer duplicator;
                /*!
                 * \brief copyImage copy an itk image.
                 * \param img image to copy.
                 * \return the copied image.
                 */
                static ImageType::Pointer copyImage(ImageType::Pointer img);
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_INTERNALDATA2D_H
