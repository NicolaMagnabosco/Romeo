#ifndef ROMEO_CONTROLLER_RESULTSCONTROLLER_H
#define ROMEO_CONTROLLER_RESULTSCONTROLLER_H

/*!
 *\file resultscontroller.h
 *\author Adami Alberto (alberto.adami.7@gmail.com)
 *\date 2013-02-25
*/
/*
*Changes:
*+----------+------------+---------------- +-------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +              Changes                      +       Description         |
*+----------+------------+-----------------+-------------------------------------------+---------------------------+
*|                                                                                                                 |
*|   0.0.1  | 2013-02-15 |   Adami Alberto |  Romeo::Controleller::ResultsController   |   First version of class  |
*|                                                                                                                 |                            |                                                                               |
*+----------+------------+-----------------+-------------------------------------------+---------------------------+
*/

#include <QObject>
#include "controller/acontroller.h"
#include "view/window/resultsview.h"
#include "controller/mainwindowcontroller.h"

using Romeo::Controller::AController;
using Romeo::View::Window::ResultsView;

namespace Romeo {
    namespace Controller {
    /*!
     * \brief The ResultsController class, extends AController, represents the controller for the user inputs of the analysis results view.
     */
        class ResultsController : public AController
        {
            Q_OBJECT

        private:
            /*!
             * \brief idSelected is the id of the analysis selected
             */
            int idSelected;
            /*!
             * \brief titleRestult is the title on the top of the page
             */
            QString titleRestult;

        protected:
            /*!
             * \brief Crea tutte le connessioni.
             */
            virtual void createConnections() const;
        public:
            /*!
             * \brief ResultsController contructor the controller object of the given view and parent
             * \param view is the connected view
             * \param parent is the parent of the controller object
             */
            ResultsController(ResultsView *view, QObject *parent=0);

        public slots:
            /*!
             * \brief slotRowSelected slot recieve the signal when the user select the analysis row
             * \param index is the selected index of the table
             */
            void slotRowSelected(const QModelIndex & index);
            /*!
             * \brief slotRowSelectedDouble slot recieve the signal when the user double click on the analysis row
             * \param index is the selected index of the table
             */
            void slotRowSelectedDouble(const QModelIndex & index);
            /*!
             * \brief slotRestartClicked slot recieve the signal when the user click on restart button
             */
            void slotRestartClicked();
            /*!
             * \brief slotShowClicked slot recieve the signal when the user click on show results of the analysis
             */
            void slotShowClicked();
        };

    } // namespace Controller
} // namespace Romeo

#endif // ROMEO_CONTROLLER_RESULTSCONTROLLER_H
