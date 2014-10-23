#ifndef ROMEO_MODEL_UTIL_DAO_FEATUREDAO_H
#define ROMEO_MODEL_UTIL_DAO_FEATUREDAO_H

#include "model/util/dao/adatabase.h"
#include "model/core/feature/afeature.h"
#include "model/core/protocol.h"
#include "model/core/featcreator.h"

using Romeo::Model::Util::DAO::ADatabase;
using Romeo::Model::Core::Feature::AFeature;
using Romeo::Model::Core::Protocol;
/*!
 *\file featuredao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-23
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-23 |   Luisetto Luca |    Romeo::Model::Util::Dao::FeatureDAO                     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {
    namespace Model {
        namespace Util {
            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the feature table of the database.
                 */
                class FeatureDAO : public ADatabase
                {
                public:
                    /*!
                     * \brief when FeatureDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                     */
                    FeatureDAO();
                    /*!
                     * \brief The method test if the feature already exists.
                     * \param id is the id of the feature to test.
                     * \return Return true if feature already exist, false if not exist.
                     */
                    bool existFeature(const int id) const;
                    /*!
                     * \brief The method create a new feature in the database.
                     * \param feature is the feature to insert in the database
                     * \param protocol is the protocol associated.
                     * \return Return true if creation successful, false if fails.
                     */
                    bool createFeature(const AFeature& feature, const Protocol& protocol);
                    /*!
                     * \brief The method update a feature in the database.
                     * \param feature is the feature to update in the database
                     * \param protocol is the protocol associated.
                     * \return Return true if update successful, false if fails.
                     */
                    bool updateFeature(const AFeature& feature, const Protocol& protocol);
                    /*!
                     * \brief The method remove the features associated to the protocol from the database.
                     * \param protocol is the protocol associated.
                     * \return Return true if delete successful, false if fails.
                     */
                    bool removeFeature(const QString& protocol);
                    /*!
                     * \brief The method remove the feature with the specified id.
                     * \param id is the unique id of the feature.
                     * \return Return true if delete successful, false if fails.
                     */
                    bool removeFeature(const int id);
                    /*!
                     * \brief The method get the feature with name and associated to the protocol.
                     * \param featureName is the name of the feature.
                     * \param protocol is the protocol associated.
                     * \return Return a feature pointer.
                     */
                    AFeature* getFeatureOfProtocol(QString& featureName, Protocol* protocol);
                    /*!
                     * \brief get all Feature that are members of Protocol
                     * \param protocol which the feature are part
                     * \return QVector<AFeature*> contains the pointer to the Feature
                     */
                    QVector<AFeature*> getAllFeatureOfProtocol(Protocol* protocol);
                    /*!
                     * \brief get all Feature that are members of Protocol
                     * \param protocolName is the name of protocol which the feature are part
                     * \return QVector<AFeature*> contains the pointer to the Features
                     */
                    QVector<AFeature*> getAllFeatureOfProtocol(const QString& protocolName);
                };

            } // namespace DAO
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_FEATUREDAO_H
