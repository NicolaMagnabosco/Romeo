#ifndef ROMEO_MODEL_UTIL_DAO_GROUPDAO_H
#define ROMEO_MODEL_UTIL_DAO_GROUPDAO_H

#include <QString>
#include <QVector>
#include "model/core/groupofsubject.h"
#include "model/core/asubject.h"
#include "model/util/dao/adatabase.h"
#include "model/core/proxysubject.h"
#include "model/util/dao/subjectdao.h"
#include "utils.h"
#include <QDateTime>
#include <QSqlQuery>

using Romeo::Model::Core::GroupOfSubject;
using Romeo::Model::Core::ASubject;
using Romeo::Model::Util::DAO::ADatabase;
/*!
 *\file groupdao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-23
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-23 |   Luisetto Luca |      Romeo::Model::Util::Dao::GroupDAO                     |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Util {

            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the group of subjects table of the database.
                 */
                class GroupDAO : public ADatabase
                {
                public:
                    /*!
                     * \brief when GroupDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                     */
                    GroupDAO();
                    /*!
                     * \brief existGroupWithName, this method return true if a Group with the name contatined in parameter name, exists in database
                     * \param name
                     * \return
                     */
                    bool existGroupWithName(const QString& name);
                    /*!
                     * \brief This method test if exists a group with name in the parameter and differente to the oldName.
                     * \param name
                     * \return Return true if exists a Group with the newName name and different to oldName, false if not exists a group with newName name.
                     */
                    bool existGroupWithName(const QString& newName, const QString& oldName);
                    /*!
                     * \brief getAllGroup, this method return a QVector contained all the GroupOfSubject that are in the database
                     * \return QVector<GroupOfSubject*>
                     */
                    QVector<GroupOfSubject*> getAllGroup();
                    /*!
                     * \brief return a QVector that contains the name of each Group of Subject contained in database
                     * \return QVector<QString>
                     */
                    QVector<QString> getAllGroupName();
                    /*!
                     * \brief getGroupByName, this method return the GroupOfSubject with the name contained in the paramenter name
                     * \param name
                     * \return GroupOfSubject*
                     */
                    GroupOfSubject* getGroupByName(const QString& name);
                    /*!
                     * \brief createGroup, this method insert the group contained in paramenter group in the database
                     * \param group
                     */
                    bool createGroup(const GroupOfSubject& group);
                    /*!
                     * \brief deleteGroup, this method delete from the database the group cotained in parameter group
                     * \param group
                     */
                    bool deleteGroup(const QString& group);
                    /*!
                     * \brief addSubject, this method add the parameter subject to the parameter group in database
                     * \param subject
                     * \param group
                     */
                    bool addSubjectToGroup(const ASubject* subject, const GroupOfSubject& group);
                    /*!
                     * \brief removeSubject, this method remove the parameter subject from the parameter group in database
                     * \param subject
                     * \param group
                     */
                    bool removeSubjectFromGroup(const ASubject& subject, const GroupOfSubject& group);
                    /*!
                     * \brief getSubjectOfGroup, this method return all Subject that are member of parameter group
                     * \param group
                     * \return QVector<ASubject*>
                     */
                    QVector<ASubject*> getSubjectsOfGroup(const QString& group);
                    /*!
                     * \brief The method update the group of subjects.
                     * \param group is the updated group.
                     * \return Return true if update successful, false if fails.
                     */
                    bool updateGroupOfSubject(const GroupOfSubject& group);

                };

            } // namespace Dao

        } // namespace Util

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_GROUPDAO_H
