
//Mari

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "graphwidget.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    GraphWidget *widget = new GraphWidget;

    MainWindow w;//mainWindow;
    w.setCentralWidget(widget);


    w.show();
    
    return a.exec();
}
