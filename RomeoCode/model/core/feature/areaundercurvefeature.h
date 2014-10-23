#ifndef AREAUNDERCURVEFEATURE_H
#define AREAUNDERCURVEFEATURE_H


#include "model/core/feature/dynamicfeature.h"


using Romeo::Model::Core::Feature::DynamicFeature;


/*!
 *\file areaundercurvefeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-25
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-25 | Scapin Davide   | Romeo::Model::Core::Feature::AreaUnderCurveFeature  |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {
            /*!
             * \brief AreaUnderCurveFeature class represent Area under the curve features extraction alghorithm.
             * It can be applied to 2D-t or 3D-t images.
             */
            class AreaUnderCurveFeature : public DynamicFeature
            {
            public:
                /*!
                 * \brief AreaUnderCurveFeature is a default or 1 parameters constructor of the class
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                AreaUnderCurveFeature(int idFeat = -1);
                /*!
                 * \brief AreaUnderCurveFeature is the 1 or 2 parameters constructor of the class.
                 * \param parameters is a QString list that conteins feature's parameters.
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                AreaUnderCurveFeature(const QStringList& parameters, int idFeat = -1);
                /*!
                 * \brief Execute Area under the curve feature extractor on 2D video.
                 * \param Input Video in Video2D format.
                 * \return Output image in RGBImage2D format.
                 */
                virtual RGBImage2D* execute2DAnalysis(Video2D* video);
                /*!
                 * \brief Execute Area under the curve feature extractor on 3D video.
                 * \param Input Video in Video3D format.
                 * \return Output image in RGBImage3D format.
                 */
                virtual RGBImage3D* execute3DAnalysis(Video3D* video);
                /*!
                 * \brief ~AreaUnderCurveFeature virtual destructor of the class.
                 */
                virtual ~AreaUnderCurveFeature();
            };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo


#endif // AREAUNDERCURVEFEATURE_H
