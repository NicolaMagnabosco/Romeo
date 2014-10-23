#ifndef ROMEO_MODEL_CORE_FEATURE_STANDARDDEVIATIONFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_STANDARDDEVIATIONFEATURE_H

#include "model/core/feature/firstorderfeature.h"
#include "model/core/feature/meanfeature.h"

using Romeo::Model::Core::Feature::FirstOrderFeature;
/*!
 *\file standarddeviationfeature.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-03-14
*/
/*
*Changes:
*+----------+------------+-------------------+-------------------------------------------------------+---------------------------+
*|  Version +    Date    +    Programmer     +                       Changes                         +       Description         |
*+----------+------------+-------------------+-------------------------------------------------------+---------------------------+
*|          |            |                   |                                                       |                           |
*|   0.0.1  | 2013-03-14 | Magnabosco Nicola | Romeo::Model::Core::Feature::StandardDeviationFeature |   First version of class  |
*|          |            |                   |                                                       |                           |
*+----------+------------+-------------------+-------------------------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace Model {
        namespace Core {
            namespace Feature {
                /*!
                 * \brief StandardDeviationFeature class represent StandardDeviation features extraction alghorithm.
                 * It can be applied to 2D or 3D images.
                 */
                class StandardDeviationFeature : public FirstOrderFeature
                {
                public:
                    /*!
                     * \brief StandardDeviationFeature is a default or 1 parameters constructor of the class
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    StandardDeviationFeature(int idFeat = -1);
                    /*!
                     * \brief StandardDeviationFeature is the 1 or 2 parameters constructor of the class.
                     * \param parameters is a QString list that conteins feature's parameters.
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    StandardDeviationFeature (const QStringList& parameters, int idFeat = -1);
                    /*!
                     * \brief singleChannelEXecution2D Execute StandardDeviation feature extractor on 2D images.
                     * \param Input image in InternalData2D format.
                     * \return Output image in InternalData2D format.
                     */
                    virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                    /*!
                     * \brief Execute StandardDeviation feature extractor on 3D images.
                     * \param Input image in InternalData3D format.
                     * \return Output image in InternalData3D format.
                     */
                    virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                    /*!
                     * \brief ~StandardDeviationFeature virtual destructor of the class.
                     */
                    virtual ~StandardDeviationFeature();
                };

            } // namespace Feature
        } // namespace Core
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_STANDARDDEVIATIONFEATURE_H
