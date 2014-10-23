#include "selectdeselectwidget.h"

using Romeo::View::Component::SelectDeselectWidget;
using Romeo::View::Window::APanel;

SelectDeselectWidget::SelectDeselectWidget(QWidget *parent) : QWidget(parent)
{
    selectAll = new QPushButton("Select All", this);
    deselectAll = new QPushButton("Deselect All", this);

    QHBoxLayout *widgetLayout = new QHBoxLayout(this);
    widgetLayout->setSpacing(-1);
    widgetLayout->setContentsMargins(0, 0, 0, 0);
    widgetLayout->addWidget(selectAll);
    widgetLayout->addWidget(deselectAll);

    APanel *apanel=qobject_cast<APanel*>(parent);
    connect(selectAll, SIGNAL(clicked()), apanel, SIGNAL(selectAll()));
    connect(deselectAll, SIGNAL(clicked()), apanel, SIGNAL(deselectAll()));

    setupObjectsName();
}

void SelectDeselectWidget::setupObjectsName()
{
    setObjectName("SelectDeselectWidget");
    selectAll->setObjectName("selectAll");
    deselectAll->setObjectName("deselectAll");
}
