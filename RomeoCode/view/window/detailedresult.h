#ifndef ROMEO_VIEW_WINDOW_DETAILEDRESULT_H
#define ROMEO_VIEW_WINDOW_DETAILEDRESULT_H

#include "view/window/apanel.h"
#include "view/component/navwidget.h"
#include <QTreeView>
#include <QScrollArea>
#include <QWidget>
#include "view/window/mainwindow.h"
#include <QFileSystemModel>
#include "utils.h"
#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>
#include "view/component/imagelabel.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;
/*!
 *\file detailedresault.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-13
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-13 | Bissacco Nicolò |           Romeo::View::Window::DetailedResult           |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Window {

            /*!
             * \brief The DetailedResult class represent the page for the detailed analysis results.
             */
            class DetailedResult : public APanel
            {
                Q_OBJECT

            private:
                /*!
                 * \brief modelTree is the model for the tree of analysis results.
                 */
                QFileSystemModel *modelTree;

                QLabel *title;
                QWidget *topWidget;
                    QTreeView *treeView;
                    QScrollArea *scrollArea;
                        QWidget *scrollAreaWidgetContents;
                NavWidget *bottomWidget;

                /*!
                 * \brief imageWidgetLit is the vector with image widget pointers.
                 */
                QVector<QWidget*> imageWidgetLit;

                /*!
                 * \brief createTop create the top components of the view.
                 */
                void createTop();
                /*!
                 * \brief createBottom create the bottom components of the view.
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
                 * \brief DetailedResult constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                DetailedResult(QWidget *parent =0);
                /*!
                 * \brief setTreePath set the tree path to show.
                 * \param path is the string of the path.
                 */
                void setTreePath(const QString& path);
                /*!
                 * \brief getModelTree get the model of the tree.
                 * \return Return a pointer of the tree model.
                 */
                QFileSystemModel *getModelTree();
                /*!
                 * \brief generateImages method generate the images of the path.
                 * \param path is the string of the path.
                 */
                void generateImages(const QString& path);
                /*!
                 * \brief setpageTitle method set the title on the top of the page.
                 * \param txt is the string to show.
                 */
                void setpageTitle(const QString& txt);

            signals:
                /*!
                 * \brief treeClicked signal is emitted when the user select an item from the tree.
                 * \param item is the tree index of the selection.
                 */
                void treeClicked(const QModelIndex& item);
                /*!
                 * \brief ImageDoubleClicked signal is emitted when the user double click on the image.
                 * \param path is the string path of the image.
                 */
                void ImageDoubleClicked(const QString& path);
            };

        } // namespace Window
    } // namespace View
} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_DETAILEDRESULT_H
