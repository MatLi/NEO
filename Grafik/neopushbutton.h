/*
 * FILENAME:      neopushbutton.h
 * PROJECT:       NEO
 * PROGRAMMER:    Emil
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * NeoPushButton takes care of the pushbuttons in the dock windows.
 */

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
