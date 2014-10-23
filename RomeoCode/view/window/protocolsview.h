#ifndef ROMEO_VIEW_WINDOW_PROTOCOLVIEW_H
#define ROMEO_VIEW_WINDOW_PROTOCOLVIEW_H

#include "view/window/apanel.h"
#include "view/component/navwidget.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTableView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHeaderView>
#include "view/window/mainwindow.h"
#include "model/qtModel/protocoltablemodel.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
using Romeo::Model::QtModel::ProtocolTableModel;

/*!
 *\file protocolsview.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-18
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-18 | Bissacco Nicolò |           Romeo::View::Window::ProtocolsView            |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

        namespace View {

            namespace Window {

                /*!
                 * \brief The ProtocolsView class represent the page for the manage protocols.
                 */
                class ProtocolsView : public APanel
                {
                    Q_OBJECT
                private:
                    /*!
                     * \brief model is the model for the table of protocols.
                     */
                    ProtocolTableModel *model;

                        QWidget *topWidget;
                            QWidget *tableWidget;
                                QTableView *tableView;
                            QGroupBox *infoBox;
                                QScrollArea *algorithmInfoScrollArea;
                                    QWidget *algorithmInfoWidget;
                                        QLabel *algorithmInfo;
                                QScrollArea *featureInfoScrollArea;
                                QWidget *featureInfoWidget;
                                    QLabel *featureInfo;
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
                     * \brief ProtocolsView constructor create the view object.
                     * \param parent is the parent of the view object.
                     */
                    ProtocolsView(QWidget* parent=0);
                    /*!
                     * \brief getProtocolsTable get the table of protocols.
                     * \return Return a pointer to the table.
                     */
                    QTableView *getProtocolsTable() const;
                    /*!
                     * \brief getAlgorithmBox get the algorithm information box
                     * \return return a pointer to the box
                     */
                    QScrollArea *getAlgorithmBox() const;
                    /*!
                     * \brief getAlgorithmLabel get the algorithm information label
                     * \return Return a pointer to the label
                     */
                    QLabel *getAlgorithmLabel() const;
                    /*!
                     * \brief getFeatureBox get the feature information box
                     * \return return a pointer to the box
                     */
                    QScrollArea *getFeatureBox() const;
                    /*!
                     * \brief getFeatureLabel get the feature information label
                     * \return Return a pointer to the label
                     */
                    QLabel *getFeatureLabel() const;
                    /*!
                     * \brief resetProtocolInfo method reset the informations boxes
                     */
                    void resetProtocolInfo();

                    /*!
                     * \brief addResultMessageWidget method add the result message, success or error, to the view.
                     * \param txt is the string to show.
                     * \param type true if success, false if error.
                     */
                    virtual void addResultMessageWidget(const QString& txt, bool type);

                signals:
                    /*!
                     * \brief protocolSelected signal is emitted when the user select an item from the table.
                     * \param index is the table index of the selection.
                     */
                    void protocolSelected(const QModelIndex& index);
                };

            } // namespace Window

        } // namespace View

} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_PROTOCOLVIEW_H
