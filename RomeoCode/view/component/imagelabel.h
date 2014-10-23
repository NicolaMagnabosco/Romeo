#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QImage>

/*!
 *\file imagelabel.h
 *\author Bissacco Nicolò (nickbissa@gmail.com)
 *\date 2013-02-10
*/
/*
*Changes:
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|  Version +    Date    +   Programmer    +                       Changes                       +       Description         |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*|          |            |                 |                                                     |                           |
*|   0.0.1  | 2013-02-10 | Bissacco Nicolò |          Romeo::View::Component::ImageLabel         |   First version of class  |
*|          |            |                 |                                                     |                           |
*+----------+------------+-----------------+-----------------------------------------------------+---------------------------+
*/

namespace Romeo
{
    namespace View
    {
        namespace Component
        {
            /*!
             * \brief The class ImageLabel, extends QLabel, represents a label with image.
             */
            class ImageLabel : public QLabel
            {
                Q_OBJECT

            private:
                /*!
                 * \brief Represent the path of the image.
                 */
                QString path;

            protected:
                /*!
                 * \brief This event handler reimplementation receive mouse double click events for the label.
                 * \param event represent the mouse press event.
                 */
                virtual void mouseDoubleClickEvent(QMouseEvent *event);

            public:
                /*!
                 * \brief Construct a ImageLabel with the given parent.
                 * \param pathP represent the path of the image.
                 * \param parent represent the parent of the ImageLabel object.
                 */
                ImageLabel(const QString& pathP, QWidget *parent = 0);

                /*!
                 * \brief This method set the image to the label with the given dimensions.
                 * \param dimension represent the dimensions of the scaled image.
                 */
                void setImage(QImage &image, int dimension);

                /*!
                 * \brief This method set the path of the image.
                 * \param pathP represent the path of the image.
                 */
                void setPath(const QString& pathP);

            signals:
                /*!
                 * \brief This signal is emitted when the label is double clicked.
                 * \param path represent the path of the image of the label.
                 */
                void signalDoubleClicked(const QString& path);
            };
        }
    }
}

#endif // IMAGELABEL_H
