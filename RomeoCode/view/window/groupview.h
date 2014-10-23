#ifndef ROMEO_VIEW_WINDOW_GROUPVIEW_H
#define ROMEO_VIEW_WINDOW_GROUPVIEW_H

#include "view/window/apanel.h"
#include "view/component/navwidget.h"
#include <QTableView>
#include <QGroupBox>
#include "view/window/mainwindow.h"
#include "model/qtModel/grouptablemodel.h"
#include <QHeaderView>
#include "model/qtModel/groupsubjectstablemodel.h"
#include <QSortFilterProxyModel>

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::GroupTableModel;
using Romeo::Model::QtModel::GroupSubjectsTableModel;
/*!
 *\file groupview.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-13
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-13 | Bissacco Nicolò |           Romeo::View::Window::GroupView                |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Window {

            /*!
             * \brief The GroupView class represent the page for the manage groups of subjects.
             */
            class GroupView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief modelTable is the model for the table of groups.
                 */
                GroupTableModel *modelTable;
                /*!
                 * \brief modelSubjectsTable is the model for the table of subjects.
                 */
                GroupSubjectsTableModel *modelSubjectsTable;

                    QWidget *topWidget;
                        QWidget *tableWidget;
                            QTableView *groupTable;
                        QGroupBox *groupBox;
                            QTableView *subjectList;
                    NavWidget *bottomWidget;

                /*!
                 * \brief createTop create the top components of the view.
                 */
                void createTop();
                /*!
                 * \brief createBottom create the bottom components of the view.
                 */
                void createBottom();
                /*!
                 * \brief setupTopLayout create the layout of the top of the view.
                 */
                void setupTopLayout();

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
                 * \brief GroupView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                GroupView(QWidget *parent =0);
                /*!
                 * \brief getGroupTable get the groups table.
                 * \return Return a pointer to the groups table.
                 */
                QTableView *getGroupTable() const;
                /*!
                 * \brief getSubjectsTable get the subjects table.
                 * \return Return a pointer to the subjects table.
                 */
                QTableView *getSubjectsTable() const;

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);

            signals:
                /*!
                 * \brief itemSelected signal is emitted when the user select an item from the table.
                 * \param index is the table index of the selection.
                 */
                void itemSelected(const QModelIndex & index);
            };

        } // namespace Window

    } // namespace View

} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_GROUPVIEW_H
