#ifndef ROMEO_VIEW_WINDOW_RESULTSVIEW_H
#define ROMEO_VIEW_WINDOW_RESULTSVIEW_H

#include "view/window/apanel.h"
#include "view/component/navwidget.h"
#include <QVBoxLayout>
#include <QTableView>
#include "view/window/mainwindow.h"
#include "model/qtModel/resultstablemodel.h"
#include <QHeaderView>
#include <QVector>

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::ResultsTableModel;
/*!
 *\file resaultview.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-18
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-18 | Bissacco Nicolò |           Romeo::View::Window::ResaultsView             |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Window {

            /*!
             * \brief The ResultsView class represent the page for the list of analysis results.
             */
            class ResultsView : public APanel
            {
                Q_OBJECT
            private:              
                /*!
                 * \brief model is the model for the table of analysis results.
                 */
                ResultsTableModel *model;

                QTableView *tableView;
                NavWidget *bottomWidget;

                /*!
                 * \brief createTop method create the objects of the top of the view.
                 */
                void createTop();
                /*!
                 * \brief createBottom method create the objects of the bottom of the view.
                 */
                void createBottom();

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
                 * \brief ResultsView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                ResultsView(QWidget *parent =0);
                /*!
                 * \brief getModel get the table model
                 * \return Return a pointer to the model
                 */
                QAbstractItemModel *getModel() const;
                /*!
                 * \brief enableButtons method enable the bottom buttons
                 */
                void enableButtons();

            signals:
                /*!
                 * \brief rowSelected signal is emitted when the user select an item from the table.
                 * \param index is the table index of the selection.
                 */
                void rowSelected(const QModelIndex & index);
                /*!
                 * \brief rowSelectedDouble signal is emitted when the user double click on the item of the table
                 * \param index  is the table index of the selection.
                 */
                void rowSelectedDouble(const QModelIndex & index);
            };

        } // namespace Window
    } // namespace View
} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_RESULTSVIEW_H
