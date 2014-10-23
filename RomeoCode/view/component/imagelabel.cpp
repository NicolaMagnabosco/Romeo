#include "imagelabel.h"

using Romeo::View::Component::ImageLabel;

ImageLabel::ImageLabel(const QString& pathP, QWidget *parent) :
    QLabel(parent), path(pathP)
{
}

void ImageLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!path.isEmpty()) {
        emit signalDoubleClicked(path);
    }
}

void ImageLabel::setImage(QImage &image, int dimension)
{
    setPixmap(QPixmap::fromImage(image.scaledToWidth(dimension)));
}

void ImageLabel::setPath(const QString& pathP)
{
    path = pathP;
}
