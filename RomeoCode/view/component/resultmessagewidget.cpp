#include "resultmessagewidget.h"

using Romeo::View::Component::ResultMessageWidget;

ResultMessageWidget::ResultMessageWidget(QWidget *parent) :
    QWidget(parent)
{    
}

ResultMessageWidget::~ResultMessageWidget()
{
    delete message;
}

ResultMessageWidget* ResultMessageWidget::successWidget(const QString& txt, QWidget *parent)
{

    ResultMessageWidget * ret = new ResultMessageWidget(parent);
    ret->setupWidget(txt);
    ret->setObjectName("successWidget");
    return ret;
}

ResultMessageWidget* ResultMessageWidget::errorWidget(const QString& txt, QWidget *parent)
{

    ResultMessageWidget * ret = new ResultMessageWidget(parent);
    ret->setupWidget(txt);
    ret->setObjectName("errorWidget");
    return ret;
}

void ResultMessageWidget::setupWidget(const QString& txt)
{

    message = new QLabel(txt, this);
    message->setObjectName("resultMessage");

    QHBoxLayout *boxLayout = new QHBoxLayout(this);
    boxLayout->setSpacing(-1);
    boxLayout->setContentsMargins(0, 0, 0, 0);
    boxLayout->addWidget(message);

    setMinimumHeight(50);
    setMaximumHeight(50);
}
