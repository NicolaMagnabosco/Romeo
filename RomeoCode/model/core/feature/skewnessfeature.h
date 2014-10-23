#ifndef ROMEO_MODEL_CORE_FEATURE_SKEWNESSFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_SKEWNESSFEATURE_H

#include "model/core/feature/firstorderfeature.h"
#include "model/core/feature/meanfeature.h"
#include "model/core/feature/standarddeviationfeature.h"

using Romeo::Model::Core::Feature::FirstOrderFeature;

/*!
 *\file skewnessfeature.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-03-14
*/
/*
*Changes:
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +    Programmer     +                       Changes                       +       Description         |
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*|          |            |                   |                                                     |                           |
*|   0.0.1  | 2013-03-14 | Magnabosco Nicola |    Romeo::Model::Core::Feature::SkewnessFeature     |   First version of class  |
*|          |            |                   |                                                     |                           |
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Feature {
                /*!
                 * \brief SkewnessFeature class represent Skewness features extraction alghorithm.
                 * It can be applied to 2D or 3D images.
                 */
                class SkewnessFeature : public FirstOrderFeature
                {
                public:
                    /*!
                     * \brief SkewnessFeature is a default or 1 parameters constructor of the class
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    SkewnessFeature(int idFeat = -1);
                    /*!
                     * \brief SkewnessFeature is the 1 or 2 parameters constructor of the class.
                     * \param parameters is a QString list that conteins feature's parameters.
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    SkewnessFeature(const QStringList& parameters, int idFeat = -1);
                    /*!
                     * \brief singleChannelEXecution2D Execute Skewness feature extractor on 2D images.
                     * \param Input image in InternalData2D format.
                     * \return Output image in InternalData2D format.
                     */
                    virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                    /*!
                     * \brief Execute Skewness feature extractor on 3D images.
                     * \param Input image in InternalData3D format.
                     * \return Output image in InternalData3D format.
                     */
                    virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                    /*!
                     * \brief ~SkewnessFeature virtual destructor of the class.
                     */
                    virtual ~SkewnessFeature();
                };

            } // namespace Feature

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_SKEWNESSFEATURE_H
