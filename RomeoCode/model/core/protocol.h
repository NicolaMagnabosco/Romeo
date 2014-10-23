#ifndef ROMEO_MODEL_CORE_PROTOCOL_H
#define ROMEO_MODEL_CORE_PROTOCOL_H

#include "model/core/algorithm/aalgorithm.h"
#include <QVector>
#include "model/core/feature/afeature.h"
#include <QDateTime>

using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::Feature::AFeature;

/*!
 *\file protocol.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-26
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description         |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*|                                                                                                           |
*|   0.0.1  | 2013-02-26 |   Adami Alberto |  Romeo::Model::Core::Protocol       |   First version of class  |
*|                                                                                                           |
*|   0.1.0  | 2013-03-10 |   Adami Alberto |  Romeo::Model::Core::Protocol       |       Fixed some bugs     |
*|                                                                                                           |
*|   1.0.0  | 2013-05-15 |   Adami Alberto |  Romeo::Model::Core::Protocol       |Definitive version of class|                                                                                             |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
            /*!
             * \brief The Protocol class represents a Protocol in the Romeo's system.
             * A protocol has a name, a type, a list of features and an algoritm.
             */
            class Protocol
            {
            private:
                /*!
                 * \brief name represents the name of the Protocol.
                 */
                QString name;
                /*!
                 * \brief type represents the type of the Protocol (2D, 2D-t, 3D, 3D-t).
                 */
                QString type;
                /*!
                 * \brief features represents the features in the Protocol.
                 */
                QVector<AFeature*> features;
                /*!
                 * \brief algorithm represents the pointer to the algorithm of the Protocol.
                 */
                AAlgorithm* algorithm;
                /*!
                 * \brief creationDate represents the creation date of the Protocol.
                 */
                QDateTime creationDate;

            public:
                /*!
                 * \brief Constructs a Protocol object with the given name, type, features, algorithm and date.
                 * \param pName represents the name of the Protocol.
                 * \param pType represent the type of the Protocol (2D, 2D-t, 3D, 3D-t).
                 * \param feats repressents the features of the Protocol.
                 * \param alg represents the algorithm of the Protocol.
                 * \param dateTime represent the creation date of the Protocol.
                 */
                Protocol(const QString& pName, const QString& pType, QVector<AFeature*> feats = QVector<AFeature*>(), AAlgorithm *alg = 0, const QDateTime& dateTime = QDateTime());
                /*!
                 * \brief Constructs a Protocol's object with the given name, type and date.
                 * \param pName represents the name of the Protocol.
                 * \param pType represents the type of the Protocol (2D, 2D-t, 3D, 3D-t).
                 * \param dateTime represents the creation date of the Protocol.
                 */
                Protocol(const QString& pName, const QString& pType, const QDateTime& dateTime);
                /*!
                 * \brief Method that check if the Protocol has an algorithm.
                 * \return Return a bool indicates if the Protocol has an algorithm.
                 * True indicates that the Protocol has an algorithm.
                 * False indicates that the Protocol hasn't an algorithm.
                */
                bool hasAlgorithm() const;
                /*!
                 * \brief Method that return the number of the Features in the Protocol.
                 * \return Return an int containing the number of features in the Protocol.
                 */
                int getNumberOfFeatures() const;
                /*!
                 * \brief Method that return the Algorithm in the Protocol.
                 * If the Protocol has not Algorithm the method return a null pointer.
                 * \return Return an AAlgorithm's object.
                 */
                AAlgorithm* getAlgorithm() const;
                /*!
                 * \brief Method that return the features in the protocol.
                 * \return Return a vector containing the AFeature's objects in the Protocol.
                 */
                QVector<AFeature*> getFeatures() const;
                /*!
                 * \brief Method that return the name of the Protocol.
                 * \return Return a QString's object that contain the name of the Protocol.
                 */
                QString getName() const;
                /*!
                 * \brief Method that add the given feature to the Protocol.
                 * \param newFeature represent the feature to add to the Protocol.
                 */
                void addFeature(AFeature *newFeature);
                /*!
                 * \brief Method that add or change the Algorithm of the Protocol.
                 * \param newAlgorithm represents the new Algorithm of the Protocol.
                 */
                void setAlgorithm(AAlgorithm *newAlgorithm);
                /*!
                 * \brief Method that return the typ of the Protocol (2D, 2D-t, 3D, 3D-t).
                 * \return Return a QString containing the type of the Protocol.
                 */
                QString getType() const;
                /*!
                 * \brief Method that return the creation date of the Protocol.
                 * \return Return a QDateTime's object containig the creation date of the Protocol.
                 */
                QDateTime getCreationDate() const;
                /*!
                 * \brief Destroy the Protocol's object.
                 */
                ~Protocol();
            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_PROTOCOL_H
