#ifndef ROMEO_MODEL_CORE_FEATURE_MEANFEATURE_H
#define ROMEO_MODEL_CORE_FEATURE_MEANFEATURE_H

#include "model/core/feature/firstorderfeature.h"

using Romeo::Model::Core::Feature::FirstOrderFeature;

/*!
 *\file meanfeature.h
 *\author Magnabosco Nicola (nick.magnabosco@gmail.com)
 *\date 2013-03-14
*/
/*
*Changes:
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +    Programmer     +                       Changes                       +       Description         |
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*|          |            |                   |                                                     |                           |
*|   0.0.1  | 2013-03-14 | Magnabosco Nicola |      Romeo::Model::Core::Feature::MeanFeature       |   First version of class  |
*|          |            |                   |                                                     |                           |
*+----------+------------+-------------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            namespace Feature {
                /*!
                 * \brief MeanFeature class represent Mean features extraction alghorithm.
                 * It can be applied to 2D or 3D images.
                 */
                class MeanFeature : public FirstOrderFeature
                {
                public:
                    /*!
                     * \brief MeanFeature is a default or 1 parameters constructor of the class
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    MeanFeature(int idFeat = -1);
                    /*!
                     * \brief MeanFeature is the 1 or 2 parameters constructor of the class.
                     * \param parameters is a QString list that conteins feature's parameters.
                     * \param idFeat is the id code of the feature;the default value is -1.
                     */
                    MeanFeature(const QStringList& parameters, int idFeat = -1);
                    /*!
                     * \brief singleChannelEXecution2D Execute Mean feature extractor on 2D images.
                     * \param Input image in InternalData2D format.
                     * \return Output image in InternalData2D format.
                     */
                    virtual InternalData2D* singleChannelEXecution2D(InternalData2D *channel);
                    /*!
                     * \brief Execute Mean feature extractor on 3D images.
                     * \param Input image in InternalData3D format.
                     * \return Output image in InternalData3D format.
                     */
                    virtual InternalData3D* singleChannelEXecution3D(InternalData3D *channel);
                    /*!
                     * \brief ~MeanFeature virtual destructor of the class.
                     */
                    virtual ~MeanFeature();
                };

            } // namespace Feature

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_FEATURE_MEANFEATURE_H
