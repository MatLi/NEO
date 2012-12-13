#include "datadock.h"
#include <QtGui>
#include <QDialog>
#include "neopushbutton.h"

DataDock::DataDock(QWidget *parent) :
    QDockWidget(parent)
{



    QWidget *wi = new QWidget;

    QGridLayout *layout = new QGridLayout();
    //Noddata
    QLabel *name = new QLabel("Node name: ");
    QLabel *price = new QLabel("Node prize: ");
    QLabel *flow = new QLabel("Node flow: ");
    neoPushButton *change = new neoPushButton(this);
    nodeName_ = new QLineEdit();
    nodeFlow_ = new QLineEdit();
    nodePrice_ = new QLineEdit();

    nodePrice_->setReadOnly(true);
    change->setText("Change node data");

    //Bågdata
    QLabel *cost = new QLabel("Egde cost: ");
    QLabel *reducedCost = new QLabel("Reduced cost: ");
    QLabel *edge_flow = new QLabel("Edge flow: ");
    QLabel *max_flow = new QLabel("Max flow: ");
    QLabel *min_flow = new QLabel("Min flow: ");
    neoPushButton *edgechange = new neoPushButton(this);
    edgeCost_ = new QLineEdit();
    edgeReducedCost_ = new QLineEdit();
    edgeFlow_ = new QLineEdit();
    maxFlow_ = new QLineEdit();
    minFlow_ = new QLineEdit();

    edgeReducedCost_->setReadOnly(true);
    edgeFlow_->setReadOnly(true);
    edgechange->setText("Change edge data");


    layout->addWidget(nodeName_,0,1);
    layout->addWidget(nodeFlow_,1,1);
    layout->addWidget(nodePrice_,2,1);
    layout->addWidget(name,0,0);
    layout->addWidget(price,2,0);
    layout->addWidget(flow,1,0);
    layout->addWidget(change,4,0);
    layout->addWidget(cost,5,0);
    layout->addWidget(edgeCost_,5,1);
    layout->addWidget(reducedCost,6,0);
    layout->addWidget(edgeReducedCost_,6,1);
    layout->addWidget(edge_flow,7,0);
    layout->addWidget(edgeFlow_,7,1);
    layout->addWidget(max_flow,8,0);
    layout->addWidget(maxFlow_,8,1);
    layout->addWidget(min_flow,9,0);
    layout->addWidget(minFlow_,9,1);
    layout->addWidget(edgechange,10,0);

    setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);

    setWindowTitle("Nod-/Bågdata");


    wi->setLayout(layout);
    setWidget(wi);
}

void DataDock::editnodeName(QString newName_)
{
  nodeName_->setText(newName_);
}
void DataDock::editnodeFlow(QString newFlow_)
{
  nodeFlow_->setText(newFlow_);
}

void DataDock::editnodePrice(QString newPrice_)
{
  nodePrice_->setText(newPrice_);
}

void DataDock::editedgeCost(QString newCost_)
{
  edgeCost_->setText(newCost_);
}
void DataDock::editedgeReducedCost(QString newReducedCost_)
{
  edgeReducedCost_->setText(newReducedCost_);
}

void DataDock::editedgeminFlow(QString newMinFlow_)
{
  minFlow_->setText(newMinFlow_);
}

void DataDock::editedgemaxFlow(QString newMaxFlow_)
{
  maxFlow_->setText(newMaxFlow_);
}

double DataDock::edgeCost()
{
  return edgeCost_->text().toDouble();
}

double DataDock::edgeminFlow()
{
  return minFlow_->text().toDouble();
}

double DataDock::edgemaxFlow()
{
  return maxFlow_->text().toDouble();
}

double DataDock::nodeFlow()
{
  return nodeFlow_->text().toDouble();
}

std::string DataDock::nodeName()
{
  return nodeName_->text().toUtf8().constData();
}

void DataDock::change_currentnode(GraphicNode* new_current)
{
  current_node=new_current;
}

void DataDock::change_currentedge(GraphicEdge* new_current)
{
  current_edge=new_current;
}

void DataDock::editedgeFlow(QString newFlow)
{
  edgeFlow_->setText(newFlow);
}


GraphicNode* DataDock::return_current_node()
{
  return current_node;
}

GraphicEdge* DataDock::return_current_edge()
{
  return current_edge;
}
