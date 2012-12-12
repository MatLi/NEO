//Mari
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "datadock.h"
#include "addedgedock.h"

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
    AddEdgeDock* return_AddEdgeDock();
    DataDock* return_DataDock();

private:
    Ui::MainWindow *ui;

    AddEdgeDock *dock2;
    DataDock *dock;


};

#endif // MAINWINDOW_H
