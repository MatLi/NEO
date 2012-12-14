#include "neopushbutton.h"
#include "mainwindow.h"
#include "graphwidget.h"
#include "datadock.h"
#include "graphicedge.h"

NeoPushButton::NeoPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void NeoPushButton::mousePressEvent(QMouseEvent *event)
{
    if(text()=="Add edge")
    {
        QString start, end;

        MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
        GraphWidget *graph_ = dynamic_cast<GraphWidget *>(mainwindow_->centralWidget());

        start = mainwindow_->returnAddEdgeDock()->startText();
        end = mainwindow_->returnAddEdgeDock()->endText();

        graph_->addEdge(start,end);
    }
    else if(text()=="Remove edge")
    {
        QString start, end;

        MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
        GraphWidget *graph_ = dynamic_cast<GraphWidget *>(mainwindow_->centralWidget());

        start = mainwindow_->returnAddEdgeDock()->startText();
        end = mainwindow_->returnAddEdgeDock()->endText();

        graph_->removeEdge(start,end);
    }
    else if(text()=="Change node data")
    {

      MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
      DataDock *dataw = dynamic_cast<DataDock*>(mainwindow_->returnDataDock());
      
      dataw->returnCurrentNode()->net_node->change_flow(dataw->nodeFlow());
      dataw->returnCurrentNode()->net_node->change_name(dataw->nodeName());
      QString qstr = QString::fromStdString(dataw->nodeName());
      dataw->returnCurrentNode()->setName(qstr);
    } 
    else if(text()=="Change edge data")
    {
      MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
      DataDock *dataw = dynamic_cast<DataDock*>(mainwindow_->returnDataDock());
      
      dataw->returnCurrentEdge()->net_edge->change_cost(dataw->edgeCost());
      dataw->returnCurrentEdge()->net_edge->change_maxflow(dataw->edgeMaxFlow());
      dataw->returnCurrentEdge()->net_edge->change_minflow(dataw->edgeMinFlow());
    }
    else if(text() == "Remove node")
      {
	QString node;

	MainWindow *mainwindow_ = dynamic_cast<MainWindow *>(window());
	GraphWidget *graph_ = dynamic_cast<GraphWidget *>(mainwindow_->centralWidget());
	
    node = mainwindow_->returnAddEdgeDock()->nodeText();

	graph_->removeNode(node);
	
      }
}
