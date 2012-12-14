#ifndef NEOPUSHBUTTON_H
#define NEOPUSHBUTTON_H

#include <QPushButton>
#include <QString>

class NeoPushButton : public QPushButton
{
    Q_OBJECT
public:
   explicit NeoPushButton(QWidget *parent = 0);
    
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    
};

#endif // NEOPUSHBUTTON_H
