#ifndef ROMEO_CONTROLLER_MAINWINDOWCONTROLLER_H
#define ROMEO_CONTROLLER_MAINWINDOWCONTROLLER_H

#include <QObject>
#include "view/window/apanel.h"
#include "view/window/mainwindow.h"
#include "controller/acontroller.h"
#include "model/util/log/log.h"

using Romeo::View::Window::APanel;
using Romeo::View::Window::MainWindow;
using Romeo::Controller::AController;

/*!
 *\file mainwindowcontroller.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-13
*/
/*
*Changes:
*+----------+------------+---------------- +--------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                  Changes                   +       Description         |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*|                                                                                                                  |
*|   0.0.1  | 2013-02-13 |   Adami Alberto |  Romeo::Controleller::MainWindowController |   First version of class  |
*|                                                                                                                  |
*|  0.0.2   | 2013-03-03 |   Adami Alberto |  Romeo::Controller::MainWindowController   |   Add all the slots       |
*+----------+------------+-----------------+--------------------------------------------+---------------------------+
*/


namespace Romeo {

    namespace Controller {

        /*!
         * \brief The MainWindowController class have the goal to control a MainWindow's object.
         */
        class MainWindowController : public QObject
        {
            Q_OBJECT
        private:
            /*!
              * \brief Construct a MiainWindowController with the given main and parent.
              * \param main rappsent the MainWindow's object to manage.
              * \param parent rappresent the parent of the MainWindow's object.
              */
             MainWindowController(MainWindow * main, QObject * parent = 0);
            /*!
             * \brief mainWindowController represent the unique instance of MainWindowController available.
             */
            static MainWindowController * mainWindowController;
            /*!
             * \brief Create all the connection of the controller.
             */
            void createConnections() const;
            /*!
             * \brief mainView represents the MainWindow' s object that the MainWindowController is managing.
             */
            MainWindow * mainView;
            /*!
             * \brief registerToSystem has the goal to set the main content of the MainWindow with the given view.
             * Finally the method pass the controller to the addController method of the class ControllerManager.
             * \param view represent the view to display how main contents in the mainwindow.
             * \controller represent the controller of the view.
             */
            void registerToSystem(APanel * view, AController * controller) const;
            /*!
             * \brief firstOpen indicate if is the first time that the MainWindow is displayed.
             */
            bool firstOpen;

        public:
            /*!
             * \brief getMainWindowController represent the static access to obtain the unique instance of MainWindowController' s class.
             * \return the unique instance of MainWindowController's object.
             */
             static MainWindowController * getMainWindowController();
             /*!
              * \brief Destruct the controller anda the mainView object.
              */
             ~MainWindowController();
        public slots:
             /*!
              * \brief slotWelcome allow to the user to return at the WelcomeView.
              * This slot is executed when the user decided to go to the welcome view.
              */
             void slotWelcome();
             /*!
              * \brief slotNewSubject allow to the user to create a new subject in the system.
              * This slot is executed when the user decided to create a new subject.
              */
             void slotNewSubject();
             /*!
              * \brief slotSHowSubjecs allow to the user to visualize the available subjects.
              * This slot is executed when the user decided to visualize the subjects.
              */
             void slotShowSubjects();
             /*!
              * \brief slotNewGroup allow to the user to create a new group.
              * This slot is executed when the user decided to create a new group of subject.
              */
             void slotNewGroup();
             /*!
              * \brief slotEditGroup allow to the user to change an existent group of subject.
              * This slot is executed when the user decided to change a group.
              * \param group represent the name of the group
              */
             void slotEditGroup(const QString & group);
             /*!
              * \brief slotShowGroups allow to the user to visualize the available group of subjects.
              * This slot is executed when the user decided to visualize the groups of subject.
              * \param from represent the view from which the user decided to go to the show group view.
              */
             void slotShowGroups(const QString & from = "");

             /*!
              * \brief slotNewProtocol allow to the user to create a new protocol.
              * This slot is executed when the user decided to create a new protocol.
              */
             void slotNewProtocol();
             /*!
              * \brief slotEditProtocol allow to the user to change an exisstent protocol.
              * This slot is executed when the user decided to change a protocol.
              * \param protocol is the name of the protocol of wich the user want to change.
              */
             void slotEditProtocol(const QString & protocol);
             /*!
              * \brief slotShowProtocols allow to the user to visualize the available protocols.
              * This slot is executed when the user decided to create a new procol.
              * \param from represent the view from wich the user decided to go to the show protocols view.
              */
             void slotShowProtocols(const QString & from = "");
             /*!
              * \brief slotNewDataset allow to the user to create a new dataset.
              * This slot is executed when the user decided to create a new dataset.
              */
             void slotNewDataset();
             /*!
              * \brief slotShowDatasets allow to the user to visualize the available datasets.
              * This slot is executed when the user decided to visualize the datasets.
              * \param from represent the view from wich the user decided to go to the show datasets view
              */
             void slotShowDatasets(const QString & from = "");
             /*!
             * \brief slotStartAnalysis allow to the user to start a new analysis.
             * This slot is executed when the user decided to start a new analysis with Romeo.
             */
             void slotStartAnalysis();
             /*!
              * \brief slotRestartAnalysis allow to the user to restart a previous analysis.
              * This slot is executed when the user decided to restart a previous analysis.
              * \param id represent the id the anlysis the user want to restart.
              */
             void slotRestartAnalysis(int id);
             /*!
              * \brief slotAnalysisResults allow to the user to visualize the details of the previous analysis executed.
              * This slot is executed when the user decided to visualize the result of previous analysis.
              * \param from
              */
             void slotAnalysisResults(int from = 1);
             /*!
             * \brief slotDetailedResults allow to the user to show the details of a specific analysys.
             * This slot is executed when the user decided to visualize a specifi results.
             * \param id is the id of the analysis of which the user want to see details.
             * \ title is the title at the top of the detailed results page
             */
             void slotDetailedResults(int id, const QString & title);
             /*!
             * \brief slotAboutRomeo allow to the user to visulize information about Romeo.
             * This slot is executed when the user decided to visualize the information about Romeo.
             */
             void slotAboutRomeo();
             /*!
              * \brief slotShortCuts allow to the user to visualize the ShortCuts used in Romeo.
              * This slot is executed when the user decided to visualize the shortcuts used in Romeo.
             */
             void slotShortCuts();
            /*!
             * \brief slotCloseRomeo is executed when the user decided to exit from the Romeo application.
            */
             void slotCloseRomeo();
            /*!
             * \brief slotHelp allow to visualize the User Manual of Romeo.
             * This slot is executed when the user decided to visualize the Romeo User Manual.
            */
             void slotHelp();

             /*!
              * \brief slotHelpPage allow to visualize the User Manual of Romeo with a specific page.
              * This slot is executed when the user decided to visualize the Romeo User Manual from a view.
             */
             void slotHelpPage();
             /*!
              * \brief slotHelpVideo allo to the user to visualize the Video Guide of Romeo.
              * This slot is executed when the user decided to visualize the Romeo Vieo Guide-
              */
             void slotHelpVideo();

        };

    } // namespace Controller

} // namespace Romeo

#endif // ROMEO_CONTROLLER_MAINWINDOWCONTROLLER_H
