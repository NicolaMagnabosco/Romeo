#ifndef ROMEO_VIEW_WINDOW_NEWDATASETVIEW_H
#define ROMEO_VIEW_WINDOW_NEWDATASETVIEW_H

#include <view/window/apanel.h>
#include <view/component/navwidget.h>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTableView>
#include "view/window/mainwindow.h"
#include "model/qtModel/datasetgrouptablemodel.h"
#include "model/qtModel/datasetprotocoltablemodel.h"
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include "utils.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::DatasetGroupTableModel;
using Romeo::Model::QtModel::DatasetProtocolTableModel;

/*!
*\file newdatasetview.h
*\author Magnabosco Nicola (nick.magnabosco@gmail.com)
*\date 2013-02-17
*/

/*
*Changes:
*+----------+------------+---------------- +------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                Changes             +       Description         |
*+----------+------------+-----------------+------------------------------------+---------------------------+
*|                                                                                                          |
*|   0.0.1  | 2013-02-17 | Magnabosco Nicola| Romeo::View::Window::NewDatasetView  | First version of class    |
*|                                                                                                          |
*+----------+------------+-----------------+------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace  View {

        namespace Window{

            /*!
             * \brief The NewDatasetView class represent the page for the new dataset insertion.
             */
            class NewDatasetView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief modelGroups is the model for the table of subjects.
                 */
                DatasetGroupTableModel *modelGroups;
                /*!
                 * \brief modelProtocols is the model for the table of features.
                 */
                DatasetProtocolTableModel *modelProtocols;

                    QWidget *topWidget;
                        QWidget *nameWidget;
                            QLabel *datasetLabel;
                            QLineEdit *datasetLineEdit;

                    QWidget *centralWidget;
                        QGroupBox *subjectBox;
                            QTableView *subjectTable;
                        QGroupBox *protocolBox;
                            QTableView *protocolTable;
                        QGroupBox *detailsBox;
                            QScrollArea *detailSubjectScrollArea;
                                QWidget *detailSubjectScrollAreaWidget;
                                    QLabel *detailSubject;
                            QScrollArea *detailProtocolScrollArea;
                                QWidget *detailProtocolScrollAreaWidget;
                                    QLabel *detailProtocol;

                    NavWidget *bottomWidget;

                /*!
                 * \brief createTop: initialize every objects conteined into
                 * "topWidget" widget.
                 */
                void createTop();

                /*!
                 * \brief createCenter: initialize every objects conteined into
                 * "centerWidget" widget.
                 */
                void createCenter();

                /*!
                 * \brief createBottom: initialize every objects conteined into
                 * "bottomWidget" widget.
                 */
                void createBottom();

                /*!
                 * \brief setupLayout initialize "mainLayout" and call three methods:
                 * "setupTopLayout", "setupCenterLayout" and "setupBottomLayout" which create respectively
                 * layouts.
                 */
                void setupTopLayout();
                /*!
                 * \brief setupCenterLayout create the layout of the center of the view.
                 */
                void setupCenterLayout();

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
                 * \brief NewDatasetView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                NewDatasetView(QWidget *parent =0);
                /*!
                 * \brief getGroupsTable get the groups table.
                 * \return Return a pointer to the groups table.
                 */
                QTableView *getGroupsTable() const;
                /*!
                 * \brief getProtocolsTable get the protocols table.
                 * \return Return a pointer to the protocols table.
                 */
                QTableView *getProtocolsTable() const;
                /*!
                 * \brief getGroupInfoLabel get the label info of the group.
                 * \return Return a pointer to the group label info.
                 */
                QLabel *getGroupInfoLabel() const;
                /*!
                 * \brief getProtocolInfoLabel get the label info of the protocol.
                 * \return Return a pointer to the protocol label info.
                 */
                QLabel *getProtocolInfoLabel() const;
                /*!
                 * \brief setGroupInfo set the group informations.
                 * \param txt is the string to show.
                 */
                void setGroupInfo(const QString& txt);
                /*!
                 * \brief setProtocolInfo set the protocol informations.
                 * \param txt is the string to show.
                 */
                void setProtocolInfo(const QString& txt);
                /*!
                 * \brief getName get the name of the dataset.
                 * \return Returna string.
                 */
                QString getName() const;
                /*!
                 * \brief getGroupSelected get the selected group.
                 * \return Return a table index.
                 */
                QModelIndex getGroupSelected() const;
                /*!
                 * \brief getProtocolsSelected get the protocols selected.
                 * \return Return a list of table indexes.
                 */
                QModelIndexList getProtocolsSelected() const;
                /*!
                 * \brief resetFields method reset all the view fields.
                 */
                void resetFields();
                /*!
                 * \brief resetInfo method reset the informations boxes.
                 */
                void resetInfo();

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);

                /*!
                 * \brief setEditFields method set the fields with the data
                 * \param dataset is a pointer to the dataset to edit.
                 */
                void setEditFields(Dataset* dataset);

            signals:
                /*!
                 * \brief groupSelected signal is emitted when the user select an item from the table.
                 * \param index is the table index of the selection.
                 */
                void groupSelected(const QModelIndex & index);
                /*!
                 * \brief protocolSelected signal is emitted when the user select an item from the table.
                 * \param index is the table index of the selection.
                 */
                void protocolSelected(const QModelIndex & index);
            };
        } // namespace Window
    } // namespace View
} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_NEWDATASETVIEW_H
