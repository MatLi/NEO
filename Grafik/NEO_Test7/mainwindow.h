//Mari
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "Network.h"
#include "Node.h"
#include "Edge.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void paintEvent (QPaintEvent *event);
    Network *net;

public slots:
    void saveProj();

private:
    Ui::MainWindow *ui;

    void setupMenuBar();
};

#endif // MAINWINDOW_H
