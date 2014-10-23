#ifndef ROMEO_MODEL_CORE_FEATURE_MEANDYNAMICFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_MEANDYNAMICFEATURE_H

#include "model/core/feature/dynamicfeature.h"


using Romeo::Model::Core::Feature::DynamicFeature;


/*!
 *\file meandynamicfeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-25
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-04-01 | Scapin Davide   |   Romeo::Model::Core::Feature::MeanDynamicFeature   |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {
            /*!
             * \brief MeanDynamicFeature class represent mean dynamic features extraction alghorithm.
             * It can be applied to 2D-t or 3D-t images.
             */
            class MeanDynamicFeature : public DynamicFeature
            {
            public:
                /*!
                 * \brief MeanDynamicFeature is a default or 1 parameters constructor of the class
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                MeanDynamicFeature(int idFeat = -1);
                /*!
                 * \brief MeanDynamicFeature is the 1 or 2 parameters constructor of the class.
                 * \param parameters is a QString list that conteins feature's parameters.
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                MeanDynamicFeature(const QStringList& parameters, int idFeat = -1);
                /*!
                 * \brief Execute Mean feature extractor on 2D video.
                 * \param Input Video in Video2D format.
                 * \return Output image in RGBImage2D format.
                 */
                virtual RGBImage2D* execute2DAnalysis(Video2D* video);
                /*!
                 * \brief Execute Mean Dynamic feature extractor on 3D video.
                 * \param Input Video in Video3D format.
                 * \return Output image in RGBImage3D format.
                 */
                virtual RGBImage3D* execute3DAnalysis(Video3D* video);
                /*!
                 * \brief ~MeanDynamicFeature virtual destructor of the class.
                 */
                virtual ~MeanDynamicFeature();
            };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_MEANDYNAMICFEATURE_H
