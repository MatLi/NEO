#include "neopushbutton.h"
#include "mainwindow.h"

neoPushButton::neoPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void neoPushButton::mousePressEvent(QMouseEvent *event)
{
    QString start, end;

    MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
    GraphWidget *graph_ = dynamic_cast<GraphWidget *>(mainwindow_->centralWidget());

    start = mainwindow_->return_AddEdgeDock()->start_text();
    end = mainwindow_->return_AddEdgeDock()->end_text();

    graph_->addEdge(start,end);
}
