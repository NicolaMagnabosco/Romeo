#ifndef APANEL_H
#define APANEL_H

#include <QWidget>
#include <QPushButton>
#include <QFile>
#include <QApplication>
#include <QStringListModel>
#include <QLabel>
#include <QHBoxLayout>
#include "view/component/resultmessagewidget.h"

using Romeo::View::Component::ResultMessageWidget;

/*!
*\file apanel.h
*\author Adami Alberto (albertoa.adami.7@gmail.com)
*\date 2013-02-13
*/
/*
*Changes:
*+----------+------------+---------------- +--------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +         Changes                +       Description         |
*+----------+------------+-----------------+--------------------------------+---------------------------+
*|                                                                                                      |
*|   0.0.1  | 2013-02-13 |   Adami Alberto |  Romeo::View::Window::Apanel   | First version of class    |
*|   0.0.2  | 2013-02-28 |   Adami Alberto |  Romeo::View::Window::APanel   | Complete the docuemtation |
*|                                                                                                      |
*+----------+------------+-----------------+--------------------------------+---------------------------+
*/
namespace Romeo
{
    namespace View
    {
        namespace Window
        {
            /*!
             * \brief The APanel class is the base class of the Romeos'view.
             * It's an abstract class and contains all the basic methods and signals inherited by the subclasses of Apanel.
             *
             * For subclasses the APanel class the developer have to implement the following method:
             * -loadCss(): this method have the goal to load the css code;
             * -setUpObjectName(): this method have the goal to set all the objectname using in css;
             * -setUpToolTip():
             * -adConnect(): this method create all the connections for the view;
             * -setUpView(): this method setup the view.
             */
            class APanel : public QWidget
            {
                Q_OBJECT
            protected:
                /*!
                 * \brief True if toolbar is show in the view, false if toolbar is hide in the view.
                 */
                bool showToolbar;

                /*!
                 * \brief resultMessageWidget is a pointer to the component that show to the user the result message of an user action.
                 */
                ResultMessageWidget *resultMessageWidget;

                /*!
                 * \brief Construct an APanel's object with the given parent.
                 * This class is abstract and so it's not possible to instanate an object of Apanel's class, but only an APenl's
                 * subclass.
                 * \param parent rappresents the parent of the APanel's object created.
                 */
                APanel(QWidget *parent= 0);

                /*!
                 * \brief Load the css of the class.
                 * All subclasses of Apanel class have to implement this method.
                 */
                virtual void loadCss() =0;
                /*!
                 * \brief Setup the object name  of all objects used in css code.
                 * All subclasses of Apanel class have to implement this method.
                 */
                virtual void setupObjectName() =0;
                /*!
                 * \brief setupToolTip
                 */
                virtual void setupToolTip() =0;
                /*!
                 * \brief Create all the connections for the view.
                 * All subclasses of Apanel class have to implement this method.
                 */
                virtual void addConnect() const =0;
                /*!
                 * \brief Set up the view.
                 * All subclasses of Apenal class have to implement this method.
                 */
                virtual void setupView() =0;

                /*!
                 * \brief Set up the layout of view.
                 * All subclasses of Apenal class have to implement this method.
                 */
                virtual void setupLayout() =0;

                /*!
                 * \brief This method have the goal to initialize the view.
                 */
                void initializeView();

                /*!
                 * \brief This method return a string list of types.
                 * \param parent represent the parent of the list object.
                 * \return Returns a DialogCode result. a pointer to the string list.
                 */
                static QStringListModel * getTypeRomeo(QObject *parent = 0);                

                /*!
                 * \brief This method create an informative label show to the user near the input fields.
                 * \param txt represent the text show to the user.
                 * \param parent represent the parent of the label object.
                 * \return Return a pointer to the created label.
                 */
                QLabel *labelInfo(const QString& txt, QWidget * parent = 0) const;
                /*!
                 * \brief This method create a label to show to the user an empty list.
                 * \param txt represent the text show to the user.
                 * \param parent represent the parent of the label object.
                 * \return Return a pointer to the created label.
                 */
                QLabel *labelEmpty(const QString& txt, QWidget *parent = 0) const;

                /*!
                 * \brief The method set if toolbar is shown or not in the view based on show parameter.
                 * \param show true set toolbar visible, false set toolbar hide.
                 */
                void setShowToolbar(bool show);

            public:
                /*!
                 * \brief Destroy the object.
                 * All this APanel's children are deleted first. After the APanel class'll be destroyed.
                */
                virtual ~APanel();

                /*!
                 * \brief This method add the result message to the view with the given parameters.
                 * \param txt represent the text show to the user.
                 * \param type: true if success message, false if error message.
                 */
                virtual void addResultMessageWidget(const QString& txt, bool type);
                /*!
                 * \brief This method delete the result message widget.
                 */
                void removeResultMessageWidget();
                /*!
                 * \brief This method return a pointer to the ResultMessageWidget.
                 */
                ResultMessageWidget *getResultMessageWidget() const;

                /*!
                 * \brief The method return if toolbar is shown or not in the view.
                 * return Return true if toolbar is visible, false if toolbar is hide.
                 */
                bool isShowToolbar() const;

            signals:
                /*!
                 * \brief Signal emitted when the user decidet to return at the previous view.
                 */
                void backView();
                /*!
                 * \brief Signal emitted when the user decided to save the changes at the current view.
                 */
                void saveObject();

                /*!
                 * \brief Signal emitted when the user decided to edit the current object
                 */
                void editObject();

                /*!
                 * \brief Signal emitted when the user decided to delete the current object
                 */
                void deleteObject();

                /*!
                 * \brief Signal emitted when the user decided to start the analysis
                 */
                void startAnalysis();

                /*!
                 * \brief Signal emitted when a user click on select all button
                 */
                void selectAll();

                /*!
                 * \brief Signal emitted when a user click on deselect all button
                 */
                void deselectAll();

                /*!
                 * \brief Signal emitted when a user click on restart analysis button
                 */
                void restartAnalysis();

                /*!
                 * \brief Signal emitted when a user click on export analysis results button
                 */
                void exportSignal();

                /*!
                 * \brief Signal emitted when a user click on show analysis results button
                 */
                void showAnalysisResults();
            };

        }

    }

}

#endif // APANEL_H
