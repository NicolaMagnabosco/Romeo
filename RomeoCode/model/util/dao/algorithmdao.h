#ifndef ROMEO_MODEL_UTIL_DAO_ALGORITHMDAO_H
#define ROMEO_MODEL_UTIL_DAO_ALGORITHMDAO_H


#include "model/util/dao/adatabase.h"
#include "model/core/algorithm/aalgorithm.h"
#include "model/core/algcreator.h"
#include "model/core/protocol.h"
#include <QDate>

using Romeo::Model::Util::DAO::ADatabase;
using Romeo::Model::Core::Algorithm::AAlgorithm;
using Romeo::Model::Core::Protocol;

/*!
 *\file algorithmdao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-21
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-21 |   Luisetto Luca |  Romeo::Model::Util::Dao::AlgorithmDAO                     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/


namespace Romeo {
    namespace Model {
        namespace Util {
            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the algorithm table of the database.
                 */
                class AlgorithmDAO : public Romeo::Model::Util::DAO::ADatabase
                {

                public:
                    /*!
                     * \brief when AlgorithmDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                     */
                    AlgorithmDAO();
                    /*!
                     * \brief getAlgorithmById, this method return the algorithm with the parameter id
                     * \param id
                     * \return IAlgorithm*
                     */
                    AAlgorithm* getAlgorithmById(int id);
                    /*!
                     * \brief addAlgorithm, this method add param algorithm to database
                     * \param algorithm
                     */
                    int addAlgorithm(const AAlgorithm& algorithm);
                    /*!
                     * \brief deleteAlgorithm this method delete from database the parameter algorithm
                     * \param algorithm
                     */
                    bool deleteAlgorithm(const AAlgorithm& algorithm);
                    /*!
                     * \brief deleteAlgorithm this method delete from database an algorithm with name and param
                     * \param name
                     * \param param
                     */
                    bool deleteAlgorithm(const QString& name, const QString& param);
                    /*!
                     * \brief  this method return all algorithm that are contained in database
                     * \return QVector<Algorithm*>
                     */
                    QVector<AAlgorithm*> getAllAlgorithm();
                    /*!
                     * \brief get the Algorithm of the given Protocol
                     * \param Protocol which take the algorithm
                     * \return a pointer to the desired Algorithm
                     */
                    AAlgorithm* getAlgorithmOfProtocol(const Protocol& protocol);
                    /*!
                     * \brief get the Algorithm of a Protocol provide the Protocol name
                     * \param the protocol name which take the algorithm
                     * \return a pointer to the desired Algorithm
                     */
                    AAlgorithm* getAlgorithmOfProtocol(const QString& protocolName);
                    /*!
                     * \brief The method delete the algorithm by id.
                     * \param id is the id of the algorithm to delete.
                     * \return Return true if delete successful, false if fails.
                     */
                    bool deleteAlgorithm(const int id);
                    /*!
                     * \brief The method update the algorithm passed on the parameter.
                     * \param newAlg is the new algorithm informations.
                     * \param oldAlg is the old algorithm to modify.
                     * \return Return the id of the updated algorithm.
                     */
                    int updateAlgorithm(const AAlgorithm *newAlg, const AAlgorithm *oldAlg);
                };

            } // namespace DAO
        } // namespace Util
    } // namespace Model
} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_ALGORITHMDAO_H
