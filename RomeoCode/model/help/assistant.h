#ifndef ROMEO_MODEL_HELP_ASSISTANT_H
#define ROMEO_MODEL_HELP_ASSISTANT_H

#include <QString>
#include <QProcess>

/*!
 *\file algreator.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-05-21
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------+------------------------------+
*|  Version +    Date    +   Programmer    +              Changes                +       Description            |
*+----------+------------+-----------------+-------------------------------------+------------------------------+
*|                                                                                                              |
*|   0.0.1  | 2013-05-21 |   Adami Alberto |  Romeo::Model::Help::Assitant       |   First version of class     |
*|                                                                                                              |
*+----------+------------+-----------------+-------------------------------------+------------------------------+
*/
namespace Romeo {

    namespace Model {

        namespace Help {
            /*!
             * \brief The Assistant class provides the functionality for start the Qt Assistant process.
             */
            class Assistant
            {
            private:
                /*!
                 * \brief process represents the pointer to the Qt assistant process
                 */
                QProcess *process;
                /*!
                 * \brief Method that check if the assistant is already start.
                 * Otherwise start the assitant process.
                 * \return Return a QProcess object that represent the QT assistant process.
                 */
                bool startAssistant();
            public:
                /*!
                 * \brief Construct an Assitant's object.
                 */
                Assistant();
                /*!
                 * \brief Method that show the file HTML page in the Qt Assistant help.
                 * \param file represent the file to show.
                 * \param anchor is the anchor of the html page.
                 */
                void showDocumentation(const QString &file, const QString &anchor = "");
                /*!
                 * \brief Destruct the Assistant's object.
                 */
                virtual ~Assistant();
            };

        } // namespace Help

    } // namespace Model

} // namespace Romeo

#endif // ROMEO_MODEL_HELP_ASSISTANT_H
