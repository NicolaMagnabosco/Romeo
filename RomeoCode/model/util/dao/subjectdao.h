#ifndef ROMEO_MODEL_UTIL_DAO_SUBJECTDAO_H
#define ROMEO_MODEL_UTIL_DAO_SUBJECTDAO_H

#include "model/util/dao/adatabase.h"
#include "model/core/groupofsubject.h"
#include <QVector>
#include "model/core/asubject.h"
#include "model/core/proxysubject.h"
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QDateTime>
#include "utils.h"

using Romeo::Model::Util::DAO::ADatabase;
using Romeo::Model::Core::ASubject;
using Romeo::Model::Core::GroupOfSubject;

/*!
 *\file subjectdao.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-24
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-24 |   Luisetto Luca |  Romeo::Model::Util::Dao::SubjectDao                       |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/

using namespace Romeo::Model::Core;

namespace Romeo {

    namespace Model {

        namespace Util {

            namespace DAO {

                /*!
                 * \brief The class ToolBar, extends ADatabase, represents the class that interfaces with the subject table of the database.
                 */
                class SubjectDAO : public ADatabase
                {
                public:
                    /*!
                     * \brief when SubjectDAO is built it call the superclass method connect that create a connection with the database romeodata.sql
                     */
                    SubjectDAO();
                    /*!
                     * \brief return if exists in database a subject with name
                     * \param name represent the name of the subject
                     * \return true if the subject contained in database, false otherwise
                     */
                    bool existSubjecWithName(const QString& name) const;
                    /*!
                     * \brief return an Asubject pointer to a ProxySubject with the name contained in parameter
                     * \param name
                     * \return ASubject pointer to a ProxySubject
                     */
                    ASubject *getSubjectByName(const QString& name) const;
                    /*!
                     * \brief return all the subject that are contained in database
                     * \return a QVector of ASubject* with all subject in database
                     */
                    QVector<ASubject*> getAllSubjects() const;
                    /*!
                     * \brief return all subject name
                     * \return a QVector of QString, each member of vector is the name of one subject contained in database
                     */
                    QVector<QString> getAllSubjectsName() const;
                    /*!
                     * \brief to add a subject in database
                     * \param subject that will insert in database
                     */
                    bool createSubject(const ASubject& subject);
                    /*!
                     * \brief allow to know all subject that are member of a group
                     * \param group that you want to know the subject
                     * \return a QVector of subject that contains all the member of the group
                     */
                    QVector<ASubject*> subjectsOfGroup(const QString& group) const;
                    /*!
                     * \brief The method lets you know which groups the subject belongs.
                     * \param subject name of the subject.
                     * \return Return a QVector of group of subjects name.
                     */
                    QVector<QString> getGroupsOfSubject(const QString& subject) const;
                    /*!
                     * \brief The method get all the subjects by type.
                     * \param type is the type of the subjects.
                     * \return Return a QVector of subjects pointer.
                     */
                    QVector<ASubject*> getSubjectsByType(const QString& type) const;
                    /*!
                     * \brief The method get all the subjects of the dataset.
                     * \param dataset is the of the dataset.
                     * \return Return a QVector of subjects pointer.
                     */
                    QVector<ASubject*> getSubjectsOfDataset(const QString& dataset) const;
                };
            }
        }
    }
}

#endif // ROMEO_MODEL_UTIL_DAO_SUBJECTDAO_H
