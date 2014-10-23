#ifndef ROMEO_MODEL_CORE_GROUPOFSUBJECT_H
#define ROMEO_MODEL_CORE_GROUPOFSUBJECT_H

#include <QVector>
#include <QString>
#include "model/core/asubject.h"

using Romeo::Model::Core::ASubject;

/*!
 *\file groupofsubject.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-15
*/
/*
*Changes:
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description             |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*|                                                                                                               |
*|   0.0.1  | 2013-02-15 |   Adami Alberto |    Romeo::Model::GroupOfSubject     |   First version of class      |
*|                                                                                                               |
*|   0.0.2  | 2013-03-06 |   Adami Alberto |    Romeo::Model::GroupOfSubject     |   Complete the class          |
*|                                                                                                               |
*|   0.0.3  | 2013-03-22 |   Adami Alberto |    Romeo::Model::GroupOfSubject     |Definitive version of the class|                                                                                                         |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------+-------------------------------+
*/

namespace Romeo {

    namespace Model {

        namespace Core {

            /*!
             * \brief The GroupOfSubject class represent a group of subject in the Romeo's system.
             * A GroupOfSubject object varies in time.
             * At the beginning the group is empty and subsequently can be added and removed subject to the group.
             */
            class GroupOfSubject
            {
            private:
                /*!
                 * \brief imageType represents the type of group(2D, 2D-t, 3D, 3D-t).
                 */
                QString imageType;
                /*!
                 * \brief name represents the name of the group of subjcect.
                 */
                QString name;
                /*!
                 * \brief subjects contain all the subject present in the group.
                 */
                QVector<ASubject*> subjects;
                /*!
                 * \brief creationDate represents the date when the group has been created.
                 */
                QDateTime creationDate;
            public:
                /*!
                 * \brief Constructs a Group0fSubject with the given name, type, subjects list and cretion date.
                 * \param nameGroup represents the name of the group.
                 * \param imageType represents the type of the group (2D, 2D-t, 3D, 3D-t).
                 * \param subjectsV represents the list of subjects in the group.
                 * \param dateTime reprsents the creation date of the subject.c
                 */
                GroupOfSubject(const QString& nameGroup, const QString& imageType, QVector<ASubject*> subjectsV = QVector<ASubject*>(), const QDateTime& dateTime = QDateTime());
                /*!
                 * \brief Method that return the name of the group.
                 * \return  Return a QString containing the name of the group.
                 */
                QString getName() const;
                /*!
                 * \brief Method that return the type of the group (2D, 2D-t, 3D, 3D-t).
                 * \return Return a QString containing the type of the group.
                 */
                QString getImageType() const;
                /*!
                 * \brief Method that return the creation date of the group.
                 * \return Return a QDateTime containing the creation date of the group.
                 */
                QDateTime getCreationDate() const;

                /*!
                 * \brief Method that add the given subject at the group, if there isn't already.
                 * \param subject represents the subject to add to the group.
                 * \return Return a bool that indicates the state of the operation.
                 * True indicate that the insert was performed with success.
                 * False indicate that the insert wasn't performed with success.
                 */
                bool addSubject(const ASubject& subject);
                /*!
                 * \brief Method that search if the GroupOfSubject contains the given subject.
                 * \param subject represent the Subject to find in the GroupOfSubject.
                 * \return Return a bool that indicates the state of the operation.
                 * True indicate that the insert was performed with success.
                 * False indicate that the insert wasn't performed with success.
                 */
                bool containSubject(const ASubject& subject) const;
                /*!
                 * \brief Method that return a pointer to the subject with the given name.
                 * \param name represent the name of the subject.
                 * \return Return an ASubject* pointer, if the subject isn't present in the group
                 * is returned a null pointer.
                 */
                ASubject *getSubjectWithName(const QString& name) const;
                /*!
                 * \brief Method that remove the given subject from the group.
                 * \param subject represent the subject to be removed from the group.
                 * \return Return a bool that indicates the state of the operation.
                 * True indicate that the remove was performed with success.
                 * Flse indicate that the remove wasn't performed with success.
                 */
                bool removeSubject(const ASubject& subject);
                /*!
                 * \brief Method that return all the subjects present in the group.
                 * \return Return a QVector containing all the subjects in the group.
                 */
                QVector<ASubject*> getAllSubjects() const;
                /*!
                 * \brief Method that return the number of subject in the group.
                 * \return Return an int that represents the number of subject in the group.
                 */
                int subjectsCount() const;
                /*!
                 * Destroy the GroupOfSubject's object.
                 */
                ~GroupOfSubject();
            };

        }

    }

}

#endif // ROMEO_MODEL_CORE_GROUPOFSUBJECT_H
