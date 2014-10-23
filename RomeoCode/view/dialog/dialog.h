#ifndef DIALOG_H
#define DIALOG_H

#include <QMessageBox>
#include <QIcon>
/*!
 *\file dialog.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-12
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-12 | Bissacco Nicolò |Romeo::View::Dialog::Dialog                              |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo
{
    namespace View
    {
        namespace Dialog
        {
            /*!
             * \brief The class Dialog, extends QMessageBox, represents the dialog show to the users.
             */
            class Dialog : public QMessageBox
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Construct a Dialog with the given parameters.
                 * \param title represent the title of the dialog.
                 * \param text represent the message box text to be displayed.
                 * \param info represent the informative text that provides a fuller description for the message.
                 * \param detail represent the text to be displayed in the details area.
                 * \param parent represent the parent of the Dialog object.
                 */
                Dialog(const QString& title, const QString& text, const QString& info ="", const QString& detail ="", QWidget *parent = 0);

            public:
                /*!
                 * \brief The method create an informative dialog box with the given parameters.
                 * \param title represent the title of the dialog.
                 * \param text represent the message box text to be displayed.
                 * \param info represent the informative text that provides a fuller description for the message.
                 * \param detail represent the text to be displayed in the details area.
                 * \param parent represent the parent of the Dialog object.
                 * \return Returns a DialogCode result.
                 */
                static int dialogInfo(const QString& title, const QString& text, const QString& info ="", const QString& detail ="", QWidget *parent = 0);
                /*!
                 * \brief The method create an asking dialog box with the given parameters.
                 * \param title represent the title of the dialog.
                 * \param text represent the message box text to be displayed.
                 * \param info represent the informative text that provides a fuller description for the message.
                 * \param detail represent the text to be displayed in the details area.
                 * \param parent represent the parent of the Dialog object.
                 * \return Returns a DialogCode result.
                 */
                static int dialogQuestion(const QString& title, const QString& text, const QString& info ="", const QString& detail ="", QWidget *parent = 0);
                /*!
                 * \brief The method create a warning dialog box with the given parameters.
                 * \param title represent the title of the dialog.
                 * \param text represent the message box text to be displayed.
                 * \param info represent the informative text that provides a fuller description for the message.
                 * \param detail represent the text to be displayed in the details area.
                 * \param parent represent the parent of the Dialog object.
                 * \return Returns a DialogCode result.
                 */
                static int dialogWarning(const QString& title, const QString& text, const QString& info ="", const QString& detail ="", QWidget *parent = 0);
                /*!
                 * \brief The method create a critical dialog box with the given parameters.
                 * \param title represent the title of the dialog.
                 * \param text represent the message box text to be displayed.
                 * \param info represent the informative text that provides a fuller description for the message.
                 * \param detail represent the text to be displayed in the details area.
                 * \param parent represent the parent of the Dialog object.
                 * \return Returns a DialogCode result.
                 */
                static int dialogCritical(const QString& title, const QString& text, const QString& info ="", const QString& detail ="", QWidget *parent = 0);
            };
        }
    }
}

#endif // DIALOG_H
