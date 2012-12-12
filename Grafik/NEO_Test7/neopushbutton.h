#ifndef NEOPUSHBUTTON_H
#define NEOPUSHBUTTON_H

#include <QPushButton>
#include <QString>
#include "datawidget.h"

class neoPushButton : public QPushButton
{
    Q_OBJECT
public:
   explicit neoPushButton(QWidget *parent = 0);
    
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    
};

#endif // NEOPUSHBUTTON_H
