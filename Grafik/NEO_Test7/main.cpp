
//Mari

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "graphwidget.h"
#include "datawidget.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    GraphWidget *widget = new GraphWidget;
    //DataWidget *dwidget = new DataWidget;

    MainWindow w;//mainWindow;
    w.setCentralWidget(widget);

    //dwidget->show();

    w.show();

    return a.exec();
}
