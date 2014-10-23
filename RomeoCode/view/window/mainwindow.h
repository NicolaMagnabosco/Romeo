#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include "view/component/toolbar.h"
#include "view/window/apanel.h"
#include <QShortcut>
#include "utils.h"
#include <QCloseEvent>
#include "view/dialog/dialog.h"
#include "model/help/assistant.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::ToolBar;
using Romeo::Model::Help::Assistant;

/*!
*\file mainwindow.h
*\author Bissacco Nicolò (nickbissa@gmail.com)
*\date 2013-02-13
*\brief The MainWindow class provides the main application window of Romeo.
*/
/*
*Changes:
*+----------+------------+---------------- +--------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +         Changes                +       Description         |
*+----------+------------+-----------------+--------------------------------+---------------------------+
*|                                                                                                      |
*|   0.0.1  | 2013-02-13 | Bissacco Nicolò | Romeo::View::Window::MainWindow  | First version of class  |
*|                                                                                                      |
*+----------+------------+-----------------+--------------------------------+---------------------------+
*/

namespace Romeo
{
    namespace View
    {
        namespace Window
        {
            /*!
             * \brief The MainWindow class represent the main window of Romeo software.
             */
            class MainWindow : public QMainWindow
            {
                Q_OBJECT

            protected:
                /*!
                 * \brief Reimplemented from QDialog::closeEvent().
                 * This event handler is called with the given event when Qt receives a window close request for a top-level widget from the window system.
                 */
                virtual void closeEvent(QCloseEvent *event);

            private:
                /*!
                 * \brief assistant is a pointer to the interactive view.
                 */
                Assistant *assistant;
                /*!
                 * \brief central is a pointer to the widget on the center of the window.
                 */
                APanel *central;
                /*!
                 * \brief toolBar is a pointer to the toolbar object.
                 */
                ToolBar *toolBar;

                /*!
                 * \brief mainWindow represent the unique instance of MainWindow available.
                 */
                static MainWindow *mainWindow;

                /*!
                 * \brief loadCss load the style of Romeo.
                 */
                void loadCss() const;

                /*!
                 * \brief setupMainWindow setup the window properties.
                 */
                void setupMainWindow();

                /*!
                 * \brief addConnections method add the main connections of the view.
                 */
                void addConnections() const;

                /*!
                 * \brief shortcuts is a vector with the list of the shortcuts.
                 */
                QVector<QShortcut*> shortcuts;
                /*!
                 * \brief createShortCuts method create the shortcuts and connections.
                 */
                void createShortCuts();

                /*!
                *\brief Constructs a MainWindow with the given parent.
                * The class is implementated with the design pattern Singleton.
                *\param parent rappresents the parent of the MainWindow object created.
                */
                MainWindow(QWidget *parent = 0);

            public:

                /*!
                 * \brief getMainWindow represent the static access to obtain the unique instance of MainWindow' s class.
                 * \return the unique instance of MainWindow's object.
                 */
                static MainWindow * getMainWindow();

                /*!
                 *\brief Sets the given widget to be the MainWindow's central widget.
                 *The central object have to be an object of a subclass of APanel class.
                 *\param central rappresent the central widget to set as MainWindow's centralwidget.
                 *\return void
                */
                void addCentralWidget(APanel *);                

                /*!
                 * \brief getToolBar method get the toolbar pointer.
                 * \return Return the toolbar pointer.
                 */
                ToolBar * getToolBar() const;

                /*!
                 * \brief loadCssStatic method load the style file.
                 * \param path is the path to the style file.
                 * \return Return a string with the contents of the file.
                 */
                static QString loadCssStatic(const QString& path);

                /*!
                 * \brief getShotcuts method get the shortcuts vector.
                 * \return Return the shortcuts vector.
                 */
                QVector<QShortcut*> getShotcuts() const;

                /*!
                 * \brief setShortcutHomeEnable method set the shortcuts enable or not in the main page of Romeo.
                 * \param enable true if shortcuts enable, false if not.
                 */
                void setShortcutHomeEnable(bool enable);

                /*!
                 * \brief getCentralWidget method get the pointer to the central widget.
                 * \return Return a pointer to the central widget.
                 */
                APanel *getCentralWidget() const;
                /*!
                 * \brief showHelp method show the interactive guide.
                 * \param page is the page where the guide is called.
                 * \param anchor is the anchor of the html page.
                 */
                void showHelp(const QString &page, const QString &anchor = "") const;

            public slots:
                /*!
                 * \brief writeStatusBar method allows to write on the main window status bar.
                 * \param txt is the text to show on status bar.
                 * \param timeout is the time for which the message is displayed.
                 */
                void writeStatusBar(const QString& txt, int timeout =0);

            signals:
                /*!
                 * \brief homeSC signal is emitted when the home shortcut is activated.
                 */
                void homeSC();
                /*!
                 * \brief aboutSC signal is emitted when the about us shortcut is activated.
                 */
                void aboutSC();
                /*!
                 * \brief exitSC signal is emitted when the exit shortcut is activated.
                 */
                void exitSC();
                /*!
                 * \brief createNewSubjectSC signal is emitted when the new subject shortcut is activated.
                 */
                void createNewSubjectSC();
                /*!
                 * \brief showSubjectsSC signal is emitted when the manage subjects shortcut is activated.
                 */
                void showSubjectsSC();
                /*!
                 * \brief createNewGroupSC signal is emitted when the new group shortcut is activated.
                 */
                void createNewGroupSC();
                /*!
                 * \brief showGroupsSC signal is emitted when the manage groups shortcut is activated.
                 */
                void showGroupsSC();
                /*!
                 * \brief createNewProtocolSC signal is emitted when the new protocol shortcut is activated.
                 */
                void createNewProtocolSC();
                /*!
                 * \brief showProtocolsSC signal is emitted when the manage protocols shortcut is activated.
                 */
                void showProtocolsSC();
                /*!
                 * \brief createNewDatasetSC signal is emitted when the new dataset shortcut is activated.
                 */
                void createNewDatasetSC();
                /*!
                 * \brief showDatasetsSC signal is emitted when the manage datasets shortcut is activated.
                 */
                void showDatasetsSC();
                /*!
                 * \brief startAnalysisSC signal is emitted when the start analysis shortcut is activated.
                 */
                void startAnalysisSC();
                /*!
                 * \brief showResultsSC signal is emitted when the show analysis results shortcut is activated.
                 */
                void showResultsSC();
                /*!
                 * \brief helpVideoGuideSC signal is emitted when the video guide shortcut is activated.
                 */
                void helpVideoGuideSC();
                /*!
                 * \brief helpManualSC signal is emitted when the interactive guide shortcut is activated.
                 */
                void helpManualSC();
                /*!
                 * \brief shortCutsSC signal is emitted when the show shortcuts shortcut is activated.
                 */
                void shortCutsSC();
                /*!
                 * \brief helpPage signal is emitted when the help button is clicked.
                 */
                void helpPage();
            };
        }

    }

}
#endif // MAINWINDOW_H
