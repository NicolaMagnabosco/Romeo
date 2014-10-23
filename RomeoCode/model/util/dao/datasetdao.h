#ifndef ROMEO_MODEL_UTIL_DAO_DATASETDAO_H
#define ROMEO_MODEL_UTIL_DAO_DATASETDAO_H

#include <QVector>
#include <QString>
#include "model/util/dao/adatabase.h"
#include "model/core/dataset.h"
#include "model/core/protocol.h"
#include "model/core/groupofsubject.h"
#include "model/util/dao/groupdao.h"
#include "model/util/dao/subjectdao.h"
#include "model/util/dao/protocoldao.h"
#include "utils.h"
#include "model/core/asubject.h"

using Romeo::Model::Util::DAO::ADatabase;
using Romeo::Model::Core::Dataset;
using Romeo::Model::Core::Protocol;
using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Util::DAO::GroupDAO;
using Romeo::Model::Core::ASubject;
/*!
 *\file datasetdao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-23
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-23 |   Luisetto Luca |  Romeo::Model::Util::Dao::DatasetDAO                     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {
    namespace Model {
        namespace Util {
            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the dataset table of the database.
                 */
                class DatasetDAO : public ADatabase
                {
                public:
                    /*!
                    * \brief return if exists in database a subject with the given name
                    * \param name, need to find a subject
                    * \return true if the subject contained in database, false otherwise
                    */
                    bool existDatasetWithName(const QString& name);
                    /*!
                     * \brief get all Dataset contained in database
                     * \return a QVector of pointers to Dataset object
                     */
                    QVector<Dataset*> getAllDataset();
                    /*!
                     * \brief get all name of Dataset contained in database
                     * \return QVector of QString that contains the Dataset name
                     */
                    QVector<QString> getAllDatasetName();
                    /*!
                     * \brief get a Group of Subject that is memeber of given Dataset
                     * \param Dataset which the Group is member
                     * \return a pointer to the Group of Subject member of the given Dataset
                     */
                    GroupOfSubject* getGroupOfDataset( const Dataset& dataset);
                    /*!
                     * \brief get a Group of Subjects that is memeber of given Dataset
                     * \param Dataset name which the Group is member
                     * \return a pointer to the Group of Subject member of the given Dataset
                     */
                    GroupOfSubject* getGroupOfDataset( const QString& dataset);
                    /*!
                     * \brief get the protocols of the dataset.
                     * \param dataset is the dataset to search.
                     * \return Return a vector with protocols pointer.
                     */
                    QVector<Protocol*> getProtocolsOfDataset( const Dataset& dataset);
                    /*!
                     * \brief get the protocols of the dataset.
                     * \param dataset name is the dataset to search.
                     * \return Return a vector with protocols pointer.
                     */
                    QVector<Protocol*> getProtocolsOfDataset( const QString& dataset);
                    /*!
                     * \brief The method create the dataset with the parameters.
                     * \param name is the name of the dataset.
                     * \param group is the name of the group of subject.
                     * \param protocolVector is a vector with protocols name.
                     * \return Return true if creation successful, false if fails.
                     */
                    bool createDataset(const QString& name, const QString& group, const QVector<QString>& protocolVector);
                    /*!
                     * \brief The method delete the dataset.
                     * \param dataset is the dataset to delete.
                     * \return Return true if deletion successful, false if fails.
                     */
                    bool deleteDataset(const Dataset& dataset);
                    /*!
                     * \brief The method delete the dataset.
                     * \param dataset name is the dataset to delete.
                     * \return Return true if deletion successful, false if fails.
                     */
                    bool deleteDataset(const QString& dataset);
                    /*!
                     * \brief when DatasetDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                     */
                    DatasetDAO();
                    /*!
                     * \brief The method get all subjects of dataset.
                     * \param dataset is the dataset.
                     * \return Return a vector with the subjects.
                     */
                    QVector<ASubject*> getAllSubjectsOfDataset(const QString& dataset);
                    /*!
                     * \brief The method get the dataset by name.
                     * \param name is the name of the dataset.
                     * \return Return a dataset pointer.
                     */
                    Dataset *getDatasetByName(const QString& name);
                };

            } // namespace DAO
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_DATASETDAO_H
