#ifndef ROMEO_MODEL_CORE_REGIONITERATOR_H
#define ROMEO_MODEL_CORE_REGIONITERATOR_H

#include "model/core/internaldata.h"
#include "itkImage.h"
#include "itkRGBPixel.h"
#include "itkImageRegionIterator.h"

namespace Romeo {

    namespace Model {

        namespace Core {

            template<class Type, class ImageType>
            class RegionIterator{
            public:
                typedef itk::ImageRegionIterator<Type> RegionIteratorType;
                RegionIterator(ImageType)
                {
                    regionIt(img, img->getRequestedRegion());
                }

                void goToEnd();
                void goToBegin();
                bool isAtEnd();
                void setPixel(float value);
                float getPixelValue();
                RegionIterator& operator++();
                RegionIterator& operator--();
            private:
                RegionIteratorType* regionIt;
            };

        }

    }

}


#endif // ROMEO_MODEL_CORE_REGIONITERATOR_HH
