#ifndef ROMEO_VIEW_WINDOW_DATASETVIEW_H
#define ROMEO_VIEW_WINDOW_DATASETVIEW_H

#include "view/window/apanel.h"
#include "view/component/navwidget.h"
#include <QTableWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <QLabel>
#include "view/window/mainwindow.h"
#include "model/qtModel/datasetstablemodel.h"
#include <QHeaderView>
#include <QSortFilterProxyModel>

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::DatasetsTableModel;
/*!
 *\file analysisdialog.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-13
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-13 | Bissacco Nicolò |           Romeo::View::Window::AnalysisDialog           |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Window {
            /*!
             * \brief The DatasetsView class represent the page for the manage datasets.
             */
            class DatasetsView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief model is the model for the table of datasets.
                 */
                DatasetsTableModel *model;

                    QWidget *topWidget;
                        QWidget *tableWidget;
                            QTableView *datasetsTable;
                        QTabWidget *detailTabWidget;
                            QScrollArea *groupTabScrollArea;
                                QWidget *groupTabWidget;
                                    QLabel *groupInfo;
                            QScrollArea *protocolScrollArea;
                                QWidget *protocolTabWidget;
                                    QLabel *protocolInfo;
                    NavWidget *bottomWidget;

                /*!
                 * \brief createTop method create the objects of the top of the view.
                 */
                void createTop();
                /*!
                 * \brief createBottom method create the objects of the bottom of the view.
                 */
                void createBottom();
                /*!
                 * \brief setupTopLayout method create the layout of the top of the view.
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
                 * \brief DatasetsView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                DatasetsView(QWidget *parent =0);
                /*!
                 * \brief getDatasetTable method return the dataset table.
                 * \return Return a pointer to the dataset table.
                 */
                QTableView *getDatasetTable() const;

                /*!
                 * \brief setGroupInfo set the informations of the group.
                 * \param txt is the string to show.
                 */
                void setGroupInfo(const QString& txt);
                /*!
                 * \brief setProtocolsInfo set the protocols informations.
                 * \param txt is the string to show.
                 */
                void setProtocolsInfo(const QString& txt);

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);

                /*!
                 * \brief resetDatasetInfo method reset the informations boxes.
                 */
                void resetDatasetInfo();

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

#endif // ROMEO_VIEW_WINDOW_DATASETVIEW_H
