#ifndef ROMEO_VIEW_WINDOW_NEWGROUPVIEW_H
#define ROMEO_VIEW_WINDOW_NEWGROUPVIEW_H

#include <view/window/apanel.h>
#include <view/component/navwidget.h>
#include <view/component/selectdeselectwidget.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QTableView>
#include <QDialogButtonBox>
#include <QHeaderView>
#include "view/window/mainwindow.h"
#include "model/qtModel/newgrouptablemodel.h"
#include "model/core/groupofsubject.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Component::SelectDeselectWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::NewGroupTableModel;
using Romeo::Model::Core::GroupOfSubject;

/*!
*\file newgroupview.h
*\author Magnabosco Nicola (nick.magnabosco@gmail.com)
*\date 2013-02-17
*/
/*
*Changes:
*+----------+------------+---------------- +------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                Changes             +       Description         |
*+----------+------------+-----------------+------------------------------------+---------------------------+
*|                                                                                                          |
*|   0.0.1  | 2013-02-17 | Magnabosco Nicola| Romeo::View::Window::NewSubjectView  | First version of class    |
*|                                                                                                          |
*+----------+------------+-----------------+------------------------------------+---------------------------+
*/

namespace Romeo{
    namespace View{
        namespace Window{
        /*!
             * \brief The NewGroupView class is used for creating a new Group
             * of Subject. The user can reach this window by clicking the "Create a new Group"
             * button in the WelcomePageView.
             */
            class NewGroupView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief model is the model for the table of subjects.
                 */
                NewGroupTableModel *model;
                /*!
                 * \brief nSubjects is the number of subjects of the type selected.
                 */
                int nSubjects;

                QWidget *topWidget;
                    QGroupBox *createBox;
                        QWidget *groupName;
                            QLabel *groupLabel;
                            QLineEdit *groupLineEdit;
                        QWidget *groupType;
                            QLabel *typeLabel;
                            QComboBox *comboBoxType;
                        QSpacerItem *verticalSpacer;
                    QGroupBox *listGroup;
                        QTableView *tableView;
                        SelectDeselectWidget *selDeselAllWidget;
                NavWidget *bottomWidget;

                /*!
                 * \brief setupTopLayout create the layout of the top of the view.
                 */
                void setupTopLayout();
                /*!
                 * \brief createTop create the objects of the top of the view.
                 */
                void createTop();
                /*!
                 * \brief createBottom create the objects of the bottom of the view.
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
                 * \brief Class constructor.
                 * \param parent: parent of the NewGroupView object.
                 */
                NewGroupView(QWidget* parent=0);

                /*!
                 * \brief getTableView get the table of subjects.
                 * \return Returna pointer to the table.
                 */
                QTableView *getTableView();
                /*!
                 * \brief updateProxyModel method update the table proxy model
                 * \param model is the new updated proxy model
                 * \return Return a pointer to the updated proxy model of the table.
                 */
                QSortFilterProxyModel *updateProxyModel(NewGroupTableModel *model);
                /*!
                 * \brief getNewGroupTableModel method get the table model
                 * \return Return a pointer to the model
                 */
                NewGroupTableModel *getNewGroupTableModel() const;

                /*!
                 * \brief getName get the name of the group
                 * \return Return a string
                 */
                QString getName() const;
                /*!
                 * \brief getType get the type of the group
                 * \return Return a string
                 */
                QString getType() const;
                /*!
                 * \brief getSelectedSubjects get the selected subjects
                 * \return Return a list with table indexes
                 */
                QModelIndexList getSelectedSubjects() const;
                /*!
                 * \brief resetFields method reset all fields of the view.
                 */
                void resetFields();
                /*!
                 * \brief setNSubjects method set the number of the subjects
                 * \param n is the number of subjects
                 */
                void setNSubjects(int n);
                /*!
                 * \brief setEditFields method set the fields with the data
                 * \param group is a pointer to the edit group
                 */
                void setEditFields(GroupOfSubject* group);

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);

            signals:
                /*!
                 * \brief typeSelection signal is emitted when the user select the type
                 * \param selection is the string of the selection
                 */
                void typeSelection(const QString& selection);
            };
        } // namespace Window
    } // namespace View
} // namespace Romeo
#endif // ROMEO_VIEW_WINDOW_NEWGROUPVIEW_H
