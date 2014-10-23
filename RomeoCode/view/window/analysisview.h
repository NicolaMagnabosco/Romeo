#ifndef ROMEO_VIEW_WINDOW_ANALYSISVIEW_H
#define ROMEO_VIEW_WINDOW_ANALYSISVIEW_H

#include <view/window/apanel.h>
#include <view/component/navwidget.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include "view/window/mainwindow.h"
#include "utils.h"
#include "model/util/dao/datasetdao.h"
#include "model/qtModel/analysissubjectstablemodel.h"
#include <QHeaderView>
#include "model/qtModel/analysisprotocolstablemodel.h"
#include "view/component/selectdeselectwidget.h"
#include "model/core/analysis.h"
#include <QItemSelectionModel>

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::AnalysisSubjectsTableModel;
using Romeo::Model::QtModel::AnalysisProtocolsTableModel;
using Romeo::View::Component::SelectDeselectWidget;
using Romeo::Model::Core::Analysis;

/*!
*\file newgroupview.h
*\author Magnabosco Nicola (nick.magnabosco@gmail.com)
*\date 2013-02-17
*/

/*
*Changes:
*+----------+------------+------------------+------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer     +                Changes             +       Description         |
*+----------+------------+------------------+------------------------------------+---------------------------+
*|                                                                                                          |
*|   0.0.1  | 2013-02-17 | Magnabosco Nicola| Romeo::View::Window::NewSubjectView  | First version of class    |
*|                                                                                                          |
*+----------+------------+------------------+------------------------------------+---------------------------+
*/

namespace Romeo {

    namespace View {

        namespace Window {

            /*!
             * \brief The AnalysisView class represent the page for the start analysis.
             */
            class AnalysisView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief subjectTableModel is the model for the table of subjects.
                 */
                AnalysisSubjectsTableModel *subjectTableModel;
                /*!
                 * \brief protocolsTableModel is the model for the table of protocols.
                 */
                AnalysisProtocolsTableModel *protocolsTableModel;
                /*!
                 * \brief noDatasets is the flag represent if there are dataset or not.
                 */
                bool noDatasets;

                    QWidget *topWidget;
                        QWidget *leftWidget;
                            QWidget *datasetBox;
                                QLabel *datasetSelect;
                                SelectDeselectWidget * selDesel;
                                QComboBox *datasetComboBox;
                            QGroupBox *subjectsBox;
                                QTableView *subjectListView;
                        QWidget *rightWidget;
                            QGroupBox *buttonBox;
                                QPushButton *saverButton;
                                QPushButton *viewerButton;
                            QWidget *selectorBox;
                                QTableView *selectorList;
                            QWidget *pathWidget;
                                QGroupBox *pathBox;
                                    QLineEdit *lineEdit;
                                    QPushButton *searchButton;
                    NavWidget *bottomWidget;

                /*!
                 * \brief setupTopLayout method create the layout of the top of the view.
                 */
                void setupTopLayout();
                /*!
                 * \brief setupLeftLayout method create the layout of the left of the view.
                 */
                void setupLeftLayout();
                /*!
                 * \brief setupRightLayout method create the layout of the right of the view.
                 */
                void setupRightLayout();
                /*!
                 * \brief createTop method create the objects of the top of the view.
                 */
                void createTop();
                /*!
                 * \brief createLeft method create the objects of the left of the view.
                 */
                void createLeft();
                /*!
                 * \brief createRight method create the objects of the right of the view.
                 */
                void createRight();
                /*!
                 * \brief createBottom method create the objects of the bottom of the view.
                 */
                void createBottom();
                /*!
                 * \brief setDatasetComboBox method set the list of dataset combobox.
                 */
                void setDatasetComboBox();
                /*!
                 * \brief checkDatasets method test if there are dataset to show or not.
                 */
                void checkDatasets();

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
                 * \brief AnalysisView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                AnalysisView(QWidget *parent =0);
                /*!
                 * \brief getSubjectsTable get the subjects table object.
                 * \return Return a pointer to the table.
                 */
                QTableView *getSubjectsTable() const;
                /*!
                 * \brief getSubjectsSelected get the subjects selected in the table.
                 * \return Return a list of indexes.
                 */
                QModelIndexList getSubjectsSelected() const;
                /*!
                 * \brief getProtocolsTable get the subjects table object.
                 * \return Return a pointer to the table.
                 */
                QTableView *getProtocolsTable() const;
                /*!
                 * \brief getDestinationFolder get the destination folder selected.
                 * \return Return a string with the path.
                 */
                QString getDestinationFolder() const;
                /*!
                 * \brief setDestinationFolder set the destination folder field.
                 * \param folder is the path string.
                 */
                void setDestinationFolder(const QString& folder);

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);

                /*!
                 * \brief resetView method reset all the fields of the view.
                 */
                void resetView();

                /*!
                 * \brief setRestartData method set the view with the restart data->
                 * \param analysis is the analysis to restart.
                 */
                void setRestartData(Analysis *analysis);

            signals:
                /*!
                 * \brief datasetSelected signal is emitted when a dataset is selected.
                 * \param dataset is the name of the dataset selected.
                 */
                void datasetSelected(const QString& dataset);
                /*!
                 * \brief selectDestinationDirectory signal is emitted when the user click on search folder button.
                 */
                void selectDestinationDirectory();
                /*!
                 * \brief featureSelected signal is emitted when a feature is selected.
                 * \param index is the table index of the selected feature.
                 */
                void featureSelected(const QModelIndex & index);
                /*!
                 * \brief saveAllSignal signal is emitted when the user click on save/not save all button.
                 */
                void saveAllSignal();
                /*!
                 * \brief showAllSignal signal is emitted when the user clock on show/not show all button.
                 */
                void showAllSignal();
            };

        } // namespace Window

    } // namespace View

} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_ANALYSISVIEW_H
