#ifndef ROMEO_MODEL_CORE_INTERNALDATA3D_H
#define ROMEO_MODEL_CORE_INTERNALDATA3D_H

#include "model/core/internaldata.h"
#include "model/util/readerModel/imagereader.h"
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkImageRegionIterator.h"
#include "itkNeighborhoodIterator.h"
#include "itkScalarImageToCooccurrenceMatrixFilter.h"
#include "itkRegionOfInterestImageFilter.h"

using Romeo::Model::Core::InternalData;
using Romeo::Model::Util::ReaderModel::ImageReader;

namespace Romeo {

    namespace Model {

        namespace Core {
        /*!
         *\file internaldata3D.h
         *\author Feltre Beatrice (beatrice.feltre@gmail.com)
         *\date 2013-02-10
        */
        /*
        *Changes:
        *+----------+------------+-----------------+-------------------------------------+-------------------------------+
        *|  Version +    Date    +   Programmer    +              Changes                +       Description             |
        *+----------+------------+-----------------+-------------------------------------+-------------------------------+
        *|                                                                                                               |
        *|   0.0.1  | 2013-02-10 | Feltre Beatrice |     Romeo::Model::InternalData3D   |    First version of class      |
        *|                                                                                                               |
        *|   0.0.2  | 2013-02-12 | Feltre Beatrice |     Romeo::Model::InternalData3D   |    Complete the class          |
        *|                                                                                                               |
        *|   0.0.3  | 2013-02-15 | Feltre Beatrice |     Romeo::Model::InternalData3D   | Definitive version of the class|                                                                                                         |                            |                                                                               |
        *+----------+------------+-----------------+-------------------------------------+-------------------------------+
        */
            class InternalData3D : public InternalData
            {
            public:
                typedef float PixelType;
                typedef itk::Image<PixelType,3> ImageType;
                typedef itk::RGBPixel<unsigned char>RGBPixelType;
                typedef itk::Image<RGBPixelType,3>RGBImageType;
                typedef itk::ImageRegionIterator<ImageType> RegionIteratorInternalType;
                typedef itk::NeighborhoodIterator<ImageType> NeighborhoodIteratorInternalType;
                typedef itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<ImageType> ImageToGlcmType;
                typedef ImageType::OffsetType OffsetType;
                typedef ImageToGlcmType::HistogramType HistogramType;
                typedef itk::RegionOfInterestImageFilter<ImageType,ImageType> roiType;
                /*!
                 * \brief InternalData3D is the default constructor.
                 */
                InternalData3D();

                /*!
                 * \brief InternalData3D constructs an empty 3D image with the given X and Y size.
                 * \param xsize width image size.
                 * \param ysize height image size.
                 * \param zsize deep image size.
                 */
                InternalData3D(int xsize, int ysize, int zsize);
                /*!
                 *InternalData3D constructor.
                 */
                InternalData3D(RGBImageType::Pointer );
                /*!
                 * \brief InternalData3D is a deep-copy constructor.
                 */
                InternalData3D(const InternalData3D &);
                /*!
                 * \brief getXSize
                 * \return horizontal image size
                 */
                int getXSize() const;

                /*!
                 * \brief getYSize
                 * \return vertical image size
                 */
                int getYSize() const;

                /*!
                 * \brief getZSize
                 * \return depth size
                 */
                int getZSize() const;

                /*!
                 * \brief getImage is getter method.
                 * \return the a itk pointer to the image
                 */
                ImageType::Pointer getImage();

                /*!
                 * \brief setImage set an image to the pointer "image"
                 * \param img
                 */
                void setImage(ImageType::Pointer img);

                /*!
                 * \brief ~InternalData2D is a deep-destructor.
                 */
                virtual ~InternalData3D();
            private:
                /*!
                 * \brief image itk 3d image.
                 */
                ImageType::Pointer image;
                /*!
                 * \brief copyImage copies the image.
                 * \param img image to copy.
                 * \return the copy image.
                 */
                static ImageType::Pointer copyImage(ImageType::Pointer img);
            };

        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_INTERNALDATA3D_H
