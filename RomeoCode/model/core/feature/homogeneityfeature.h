#ifndef ROMEO_MODEL_CORE_FEATURES_HOMOGENEITYFEATURE_H
#define ROMEO_MODEL_CORE_FEATURES_HOMOGENEITYFEATURE_H

#include "model/core/feature/secondorderfeature.h"

using Romeo::Model::Core::Feature::SecondOrderFeature;

/*!
 *\file homogeneity.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-16
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-16 | Scapin Davide   |  Romeo::Model::Core::Feature::HomogeneityFeature    |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {


            /*!
             * \brief HomogeneityFeature class represent Homogeneity features extraction alghorithm.
             * It can be applied to 2D or 3D images.
             */
            class HomogeneityFeature : public SecondOrderFeature
            {
            public:
                /*!
                 * \brief HomogeneityFeature is a default or 1 parameters constructor of the class
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                HomogeneityFeature(int idFeat = -1);
                /*!
                 * \brief HomogeneityFeature is the 1 or 2 parameters constructor of the class.
                 * \param parameters is a QString list that conteins feature's parameters.
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                HomogeneityFeature(const QStringList& parameters, int idFeat = -1);

                /*!
                 * \brief singleChannelEXecution2D Execute Homogeneity feature extractor on 2D images.
                 * \param Input image in InternalData2D format.
                 * \return Output image in InternalData2D format.
                 */
                virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                /*!
                 * \brief Execute Homogeneity feature extractor on 3D images.
                 * \param Input image in InternalData3D format.
                 * \return Output image in InternalData3D format.
                 */
                virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                /*!
                 * \brief ~HomogeneityFeature virtual destructor of the class.
                 */
                virtual ~HomogeneityFeature();
            };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo


#endif // ROMEO_MODEL_CORE_FEATURES_HOMOGENEITYFEATURE_H
