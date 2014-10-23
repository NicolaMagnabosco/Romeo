#ifndef ROMEO_MODEL_UTIL_DAO_ADATABASE_H
#define ROMEO_MODEL_UTIL_DAO_ADATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql/QtSql>
#include "utils.h"


/*!
 *\file adatabase.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-21
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-21 |   Luisetto Luca |  Romeo::Model::Util::Dao::ADatabase                        |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/


namespace Romeo {

    namespace Model {

        namespace Util {

            namespace DAO {
                 /*!
                 * \brief The ADatabase class inherits from QSqlDatabase, it represent a database connection and provide 2 methods to
                 * connect and disconnect the database, where is store all the data of Romeo
                 */
                class ADatabase
                {
                private:
                    /*!
                     * \brief Name of the database.
                    */
                    QString dbName;
                    /*!
                     * \brief Sql database connection object.
                    */
                    static QSqlDatabase connection;
                    /*!
                     * \brief This method return the schema Sql for the database creation.
                     * \return Return the list of creation query.
                    */
                    QStringList getCreationSchema() const;

                protected:      
                    /*!
                     * \brief This method return the connection pointer.
                     * \return Return a pointer to the connection.
                    */
                    static QSqlDatabase* getConnection();

                public:
                    /*!
                     * \brief constructs the object, it set the driver for the specific database and set the path of the database
                     */
                    ADatabase();

                    /*!
                      * \brief open the database connection
                      * \return bool, it returns true if database connect successsfully, false otherwise
                      */
                     bool connect();

                     /*!
                      * \brief close the database connection
                      * \return bool, it returns true if database disconnect successsfully, false otherwise
                      */
                     bool disconnect();

                     /*!
                      * \brief Destroy the database object and delete the connection.
                     */
                     virtual ~ADatabase();
                };

            } // namespace DAO

        } // namespace Util

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_DAO_ADATABASE_H
