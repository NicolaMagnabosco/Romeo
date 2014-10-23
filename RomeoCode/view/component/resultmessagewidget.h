#ifndef RESULTMESSAGEWIDGET_H
#define RESULTMESSAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QHBoxLayout>
/*!
 *\file resultmessagewidget.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-11
*/
/*
*Changes:
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                       +       Description         |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*|          |            |                 |                                                         |                           |
*|   0.0.1  | 2013-02-11 | Bissacco Nicolò |       Romeo::View::Component::ResultMessageWidget       |   First version of class  |
*|          |            |                 |                                                         |                           |
*+----------+------------+-----------------+---------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Component {
            /*!
             * \brief The class ResultMessageWidget, extends QWidget, represents the component of the view that displays a success message or an error message with a predefined style.
             */
            class ResultMessageWidget : public QWidget
            {
            private:
                /*!
                 * \brief Represent the label for the message text.
                 */
                QLabel *message;

                /*!
                 * \brief Construct a ResultMessageWidget with the given parent.
                 * \param parent represent the parent of the ResultMessageWidget object.
                 */
                ResultMessageWidget(QWidget *parent = 0);

                /*!
                 * \brief The method setup the component and the layout of the widget.
                 * \param txt represent the string that will appear in the widget.
                 */
                void setupWidget(const QString& txt);

            public:
                /*!
                 * \brief The method create the success ResultMessageWidget with the given text and parent.
                 * \param txt represent the string that will appear in the widget.
                 * \param parent represent the parent of the ResultMessageWidget object.
                 * \return Return the pointer to the created widget.
                 */
                static ResultMessageWidget* successWidget(const QString& txt, QWidget *parent = 0);
                /*!
                 * \brief The method create the error ResultMessageWidget with the given text and parent.
                 * \param txt represent the string that will appear in the widget.
                 * \param parent represent the parent of the ResultMessageWidget object.
                 * \return Return the pointer to the created widget.
                 */
                static ResultMessageWidget* errorWidget(const QString& txt, QWidget *parent = 0);

                /*!
                 * \brief Destroy the label of the ResultMessageWidget.
                */
                ~ResultMessageWidget();

            };
        }
    }
}

#endif // RESULTMESSAGEWIDGET_H
