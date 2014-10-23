#ifndef ROMEO_MODEL_CORE_FEATURE_CONTRASTFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_CONTRASTFEATURE_H

#include "model/core/feature/secondorderfeature.h"

using Romeo::Model::Core::Feature::SecondOrderFeature;

/*!
 *\file contrastfeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-14
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-14 | Scapin Davide   |      Romeo::Model::Core::Feature::ContrastFeature   |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {

            /*!
             * \brief ContrastFeature class represent Contrast feature extractor.
             * It can be applied to 2D or 3D images.
             */
            class ContrastFeature : public SecondOrderFeature
            {
            public:
                /*!
                 * \brief ContrastFeature is the default or 1 parameters constructor of the class
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                ContrastFeature(int idFeat = -1);
                /*!
                 * \brief ContrastFeature is the 1 or 2 parameters constructor of the class.
                 * \param parameters is QString list that conteins the feature's parameters.
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                ContrastFeature(const QStringList& parameters, int idFeat = -1);
                /*!
                 * \brief singleChannelEXecution2D performs Contrast feature extractor on 2D images.
                 * \param channel input image in InternalData2D format.
                 * \return Output image in InternalData2D format.
                 */
                virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                /*!
                 * \brief singleChannelEXecution3D performs Contrast feature extractor on 3D images.
                 * \param channel input image in InternalData3D format.
                 * \return Output image in InternalData3D format.
                 */
                virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                /*!
                 * \brief ~ContrastFeature virtual destructor of the class
                 */
                virtual ~ContrastFeature();
            };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_CONTRASTFEATURE_H
