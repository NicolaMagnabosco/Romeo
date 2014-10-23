#ifndef ROMEO_VIEW_WINDOW_NEWSUBJECTVIEW_H
#define ROMEO_VIEW_WINDOW_NEWSUBJECTVIEW_H

#include <view/window/apanel.h>
#include <view/component/navwidget.h>
#include "view/window/mainwindow.h"
#include <QLineEdit>
#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QtDebug>
#include "utils.h"
#include "view/component/resultmessagewidget.h"

using Romeo::View::Window::APanel;
using Romeo::View::Component::NavWidget;
using Romeo::View::Window::MainWindow;

/*!
*\file newsubjectview.h
*\author Magnabosco Nicola (nick.magnabosco@gmail.com)
*\date 2013-02-17
*/
/*
*Changes:
*+----------+------------+---------------- +---------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                Changes                +       Description         |
*+----------+------------+-----------------+---------------------------------------+---------------------------+
*|                                                                                                             |
*|   0.0.1  | 2013-02-17 | Magnabosco Nicola| Romeo::View::Window::NewSubjectView  | First version of class    |
*|                                                                                                             |
*+----------+------------+-----------------+---------------------------------------+---------------------------+
*/

namespace Romeo {
    namespace View {
        namespace Window {
            /*!
             * \brief The NewSubjectView class is used for creating a new subject.
             * The user of Romeo interacts with this view when he wants to create a new subject.
             */
            class NewSubjectView : public APanel
            {
                Q_OBJECT
            private:
                /*!
                 * \brief String that represent the subject's name.
                 */
                QString subjectName;
                /*!
                 * \brief String that represent the subject's image path.
                 */
                QString subjectImage;
                /*!
                 * \brief String that represent the subject's mask path.
                 *
                 * This mask is an optional parameter.
                 */
                QString subjectMask;

                /*!
                 * \brief typeSelected is the name of the type selected.
                 */
                QString typeSelected;

                QGroupBox *groupBox;
                    QWidget *nameBox;
                        QLabel *subjectLabel;
                        QLineEdit *subjectLineEdit;

                    QWidget *typeBox;
                        QLabel *typeLabel;
                        QComboBox *typeComboBox;

                    QWidget *fileBox;
                        QLabel *fileLabel;
                        QWidget *fileContainer;
                            QLineEdit *imageLineEdit;
                            QPushButton *searchFileButton;

                   QWidget *maskBox;
                        QLabel *maskLabel;
                        QWidget *maskContainer;
                            QLineEdit *maskLineEdit;
                            QPushButton *searchMaskButton;

                NavWidget *bottomWidget;

                /*!
                 * \brief createTop create the objects of the top of the view.
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
                 * \brief Class Constructor.
                 * \param parent represent the parent of NewSubjectView object.
                 */
                NewSubjectView(QWidget* parent=0);
                /*!
                 * \brief Change the name of the subject.
                 * \param name represent the new subject's name.
                 */
                void setSubjectName(const QString& name);
                /*!
                 * \brief Change the path of the subject's image.
                 * \param path represent the new subject's image path.
                 */
                void setImagePath(const QString& path);
                /*!
                 * \brief Change the path of the subject's mask.
                 * \param path represent the new subject's mask path.
                 */
                void setMaskPath(const QString& path);

                /*!
                 * \brief setTypeSelection set the selection of the combobox type
                 * \param type is the string to select
                 */
                void setTypeSelection(const QString& type);

                /*!
                 * \brief Returns the subject's name.
                 * \return a QString containing the subject's actual name.
                 */
                QString getSubjectName() const;
                /*!
                 * \brief Returns the subject's image path.
                 * \return a QString containing the subject's actual image path.
                 */
                QString getImagePath() const;
                /*!
                 * \brief Returns the subject's mask path.
                 * \return a QString containing the subject's actual mask path.
                 */
                QString getMaskPath() const;

                /*!
                 * \brief getTypeSelected get the type selected
                 * \return Return a string of the selection
                 */
                QString getTypeSelected() const;

                /*!
                 * \brief resetFields method reset all fields of the view
                 */
                void resetFields();

                /*!
                 * \brief enableSearchFile set enable the search folder
                 */
                void enableSearchFile();
                /*!
                 * \brief disableSearchFile set disable the search folder
                 */
                void disableSearchFile();

                /*!
                 * \brief addResultMessageWidget method add the result message, success or error, to the view.
                 * \param txt is the string to show.
                 * \param type true if success, false if error.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);

            signals:
                /*!
                 * \brief This signal is emitted by the view when the user decides to search the subject's image.
                 */
                void addImage();
                /*!
                 * \brief This signal is emitted by the view when the user decides to search the subject's mask.
                 */
                void addMask();
                /*!
                 * \brief This signal is emitted by the view  when the user decides to save the subject.
                 */
                void saveSubject();
                /*!
                 * \brief This signal is emitted by the view when the user change the  subject's name.
                 * \param text represent the new subjet's name assigned by the user.
                 */
                void nameTextChanged(const QString& text);
                /*!
                 * \brief This signal is emitted by the view when the user change the subject's image paht.
                 * \param text represent the new subject's image path assigned by the user.
                 */
                void imageTextChanged(const QString& text);
                /*!
                 * \brief This signal is emitted by the view when the user change the subject's mask path.
                 * \param text repsent the new subject's mask path assigned by the user.
                 */
                void maskTextChanged(const QString& text);

                /*!
                 * \brief typeSelectionChanged signal is emitted when the type selection change
                 * \param selection is the string of the selection
                 */
                void typeSelectionChanged(const QString& selection);                
            };

        } // namespace Window

    } // namespace View

} // namespace Romeo

#endif // ROMEO_VIEW_WINDOW_NEWSUBJECTVIEW_H
