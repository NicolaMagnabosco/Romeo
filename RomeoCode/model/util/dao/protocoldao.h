#ifndef ROMEO_MODEL_UTIL_DAO_PROTOCOLDAO_H
#define ROMEO_MODEL_UTIL_DAO_PROTOCOLDAO_H

#include <QVector>
#include "model/core/protocol.h"
#include "model/util/dao/adatabase.h"
#include "model/util/dao/featuredao.h"
#include "model/util/dao/algorithmdao.h"
#include "model/core/dataset.h"
#include "model/util/dao/datasetdao.h"

using Romeo::Model::Core::Protocol;
using Romeo::Model::Util::DAO::ADatabase;

/*!
 *\file protocoldao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-24
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-24 |   Luisetto Luca |   Romeo::Model::Util::Dao::ProtocolDAO                     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {
    namespace Model {
        namespace Util {
            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the protocol table of the database.
                 */
                class ProtocolDAO : public ADatabase
                {
                public:
                    /*!
                    * \brief when ProtocolDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                    */
                    ProtocolDAO();
                    /*!
                    * \brief The method check if the name of protocol already exists.
                    * \param name is the name to check.
                    * \return Return a boolean true if the name already exist, false if not exist.
                    */
                    bool existProtocolWithName(const QString& name) ;
                    /*!
                    * \brief The method get all saved protocols.
                    * \return Return a vector of protocols pointer.
                    */
                    QVector<Protocol*> getAllProtocol();
                    /*!
                    * \brief The method get all the protocol based on type.
                    * \param type is the type of the protocol.
                    * \return Return a vector of protocols pointer.
                    */
                    QVector<Protocol*> getProtocolsOfType(const QString& type);
                    /*!
                    * \brief The method get the protocol with the name passed.
                    * \param name is the name to check.
                    * \return Return a protocol pointer.
                    */
                    Protocol* getProtocolByName(const QString& name);
                    /*!
                    * \brief The method create on the database the protocol.
                    * \param protocol is the protocol to save.
                    * \return Return a boolean true if protocol creation successful, false if fails.
                    */
                    bool createProtocol(const Protocol& protocol);
                    /*!
                    * \brief The method update the protocol.
                    * \param newProtocol is the protocol with the new informations.
                    * \param oldProtocol is the old protocol to update.
                    * \param featuresToRemove is the vector with the features to remove in the protocol.
                    * \return Return a boolean true if protocol update successful, false if fails.
                    */
                    bool updateProtocol(const Protocol& newProtocol, const Protocol& oldProtocol, QVector<int> featuresToRemove);
                    /*!
                    * \brief The method delete the protocol.
                    * \param protocol is the protocol to delete.
                    * \return Return a boolean true if protocol delete successful, false if fails.
                    */
                    bool deleteProtocol(const Protocol& protocol);
                    /*!
                    * \brief The method delete the protocol with name.
                    * \param name is the name of protocol to delete.
                    * \return Return a boolean true if protocol delete successful, false if fails.
                    */
                    bool deleteProtocol(const QString& name);
                    /*!
                    * \brief The method get all protocols name.
                    * \return Return a vector with the names of protocols.
                    */
                    QVector<QString> getAllProtocolName();
                    /*!
                    * \brief The method get all protocols in the dataset.
                    * \param dataset is the name of the dataset.
                    * \return Return a vector with all protocols of the dataset.
                    */
                    QVector<Protocol*> getAllProtocolOfDataset(const QString& datasetName);
                    /*!
                    * \brief The method get the dataset of the protocol.
                    * \param protocol is the protocol to search.
                    * \return Return a vector with the dataset name.
                    */
                    QVector<QString> getDatasetOfProtocol(const QString &protocol);
                };

            } // namespace DAO
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_PROTOCOLDAO_H
