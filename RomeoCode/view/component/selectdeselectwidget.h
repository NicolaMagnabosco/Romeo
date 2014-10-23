#ifndef SELECTDESELECTWIDGET_H
#define SELECTDESELECTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "view/window/apanel.h"
/*!
 *\file selectdeselectwidget.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-11
*/
/*
*Changes:
*+----------+------------+-----------------+----------------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                           Changes                        +       Description         |
*+----------+------------+-----------------+----------------------------------------------------------+---------------------------+
*|          |            |                 |                                                          |                           |
*|   0.0.1  | 2013-02-11 | Bissacco Nicolò |      Romeo::View::Component::SelectDeselectWidget        |   First version of class  |
*|          |            |                 |                                                          |                           |
*+----------+------------+-----------------+----------------------------------------------------------+---------------------------+
*/
namespace Romeo {

    namespace View {

        namespace Component {
            /*!
             * \brief The SelectDeselectWidget, extends QWidget, represents the component of the view dedicated to display the buttons and emit the signals to "select/deselect all" from a list.
             */
            class SelectDeselectWidget : public QWidget
            {
                Q_OBJECT
            private:
                /*!
                 * \brief Represent the Select All Button.
                 */
                QPushButton *selectAll;
                /*!
                 * \brief Represent the Deselect All Button.
                 */
                QPushButton *deselectAll;

                /*!
                 * \brief The method add the object name to the Qt object.
                 */
                void setupObjectsName();

            public:
                /*!
                 * \brief Construct a SelectDeselectWidget with the given parent.
                 * \param parent represent the parent of the SelectDeselectWidget object.
                 */
                SelectDeselectWidget(QWidget *parent = 0);

            };

        }
    }
}

#endif // SELECTDESELECTWIDGET_H
