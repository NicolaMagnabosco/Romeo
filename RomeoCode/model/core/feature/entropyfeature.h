#ifndef ROMEO_MODEL_CORE_FEATURE_ENTROPYFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_ENTROPYFEATURE_H

#include "model/core/feature/secondorderfeature.h"

using Romeo::Model::Core::Feature::SecondOrderFeature;

/*!
 *\file entropyfeature.h
 *\author Scapin Davide (davideskap@gmail.com)
 *\date 2013-03-14
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-03-14 | Scapin Davide   |      Romeo::Model::Core::Feature::EntropyFeature    |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/


namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {


            /*!
             * \brief EntropyFeature class represent Entropy features extraction alghorithm.
             * It can be applied to 2D or 3D images.
             */
            class EntropyFeature : public SecondOrderFeature
            {
            public:
                /*!
                 * \brief EntropyFeature is a default or 1 parameters constructor of the class
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                EntropyFeature(int idFeat = -1);
                /*!
                 * \brief EntropyFeature is the 1 or 2 parameters constructor of the class.
                 * \param parameters is a QString list that conteins feature's parameters.
                 * \param idFeat is the id code of the feature;the default value is -1.
                 */
                EntropyFeature(const QStringList& parameters, int idFeat = -1);
                /*!
                 * \brief Execute Entropy feature extractor on 2D images.
                 * \param Input image in InternalData2D format.
                 * \return Output image in InternalData2D format.
                 */
                virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                /*!
                 * \brief Execute Entropy feature extractor on 3D images.
                 * \param Input image in InternalData3D format.
                 * \return Output image in InternalData3D format.
                 */
                virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                /*!
                 * \brief ~EntropyFeature virtual destructor of the class.
                 */
                virtual ~EntropyFeature();
            };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_ENTROPYFEATURE_H
