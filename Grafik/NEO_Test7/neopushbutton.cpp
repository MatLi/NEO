#include "neopushbutton.h"
#include "mainwindow.h"
#include "graphwidget.h"

neoPushButton::neoPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void neoPushButton::mousePressEvent(QMouseEvent *event)
{
    if(text()=="Lägg till båge")
    {
        QString start, end;

        MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
        GraphWidget *graph_ = dynamic_cast<GraphWidget *>(mainwindow_->centralWidget());

        start = mainwindow_->return_AddEdgeDock()->start_text();
        end = mainwindow_->return_AddEdgeDock()->end_text();

        graph_->addEdge(start,end);
    }
    else if(text()=="Ta bort båge")
    {
        QString start, end;

        MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
        GraphWidget *graph_ = dynamic_cast<GraphWidget *>(mainwindow_->centralWidget());

        start = mainwindow_->return_AddEdgeDock()->start_text();
        end = mainwindow_->return_AddEdgeDock()->end_text();

        graph_->removeEdge(start,end);
    }
}
