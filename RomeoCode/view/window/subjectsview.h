#ifndef SUBJECTSVIEW_H
#define SUBJECTSVIEW_H

#include "view/window/apanel.h"
#include "view/component/navwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QGroupBox>
#include <QScrollArea>
#include <QLabel>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include "view/window/mainwindow.h"
#include "model/qtModel/subjecttablemodel.h"
#include <QImage>
#include "view/component/imagelabel.h"

using Romeo::View::Window::APanel;
using Romeo::View::Window::MainWindow;
using Romeo::View::Component::NavWidget;
using Romeo::Model::QtModel::SubjectTableModel;
using Romeo::View::Component::ImageLabel;
/*!
 *\file analysisdialog.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-19
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-19 | Bissacco Nicolò |           Romeo::View::Window::SubjectsView             |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo
{
    namespace View
    {
        namespace Window
        {
            /*!
             * \brief The SubjectsView class represent the page for the manage subjects.
             */
            class SubjectsView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief model is the model for the table of subjects.
                 */
                SubjectTableModel *model;

                    QWidget *topWidget;
                        QWidget *tableWidget;
                            QTableView *tableView;
                        QGroupBox *infoBox;
                            QScrollArea *imgScrollArea;
                                QWidget *imgContainer;
                                    QWidget *imgWidget;
                                        ImageLabel *subjectImg;
                                    QWidget *maskWidget;
                                        ImageLabel *subjectMask;
                            QScrollArea *infoScrollArea;
                                QWidget *infoWidget;
                                    QLabel *infoTxt;
                    NavWidget *bottomWidget;

                /*!
                 * \brief createTop method create the objects of the top of the view.
                 */
                void createTop();
                /*!
                 * \brief setupTable method create the subjects table.
                 */
                void setupTable();
                /*!
                 * \brief setupInfoBlock method create the subjects info blocks.
                 */
                void setupInfoBlock();
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
                 * \brief SubjectsView constructor create the view object.
                 * \param parent is the parent of the view object.
                 */
                SubjectsView(QWidget *parent= 0);
                /*!
                 * \brief getTableView get the table view
                 * \return Return a pointer to the table
                 */
                QTableView *getTableView() const;
                /*!
                 * \brief setSubjectImgs method set the images of the subjects
                 * \param image is the image of the subject
                 * \param mask is the mask of the subject
                 * \param pathI is the path of the image
                 * \param pathM is the path of the mask
                 */
                void setSubjectImgs(const QImage& image, const QImage& mask, const QString& pathI, const QString& pathM);
                /*!
                 * \brief setSubjectInfo method set the subject informations
                 * \param txt is the string to show
                 */
                void setSubjectInfo(const QString& txt);

            signals:
                /*!
                 * \brief itemSelected signal is emitted when the user select an item from the table.
                 * \param index is the table index of the selection.
                 */
                void itemSelected(const QModelIndex & index);
                /*!
                 * \brief ImageDoubleClicked signal is emitted when the user double click on the subject image
                 * \param path is the path of the image
                 */
                void ImageDoubleClicked(const QString& path);
                /*!
                 * \brief MaskDoubleClicked signal is emitted when the user double click on the subject mask
                 * \param path is the path of the image
                 */
                void MaskDoubleClicked(const QString& path);
            };
        }
    }
}

#endif // SUBJECTSVIEW_H
