#ifndef ROMEO_MODEL_CORE_RGBIMAGE2D_H
#define ROMEO_MODEL_CORE_RGBIMAGE2D_H

#include "model/core/rgbimage.h"
#include "model/util/readerModel/imagereader.h"
#include "model/core/internaldata2d.h"
#include "itkRGBPixel.h"
#include "itkImageDuplicator.h"
#include "QString"
#include "itkImageRegionIterator.h"
#include "itkMaskImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkRGBToLuminanceImageFilter.h"

using Romeo::Model::Util::ReaderModel::ImageReader;
/*!
 *\file rgbimage2d.h
 *\author Feltre Beatrice (beatrice.feltre@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-20 | Feltre Beatrice |    Romeo::Model::Core::RGBImage2D   |    First version of class     |
*|                                                                                                               |
*|   0.0.2  | 2013-03-01 | Feltre Beatrice |    Romeo::Model::Core::RGBImage2D   |    Complete the class         |
*|                                                                                                               |
*|   0.0.3  | 2013-03-30 | Feltre Beatrice |    Romeo::Model::Core::RGBImage2D   |Definitive version of the class|
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            class RGBImage2D : public RGBImage
            {
            public:
                typedef itk::RGBPixel<unsigned char> RGBPixel;
                typedef itk::Image<RGBPixel,2> RGBImageType;
                typedef itk::Image<float,2> ImageType;
                typedef itk::ImageDuplicator<RGBImageType> DuplicatorType;
                typedef itk::ImageRegionIterator<RGBImageType> RegionIteratorType1;
                typedef itk::MaskImageFilter<RGBImageType,RGBImageType> MaskImageFilterType;
                typedef itk::RGBToLuminanceImageFilter<RGBImageType,ImageType> GrayscaleConverterType;

                /*!
                 * \brief RGBImage2D is the default constructor.
                 */
                RGBImage2D();

                /*!
                 * \brief RGBImage2D constructs an RGB image, calling an ImageReader.
                 * \param fileN is the image's path in the filesystem.
                 */
                RGBImage2D(const QString& fileN, const QString& mask="", bool hasMask=false);

                /*!
                 * \brief RGBImage2D is a deep-copy constructor.
                 */
                RGBImage2D(const RGBImage2D&);
                /*!
                 * \brief RGBImage2D constructs an RGB image from a InternalData2D.
                 */
                RGBImage2D(InternalData2D*);
                /*!
                 * \brief operator = redefines the assignment, making a deep copy of an RGB Image.
                 * \return
                 */
                RGBImage2D& operator=(const RGBImage2D &);

                /*!
                 * \brief getRedImage returns the red-based part of an RGB image.
                 * \return
                 */
                virtual InternalData* getRedImage();

                /*!
                 * \brief getGreenImage returns  the green-based part of an RGB image.
                 * \return
                 */
                virtual InternalData* getGreenImage();

                /*!
                 * \brief getBlueImage returns  the blue-based part of an RGB image.
                 * \return
                 */
                virtual InternalData* getBlueImage();

                /*!
                 * \brief RGBExtracter fills the three color-based images with the respective color value.
                 */
                virtual void RGBExtracter();

                /*!
                 * \brief RGBMerger rebuild the RGB image with values of the three color-based images.
                 */
                virtual void RGBMerger();

                /*!
                 * \brief getXSize
                 * \return the horizontal size of the image.
                 */
                int getXSize() const;

                /*!
                 * \brief getYSize
                 * \return the vertical size of the image.
                 */
                int getYSize() const;

                /*!
                 * \brief ~InternalData2D is a deep-destructor.
                 */

                /*!
                 * \brief getImage
                 * \return it returns a pointer to te image
                 */
                RGBImageType::Pointer getImage();
                /*!
                 * \brief getGreyscaleImage gets a greyscale image froma a RGB image.
                 * \return a greyscale image.
                 */
                ImageType::Pointer getGreyscaleImage();
                /*!
                 * \brief getMaskFileName gets mask filename.
                 * \return mask filename.
                 */
                QString getMaskFileName() const;
                /*!
                 * \brief isMasked returns true if the image has a mask.
                 * \return true if the image has a mask.
                 */
                bool isMasked() const;
                /*!
                 * \brief setImage set a new image.
                 * \param newImage the new image to set.
                 */
                void setImage(RGBImageType::Pointer newImage);

                /*!
                 * \brief maskImage mask the originalImage
                 * \param mask
                 */
                virtual void maskImage(const QString & mask);
                /*!
                 * \brief isRGB return true if the image is RGB.
                 * \return true if the image is RGB.
                 */
                bool isRGB() const;
                /*!
                 * \brief getFileName return fileName.
                 * \return fileName.
                 */
                QString getFileName() const;

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
                 * \brief ~RGBImage2D destroys RGBImage2D object.
                 */
                virtual ~RGBImage2D();
            private:
                /*!
                 * \brief isColored is true if the image is not a greyscale image.
                 */
                bool isColored;
                /*!
                 * \brief fileName is the path of the image.
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
                 * \brief originalImage is the itk image pointer.
                 */
                RGBImageType::Pointer originalImage;
                /*!
                 * \brief redImage is the red channel image.
                 */
                InternalData2D* redImage;
                /*!
                 * \brief greenImage is the green channel image.
                 */
                InternalData2D* greenImage;
                /*!
                 * \brief blueImage is the blue channel image.
                 */
                InternalData2D* blueImage;
                /*!
                 * \brief rgbDuplicator duplicate a rgb image.
                 */
                static DuplicatorType::Pointer rgbDuplicator;
                /*!
                 * \brief reader reader for a RGB image 2D.
                 */
                static ImageReader* reader;
                /*!
                 * \brief copyImage copy a image.
                 * \param img image to copy.
                 * \return a copy of the input image.
                 */
                static RGBImageType::Pointer copyImage(RGBImageType::Pointer img);
            };

            } // namespace Core

        } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_RGBIMAGE2D_H
