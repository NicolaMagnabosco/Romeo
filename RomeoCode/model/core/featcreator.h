#ifndef FEATCREATOR_H
#define FEATCREATOR_H

#include "model/core/feature/afeature.h"
#include <QVector>
#include "utils.h"
#include "model/core/feature/meanfeature.h"
#include "model/core/feature/standarddeviationfeature.h"
#include "model/core/feature/skewnessfeature.h"
#include "model/core/feature/kurtosisfeature.h"
#include "model/core/feature/entropyfeature.h"
#include "model/core/feature/energyfeature.h"
#include "model/core/feature/contrastfeature.h"
#include "model/core/feature/homogeneityfeature.h"
#include "model/core/feature/correlationfeature.h"
#include "model/core/feature/maximumfeature.h"
#include "model/core/feature/minimumfeature.h"
#include "model/core/feature/meandynamicfeature.h"
#include "model/core/feature/areaundercurvefeature.h"

using Romeo::Model::Core::Feature::AFeature;

/*!
 *\file featcreator.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-03-15
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                 Changes                    +       Description         |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|                                                                                                                  |
*|   0.0.1  | 2013-03-17 |   Adami Alberto |         Romeo::Model::FeatCreator          |  First version of class   |
*|                                                                                                                  |
*|   0.0.2  | 2013-03-21 |   Adami Alberto |         Romeo::Model::FeatCreator          |Definitive version of class|                                                                               |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The FeatCreator class represent a class used to obtain instance of Features.
             * It's implemented with the Singleton pattern.
             */
            class FeatCreator
            {
            private:
                /*!
                 * \brief featCreator represents the pointer to the unique instance of FeatCreator.
                 */
                static FeatCreator *featCreator;
                /*!
                 * \brief Constructs a FeatCreator object.
                 */
                FeatCreator();
            public:
                /*!
                 * \brief Method that returns the unique instance of FeatCrator class.
                 * If it doesn't exists already, will be create the instance.
                 * \return Return the unique instance of FeatCreator calss.
                 */
                static FeatCreator *getFeatCreator();
                /*!
                 * \brief Create the feature with the given parameters.
                 * \param parameters represents the name of the feature.
                 * \param parameters represents the prameters of the feature.
                 * \param idFeat rerpresents the id of the feature.
                 * \return Return the AFeature's object created.
                 */
                AFeature* buildFeature(const QString &name, QStringList &parameters , int idFeat = -1) const;
                /*!
                 * \brief buildFeature Create the feature with the given parameters.
                 * \param name represents the name of the feature.
                 * \param idFeat represents the id of the feature.
                 * \return Return the AFeature's Object created.
                 */
                AFeature* buildFeature(const QString& name, int idFeat = -1) const;
                /*!
                 * \brief Method that returns all the features of fist oreder.
                 * \return Return a vector contatining all the firstorder features.
                 */
                QVector<AFeature*> getAllFeaturesFirstOrder() const;
                /*!
                 * \brief Method that returns all the features of second order.
                 * \return Return a vector containing all the secondorder features.
                 */
                QVector<AFeature*> getAllFeaturesSecondOrder() const;
                /*!
                 * \brief Method that returns all the dynamic features.
                 * \return Return a vector containing all the dynamic features.
                 */
                QVector<AFeature*> getAllFeaturesDynamic() const;
            };

        } //namespace Core

    } //namespace Model

} //namespace Romeo

#endif // FEATCREATOR_H
