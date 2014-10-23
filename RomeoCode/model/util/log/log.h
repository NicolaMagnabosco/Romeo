#ifndef ROMEO_MODEL_UTIL_LOG_LOG_H
#define ROMEO_MODEL_UTIL_LOG_LOG_H

#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
/*!
 *\file log.h
 *\author Luisetto Luca (lucaluisetto91@gmail.com)
 *\date 2013-02-24
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                             Changes                        +       Description         |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*|                                                                                                                                  |
*|   0.0.1  | 2013-02-24 |   Luisetto Luca |  Romeo::Model::Util::Dao::Log                              |   First version of class  |
*|                                                                                                                                  |
*+----------+------------+-----------------+------------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Util {

            namespace Log {

                /*!
                 * \brief The class Log represents the component that takes care of generating the log files for user actions.
                 */
                class Log
                {
                private:
                    /*!
                     * \brief Construct a Log object.
                     */
                    Log();

                    /*!
                     * \brief True if log is enabled, false if log is disabled.
                     */
                    static bool enable;

                    /*!
                     * \brief Log folder name.
                     */
                    static const QString folderName;
                    /*!
                     * \brief Log file name for user actions.
                     */
                    static const QString fileUserAction;
                    /*!
                     * \brief Log complete path for user actions.
                     */
                    static const QString userActionFilePath;
                    /*!
                     * \brief Log file name for database query.
                     */
                    static const QString fileDatabaseQuery;
                    /*!
                     * \brief Log complete path for database query.
                     */
                    static const QString databaseQueryFilePath;
                    /*!
                     * \brief Log file name for analysis starts.
                     */
                    static const QString fileAnalysis;
                    /*!
                     * \brief Log complete path for analysis starts.
                     */
                    static const QString analysisFilePath;
                    /*!
                     * \brief Extension of log file.
                     */
                    static const QString extension;
                    /*!
                     * \brief Number of lines inside the log file.
                     */
                    static const int maxLinesPerFile;

                    /*!
                     * \brief This method count the lines in the file.
                     * \param file is the log file.
                     * \return Return an integer which is the number of rows in the file.
                     */
                    static int countLines(QTextStream &file);
                    /*!
                     * \brief This method write the text in the file.
                     * \param txt is the string that is written to the file.
                     * \param fileP is the name of log file.
                     */
                    static void logWriter(const QString& txt, QString fileP);

                public:
                    /*!
                     * \brief This method set the log writer enable or not.
                     * \param enableV is true if log is enable, false if log is disable.
                     */
                    static void setEnable(bool enableV = false);

                    /*!
                     * \brief This enum is used to describe the log type.
                     */
                    enum Type{_USER_ACTION_, _DATABASE_QUERY_, _ANALYSIS_};

                    /*!
                     * \brief This method write a log text based on the type.
                     * \param type is the enum type of the log.
                     * \param txt is the text that is written to the file.
                     */
                    static void writeLog(Type type, const QString& txt);
                };

            } // namespace Log

        } // namespace Util

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_UTIL_LOG_LOG_H
