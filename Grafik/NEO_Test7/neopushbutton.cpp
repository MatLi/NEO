#include "neopushbutton.h"

neoPushButton::neoPushButton(DataWidget *main_widget, QWidget *parent) :
    QPushButton(parent)
{
    mainWidget = main_widget;
}

void neoPushButton::mousePressEvent(QMouseEvent *event)
{
    mainWidget->add_edge();
}
