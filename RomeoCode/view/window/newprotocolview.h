#ifndef ROMEO_VIEW_WINDOW_NEWPROTOCOLVIEW_H
#define ROMEO_VIEW_WINDOW_NEWPROTOCOLVIEW_H

#include <view/window/apanel.h>
#include <view/component/navwidget.h>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include "view/window/mainwindow.h"
#include "utils.h"
#include "model/qtModel/newprotocolfeaturetablemodel.h"
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include "model/core/protocol.h"
#include "model/core/feature/afeature.h"
#include "model/core/algcreator.h"
#include "model/core/algorithm/aalgorithm.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::NewProtocolFeatureTableModel;
using Romeo::Model::Core::Protocol;
using Romeo::Model::Core::Algorithm::AAlgorithm;

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
namespace Romeo {
    namespace View {
        namespace Window {
            /*!
             * \brief The NewProtocolView class represent the page for the new protocol insertion.
             */
            class NewProtocolView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief model is the model for the table of features.
                 */
                NewProtocolFeatureTableModel *model;

                /*!
                 * \brief algorithmsFieldsList is a vector with the algorithms fields pointers.
                 */
                QVector<QWidget*> algorithmsFieldsList;

                    QWidget *topWidget;
                        QGroupBox *infoBox;
                            QWidget *infoWidget;
                                QWidget *nameWidget;
                                    QLabel *nameLabel;
                                    QLineEdit *nameLineEdit;
                                QWidget *typeWidget;
                                    QLabel *typeLabel;
                                    QComboBox *typeComboBox;
                            QSpacerItem *infoSpacer;
                        QGroupBox *featureBox;
                            QTableView *featureList;
                            QWidget *featButtonBox;
                                QPushButton *featureAdd;
                                QPushButton *featureRemoveBtn;
                        QGroupBox *algorithmBox;
                            QComboBox *algorithmComboBox;
                            QWidget *parametersWidget;
                            QSpacerItem *algorithmSpacer;
                    NavWidget *bottomWidget;

                /*!
                 * \brief createTop create the objects of the top of the view.
                 */
                void createTop();
                /*!
                 * \brief createLeft create the objects of the left of the view.
                 */
                void createLeft();
                /*!
                 * \brief createCenter create the objects of the center of the view.
                 */
                void createCenter();
                /*!
                 * \brief createRight create the objects of the right of the view.
                 */
                void createRight();
                /*!
                 * \brief createBottom create the objects of the bottom of the view.
                 */
                void createBottom();

                /*!
                 * \brief setupTopLayout create the layout of the top of the view.
                 */
                void setupTopLayout();

                /*!
                 * \brief setAlgorithmsComboBox set the list of algorithms combobox.
                 */
                void setAlgorithmsComboBox();

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
                 * \brief NewProtocolView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                NewProtocolView(QWidget *parent =0);
                /*!
                 * \brief getTypeSelected get the type selected
                 * \return Return the string of the selection
                 */
                QString getTypeSelected() const;
                /*!
                 * \brief getAlgorithmSelected get the algorithm selected
                 * \return Return the string of the selection
                 */
                QString getAlgorithmSelected() const;
                /*!
                 * \brief getProtocolName get the name of the protocol inserted
                 * \return  Return the string of the name
                 */
                QString getProtocolName() const;
                /*!
                 * \brief getFeaturesTable get the feature table
                 * \return Return a pointer to the table
                 */
                QTableView *getFeaturesTable() const;
                /*!
                 * \brief resetFields method reset all the view fields
                 */
                void resetFields();

                /*!
                 * \brief setEditFields set the fields of the view with the data
                 * \param protocol is the protocol to edit
                 */
                void setEditFields(Protocol* protocol);

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);
                /*!
                 * \brief getSelectedFeatures get the feature selected
                 * \return Return a list of table indexes
                 */
                QModelIndexList getSelectedFeatures() const;

                /*!
                 * \brief enableRemoveFeatureButton set the feature remove button enable or disable
                 * \param enable true if enable, false if disable
                 */
                void enableRemoveFeatureButton(const bool enable);

                /*!
                 * \brief setAlgorithmFields set the fields of algorithm parameters
                 * \param alg is the algorithm
                 */
                void setAlgorithmFields(AAlgorithm *alg);
                /*!
                 * \brief removeAlgorithmFields method remove the fields of algorithm parameters
                 */
                void removeAlgorithmFields();

                /*!
                 * \brief getAlgorithmParameters get the parameters of the algorithm
                 * \param alg is the algorithm
                 * \return Return a string list of the parameters
                 */
                QStringList getAlgorithmParameters(AAlgorithm * alg) const;

            signals:
                /*!
                 * \brief addFeatureClicked signals is emitted when the add feature button is clicked
                 */
                void addFeatureClicked();
                /*!
                 * \brief typeChange signals is emitted when type selection change
                 * \param selection is the string of the selection
                 */
                void typeChange(const QString& selection);

                /*!
                 * \brief featureRemove signals is emitted when the feature remove button is clicked
                 */
                void featureRemove();
                /*!
                 * \brief featureSelect signal is emitted when the user select an item from the table.
                 * \param index is the table index of the selection.
                 */
                void featureSelect(const QModelIndex& index);

                /*!
                 * \brief algorithmSelect signals is emitted when the algorithm is selected
                 * \param selection is the string of the selection
                 */
                void algorithmSelect(const QString& selection);
            };
        } // namespace Window
    } // namespace View
} // namespace Romeo


#endif // ROMEO_VIEW_WINDOW_NEWPROTOCOLVIEW_H
