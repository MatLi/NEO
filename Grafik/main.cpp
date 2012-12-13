/* 
 * FILENAME:      main.cpp
 * PROJEKT:       NEO
 * PROGRAMMERS:   Mari
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Mainfile for the graphics of NEO.
 */

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "graphwidget.h"
#include "datadock.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    MainWindow w;//mainWindow;
    QWidget* qww = dynamic_cast<QWidget*>(&w);
    GraphWidget *widget = new GraphWidget(qww);
    
    w.setCentralWidget(widget);

    w.show();

    return a.exec();
}
