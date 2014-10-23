#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QToolButton>
#include <QFile>
#include "utils.h"
/*!
 *\file toolbar.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-11
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-11 | Bissacco Nicolò |           Romeo::View::Component::toolbar               |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo
{
    namespace View
    {
        namespace Component
        {
            /*!
             * \brief The class ToolBar, extends QToolBar, represents the component located at the top of the view, which contains the menu with all the buttons used to navigate within Romeo.
             * The toolbar can also be moved to the left and to the right in the view.
             */
            class ToolBar : public QToolBar
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Represent a menu for the help.
                 */
                QMenu *menuHelp;

                /*!
                 * \brief Represent an action for the interactive guide item of help menu.
                 */
                QAction *actionHelpInteractiveGuide;
                /*!
                 * \brief Represent an action for the video guide item of help menu.
                 */
                QAction *actionHelpVideoGuide;
                /*!
                 * \brief Represent an action for the about item of help menu.
                 */
                QAction *aboutAction;
                /*!
                 * \brief Represent an action for the shortcuts item of help menu.
                 */
                QAction *shortCutsAction;

                /*!
                 * \brief Represent the Home Button of the toolbar.
                 */
                QToolButton *homeButton;
                /*!
                 * \brief Represent the New Subject Button of the toolbar.
                 */
                QToolButton *newSubjectButton;
                /*!
                 * \brief Represent the Manage Subjects Button of the toolbar.
                 */
                QToolButton *manageSubjectButton;
                /*!
                 * \brief Represent the New Group of Subjects Button of the toolbar.
                 */
                QToolButton *newGroupButton;
                /*!
                 * \brief Represent the Manage Groups of Subjects Button of the toolbar.
                 */
                QToolButton *manageGroupButton;
                /*!
                 * \brief Represent the New Protocol Button of the toolbar.
                 */
                QToolButton *newProtocolButton;
                /*!
                 * \brief Represent the Manage Protocols Button of the toolbar.
                 */
                QToolButton *manageProtocolButton;
                /*!
                 * \brief Represent the New Dataset Button of the toolbar.
                 */
                QToolButton *newDatasetButton;
                /*!
                 * \brief Represent the Manage Datasets Button of the toolbar.
                 */
                QToolButton *manageDatasetButton;
                /*!
                 * \brief Represent the Start Analysis Button of the toolbar.
                 */
                QToolButton *startAnalysisButton;
                /*!
                 * \brief Represent the Show Results of Analysis Button of the toolbar.
                 */
                QToolButton *resultsButton;
                /*!
                 * \brief Represent the Help Button for more Help of the toolbar.
                 */
                QToolButton *helpButton;
                /*!
                 * \brief Represent the Exit Button of the toolbar.
                 */
                QToolButton *exitButton;

                /*!
                 * \brief The method create the Help menu.
                 */
                void createMenus();
                /*!
                 * \brief The method create the connections between buttons and signals.
                 */
                void addConnections();
                /*!
                 * \brief The method setup the menu configurations and create the toolbar components.
                 */
                void setupToolbar();
                /*!
                 * \brief The method create the buttons for the toolbar.
                 */
                void createButtons();
                /*!
                 * \brief The method load the css file for the toolbar style.
                 */
                void loadCss();

            public:
                /*!
                 * \brief Construct a ToolBar with the given parent.
                 * \param parent represent the parent of the ToolBar object.
                 */
                ToolBar(QWidget * parent = 0);

            signals:
                /*!
                 * \brief The backToHome signal is emitted when the home button is pressed.
                 */
                void backToHome();
                /*!
                 * \brief The menuAbout signal is emitted when the about action is pressed.
                 */
                void menuAbout();
                /*!
                 * \brief The menuExit signal is emitted when the exit button is pressed.
                 */
                void menuExit();
                /*!
                 * \brief The createNewSubject signal is emitted when the new subject button is pressed.
                 */
                void createNewSubject();
                /*!
                 * \brief The showSubjects signal is emitted when the manage subjects button is pressed.
                 */
                void showSubjects();
                /*!
                 * \brief The createNewGroup signal is emitted when the new group of subjects button is pressed.
                 */
                void createNewGroup();
                /*!
                 * \brief The showGroups signal is emitted when the manage groups of subjects button is pressed.
                 */
                void showGroups();
                /*!
                 * \brief The createNewProtocol signal is emitted when the new protocol button is pressed.
                 */
                void createNewProtocol();
                /*!
                 * \brief The showProtocols signal is emitted when the manage protocols button is pressed.
                 */
                void showProtocols();
                /*!
                 * \brief The createNewDataset signal is emitted when the new dataset button is pressed.
                 */
                void createNewDataset();
                /*!
                 * \brief The showDatasets signal is emitted when the manage datasets button is pressed.
                 */
                void showDatasets();
                /*!
                 * \brief The startAnalysis signal is emitted when the start analysis button is pressed.
                 */
                void startAnalysis();
                /*!
                 * \brief The showResults signal is emitted when the show analysis results button is pressed.
                 */
                void showResults();
                /*!
                 * \brief The shortCutsSignal signal is emitted when the shortcuts action is pressed.
                 */
                void shortCutsSignal();
                /*!
                 * \brief The helpManualSignal signal is emitted when the interactive guide action is pressed.
                 */
                void helpManualSignal();
                /*!
                 * \brief The helpVideoGuideSignal signal is emitted when the video guide action is pressed.
                 */
                void helpVideoGuideSignal();
            };
        }
    }
}
#endif // TOOLBAR_H
