/* 
 * FILENAME:      mainwindow.h
 * PROJEKT:       NEO
 * PROGRAMMERS:   Mari, Linda, Li, David och Emil
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Code for the mainwindow menubar.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "Network.h"
#include "Node.h"
#include "Edge.h"
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

    Network *net;

public slots:
    void saveProj();
    void min_cost_flow();
    void max_cost_flow();
    void max_flow();
    void cheapest_tree();
    void cheapest_path();

    AddEdgeDock* return_AddEdgeDock();
    DataDock* return_DataDock();

private:
    Ui::MainWindow *ui;

    void setupMenuBar();

    AddEdgeDock *dock2;
    DataDock *dock;

};

#endif // MAINWINDOW_H
