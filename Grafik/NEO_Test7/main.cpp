
//Mari

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "graphwidget.h"
#include "datawidget.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    MainWindow w;//mainWindow;
    QWidget* qww = dynamic_cast<QWidget*>(&w);
    GraphWidget *widget = new GraphWidget(qww);
    
    w.setCentralWidget(widget);

    //w.net->min_cost_flow();

    w.show();

    return a.exec();
}
