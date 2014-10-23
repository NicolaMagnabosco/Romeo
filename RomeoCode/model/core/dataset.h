#ifndef ROMEO_MODEL_CORE_DATASET_H
#define ROMEO_MODEL_CORE_DATASET_H

#include <QVector>
#include <QString>
#include "model/core/groupofsubject.h"
#include "model/core/protocol.h"
#include <QDateTime>

using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Core::Protocol;

/*!
 *\file dataset.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-15
*/
/*
*Changes:
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                 Changes                    +       Description         |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|                                                                                                                  |
*|   0.0.1  | 2013-02-15 |   Adami Alberto |         Romeo::Model::Dataset              |   First version of class  |
*|                                                                                                                  |
*|   0.0.2  | 2013-02-26 |   Adami Alberto | Romeo::Model::Dataset::getNumberOfProtocols|   Add the method.         |                                                                               |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {
             /*!
             * \brief The Dataset class represent a dataset object in the Romeo system.
             */
            class Dataset
            {
            private:
                /*!
                 * \brief name represents the name of the dataset.
                 */
                QString name;
                /*!
                 * \brief group represents the group of subject associated with the dataset.
                 */
                GroupOfSubject *group;
                /*!
                 * \brief protocols represents the protocols associated with the dataset.
                 */
                QVector<Protocol*> protocols;
                /*!
                 * \brief creationDate represents the creation date of the dataset.
                 */
                QDateTime creationDate;

            public:
                /*!
                 * \brief Create a Dataset's object with the given name, group, protocols, and creation date.
                 * \param datasetName represents the name of the Dataset.
                 * \param groupOfSubject represents the group of subject associated with the dataset.
                 * \param vProtocols represents the protocols associated with the dataset.
                 * \param dateTime represents the creation date of the dataset.
                 */
                Dataset(const QString& datasetName, GroupOfSubject *groupOfSubject, QVector<Protocol*> vProtocols, const QDateTime& dateTime = QDateTime());
                /*!
                 * \brief Method that returns the name of the dataset.
                 * \return Return a QString containing the name of the dataset.
                 */
                QString getName() const;
                /*!
                 * \brief Method that returns the group of subject associated with the dataset.
                 * \return Return a GroupOfSubject object that reprsent the group of subject object
                 * associated with the dataset.
                 */
                GroupOfSubject *getGroup() const;
                /*!
                 * \brief Method that returns the protocols associated with the dataset.
                 * \return Return a vector of protocols object that represents the protocols associated with the dataset.
                 */
                QVector<Protocol*> getProtocols() const;
                /*!
                 * \brief Method that returns the creation date of the dataset.
                 * \return Return a QDateTime object that represents the creation date of the dataset.
                 */
                QDateTime getCreationDate() const;
                /*!
                 * \brief Method that return the number of protocols in the dataset.
                 * \return Return an int that represents the number of the protocols in the dataset.
                 */
                int getNumberOfProtocols() const;
                /*!
                 * \brief Method that return the number of the features associated with the protocols in the dataset.
                 *Adami Alberto \return Return an int that represents the number of features associated with the dataset.
                 */
                int getNumberOfFeaturesAssociated() const;
                /*!
                 * \brief Method that return the number of the algorithms associated with the protocols in the dataset.
                 * \return Return an int that represents the number of algorithms associated with the dataset.
                 */
                int getNumberOfAlgAssociated() const;
                /*!
                 *\breief Desctructs the Dataset object.
                 */
                ~Dataset();

            };

        } // namespace Core

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_CORE_DATASET_H
