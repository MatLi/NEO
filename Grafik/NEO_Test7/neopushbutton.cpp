#include "neopushbutton.h"
#include "mainwindow.h"
#include "graphwidget.h"
#include "datadock.h"
#include "graphicedge.h"

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
    else if(text()=="Ändra noddata")
    {

      MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
      DataDock *dataw = dynamic_cast<DataDock*>(mainwindow_->return_DataDock());
      
      dataw->return_current_node()->net_node->change_flow(dataw->nodeFlow());
      dataw->return_current_node()->net_node->change_name(dataw->nodeName());
    } 
    else if(text()=="Ändra bågdata")
    {
      MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
      DataDock *dataw = dynamic_cast<DataDock*>(mainwindow_->return_DataDock());
      
      dataw->return_current_edge()->net_edge->change_cost(dataw->edgeCost());
      dataw->return_current_edge()->net_edge->change_maxflow(dataw->edgemaxFlow());
      dataw->return_current_edge()->net_edge->change_minflow(dataw->edgeminFlow());
    }
}
