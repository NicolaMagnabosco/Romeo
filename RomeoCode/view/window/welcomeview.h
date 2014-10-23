#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QHBoxLayout>
#include <QFrame>
#include <QGroupBox>
#include <QWidget>
#include <QPushButton>
#include "view/window/apanel.h"
#include "view/window/mainwindow.h"

using Romeo::View::Window::APanel;
using Romeo::View::Window::MainWindow;
/*!
 *\file welcomeview.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-20
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-20 | Bissacco Nicolò |           Romeo::View::Window::WelcomeView              |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {
    namespace View {
        namespace Window {
            /*!
             * \brief The WelcomeView class is the main window of Romeo. Is the first page. Is the Home page.
             */
            class WelcomeView : public APanel
            {
                Q_OBJECT
            private:
                //methods
                /*!
                 * \brief The method create the left frame of the view.
                 */
                void setupLeftFrame();
                /*!
                 * \brief The method create the right frame of the view.
                 */
                void setupRightFrame();

                //members
                    QFrame *frameLeft;
                        QGroupBox *boxSubject;
                            QPushButton *btnNewSubject;
                            QPushButton *btnShowSubject;
                        QGroupBox *boxGroup;
                            QPushButton *btnNewGroup;
                            QPushButton *btnShowGroup;
                        QGroupBox *boxProtocol;
                            QPushButton *btnNewProtocol;
                            QPushButton *btnShowProtocol;
                        QGroupBox *boxDataset;
                            QPushButton *btnNewDataset;
                            QPushButton *btnShowDataset;
                    QFrame *frameRight;
                        QGroupBox *boxAnalysis;
                            QPushButton *btnStartAnalysis;
                            QPushButton *btnAnalysisResults;
                        QGroupBox *boxGuide;
                            QPushButton *btnUserGuide;
                            QPushButton *btnVideoGuide;
                        QGroupBox *boxInfo;
                            QPushButton *btnShortcuts;
                            QPushButton *btnAbout;
                        QGroupBox *boxExit;
                            QPushButton *btnExit;
                        QWidget *widgetRomeo;

            protected:
                /*!
                 * \brief The method create the connections of the view.
                 */
                virtual void addConnect() const;
                /*!
                 * \brief The method create the connections of the view.
                 */
                virtual void setupView();
                /*!
                 * \brief The method create the name of the Qt objects.
                 */
                virtual void setupObjectName();
                /*!
                 * \brief The method load the style of the view.
                 */
                virtual void loadCss();
                /*!
                 * \brief The method create the tooltips of the view.
                 */
                virtual void setupToolTip();
                /*!
                 * \brief The method setupt the layout of the view.
                 */
                virtual void setupLayout();

            public:
                /*!
                 * \brief Construct a WelcomeView object with the given parent.
                 * \param parent rappresents the parent of the WelcomeView.
                 */
                WelcomeView(QWidget *parent= 0);

            signals:
                /*!
                 * \brief The signal is emitted when the user click on new subject button.
                 */
                void createNewSubject();
                /*!
                 * \brief The signal is emitted when the user click on show subjects button.
                 */
                void showSubjects();
                /*!
                 * \brief The signal is emitted when the user click on new group of subjects button.
                 */
                void createNewGroup();
                /*!
                 * \brief The signal is emitted when the user click on show groups of subjects button.
                 */
                void showGroups();
                /*!
                 * \brief The signal is emitted when the user click on new protocol button.
                 */
                void createNewProtocol();
                /*!
                 * \brief The signal is emitted when the user click on show protocols button.
                 */
                void showProtocols();
                /*!
                 * \brief The signal is emitted when the user click on new dataset button.
                 */
                void createNewDataset();
                /*!
                 * \brief The signal is emitted when the user click on show datasets button.
                 */
                void showDatasets();
                /*!
                 * \brief The signal is emitted when the user click on start analysis button.
                 */
                void startAnalysis();
                /*!
                 * \brief The signal is emitted when the user click on show analysis results button.
                 */
                void showResults();
                /*!
                 * \brief The signal is emitted when the user click on interactive guide button.
                 */
                void userGuide();
                /*!
                 * \brief The signal is emitted when the user click on video guide button.
                 */
                void videoGuide();
                /*!
                 * \brief The signal is emitted when the user click on nshortcuts list button.
                 */
                void shortcutsList();
                /*!
                 * \brief The signal is emitted when the user click on about us button.
                 */
                void aboutus();
                /*!
                 * \brief The signal is emitted when the user click on exit button.
                 */
                void exitSignal();
            };
        }
    }
}
#endif // WELCOMEVIEW_H
