#ifndef ROMEO_MODEL_CORE_RGBIMAGE3D_H
#define ROMEO_MODEL_CORE_RGBIMAGE3D_H

#include "model/core/rgbimage.h"
#include "model/util/readerModel/imagereader.h"
#include "model/core/internaldata3d.h"
#include "QString"
#include "itkRGBPixel.h"
#include "itkImageRegionIterator.h"
#include "itkMaskImageFilter.h"
#include "itkRGBToLuminanceImageFilter.h"

/*!
 *\file rgbimage3D.h
 *\author Feltre Beatrice (beatrice.feltre@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-20 | Feltre Beatrice |    Romeo::Model::Core::RGBImage3D   |    First version of class     |
*|                                                                                                               |
*|   0.0.2  | 2013-03-01 | Feltre Beatrice |    Romeo::Model::Core::RGBImage3D   |    Complete the class         |
*|                                                                                                               |
*|   0.0.3  | 2013-03-30 | Feltre Beatrice |    Romeo::Model::Core::RGBImage3D   |Definitive version of the class|
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

using Romeo::Model::Util::ReaderModel::ImageReader;

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The RGBImage3D class represents a RGBImage 3D in Romeo.
             */
            class RGBImage3D : public RGBImage
            {
            public:

                typedef itk::RGBPixel<unsigned char> RGBPixel;
                typedef itk::Image<RGBPixel,3> RGBImageType;
                typedef itk::Image<float,3> ImageType;
                typedef itk::ImageRegionIterator<RGBImageType> RegionIteratorType;
                typedef itk::RGBToLuminanceImageFilter<RGBImageType,ImageType> GrayscaleConverterType;

                /*!
                 * \brief RGBImage3D is the default constructor.
                 */
                RGBImage3D();

                /*!
                 * \brief RGBImage3D constructs an RGB image, calling an ImageReader.
                 * \param fileN is the image's path in the filesystem.
                 */
                RGBImage3D(const QString& fileN, const QString &fileMask, bool hasMask);
                /*!
                 * \brief RGBImage3D constructs a RGBImage3D from a InternalData3D.
                 */
                RGBImage3D(InternalData3D*);
                /*!
                 * \brief RGBImage3D is a deep-copy constructor.
                 */
                RGBImage3D(const RGBImage3D&);
                /*!
                 * \brief getRedImage returns the red-based part of an RGB image.
                 * \return
                 */
                /*!
                 * \brief getGreyScaleImage converts a RGBImage 3d in a greyscale image 3d.
                 * \return
                 */
                InternalData3D* getGreyScaleImage();

                /*!
                 * \brief getRedImage gets the red RGB image channel.
                 * \return red channel.
                 */
                virtual InternalData* getRedImage() ;

                /*!
                 * \brief getGreenImage returns  the green-based part of an RGB image.
                 * \return green channel.
                 */
                virtual InternalData* getGreenImage() ;

                /*!
                 * \brief getBlueImage returns  the blue-based part of an RGB image.
                 * \return blue channel.
                 */
                virtual InternalData* getBlueImage() ;

                /*!
                 * \brief RGBExtracter fills the three color-based images with the respective color value.
                 */
                virtual void RGBExtracter();

                /*!
                 * \brief RGBMerger rebuild the RGB image with values of the three color-based images.
                 */
                virtual void RGBMerger();

                /*!
                 * \brief getXSize gets the size width of the image
                 * \return the horizontal size of the image.
                 */
                int getXSize() const;

                /*!
                 * \brief getYSize gets the size height of the image.
                 * \return the horizontal size of the image.
                 */
                int getYSize() const;

                /*!
                 * \brief getZSize gets the size deep of the image
                 * \return the horizontal size of the image.
                 */
                int getZSize() const;
                /*!
                 * \brief getImage gets itk original image.
                 * \return itk original image.
                 */
                RGBImageType::Pointer getImage();
                /*!
                 * \brief setImage sets rgb original image.
                 * \param image itk image to set.
                 */
                void setImage(ImageType::Pointer image);
                /*!
                 * \brief setImage sets a rgb original image.
                 * \param image itk image to set.
                 */
                void setImage(RGBImageType::Pointer image);
                /*!
                 * \brief maskImage sets a mask image.
                 * \param mask is the mask image to set.
                 */
                virtual void maskImage(const QString& mask);

                /*!
                 * \brief getFileName return fileName.
                 * \return fileName.
                 */
                QString getFileName() const;
                /*!
                 * \brief getMaskFileName return maskFileName.
                 * \return maskFileName.
                 */
                QString getMaskFileName() const;
                /*!
                 * \brief getimageHasMask return true if image has a mask.
                 * \return return true if image has a mask.
                 */
                bool isMasked() const;
                /*!
                 * \brief setFileName set fileName with a new value.
                 * \param newFileName is the new value of fileName.
                 */
                void setFileName(QString newFileName);
                /*!
                 * \brief setMaskFileName set maskFileName with a new value.
                 * \param newMaskFileName is the new value of maskFileName.
                 */
                void setMaskFileName(QString newMaskFileName);
                /*!
                 * \brief setImageHasMask set imageHasMask with a new value.
                 * \param newImageHasMask is the new value of imageHasMask.
                 */
                void setImageHasMask(bool newImageHasMask);
                /*!
                 * \brief ~RGBImage3D destroys the object.
                 */
                virtual ~RGBImage3D();

            private:
                /*!
                 * \brief fileName is the image path.
                 */
                QString fileName;
                /*!
                 * \brief maskFileName is the mask path.
                 */
                QString maskFileName;
                /*!
                 * \brief imageHasMask is true if the image has a mask.
                 */
                bool imageHasMask;
                /*!
                 * \brief originalImage is the original itk image.
                 */
                RGBImageType::Pointer originalImage;
                /*!
                 * \brief redImage is the red channel image.
                 */
                InternalData3D* redImage;
                /*!
                 * \brief greenImage is the green channel image.
                 */
                InternalData3D* greenImage;
                /*!
                 * \brief blueImage is the blue channel image.
                 */
                InternalData3D* blueImage;
                /*!
                 * \brief reader is the reader for 3d images.
                 */
                static ImageReader* reader;
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_RGBIMAGE3D_H
