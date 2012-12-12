#include "datadock.h"
#include <QtGui>
#include <QDialog>
#include "neopushbutton.h"

DataDock::DataDock(QWidget *parent) :
    QDockWidget(parent)
{



    QWidget *wi = new QWidget;

    QGridLayout *layout = new QGridLayout();

    QLabel *name = new QLabel("Nodnamn: ");
    QLabel *price = new QLabel("Nodpris: ");
    QLabel *flow = new QLabel("Nodflöde: ");
    neoPushButton *change = new neoPushButton(this);
    nodeName_ = new QLineEdit();
    nodeFlow_ = new QLineEdit();
    nodePrice_ = new QLineEdit();

    nodePrice_->setReadOnly(true);
    change->setText("Ändra noddata");

    layout->addWidget(nodeName_,0,1);
    layout->addWidget(nodeFlow_,1,1);
    layout->addWidget(nodePrice_,2,1);
    layout->addWidget(name,0,0);
    layout->addWidget(price,2,0);
    layout->addWidget(flow,1,0);
    layout->addWidget(change,4,0);
    

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

GraphicNode* DataDock::return_current_node()
{
  return current_node;
}
