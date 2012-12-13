#include "addedgedock.h"
#include "datadock.h"
#include <QGridLayout>
#include <QtGui>
#include <QDialog>
#include "neopushbutton.h"

AddEdgeDock::AddEdgeDock(QWidget *parent) :
    QDockWidget(parent)
{

    QWidget *wi = new QWidget;

    QGridLayout *layout = new QGridLayout;

    start = new QLineEdit();
    end = new QLineEdit();

    start->setText("Start node");
    // start->setGeometry(100,80,50,30);
    layout->addWidget(start, 0, 0);

    end->setText("End node");
    // end->setGeometry(100,120,50,30);
    layout->addWidget(end, 1, 0);

    add_edge_ = new neoPushButton(this);
    // add_edge_->setGeometry(100,160,100,20);
    add_edge_->setText("Add edge");
    layout->addWidget(add_edge_, 2, 0);

    remove_edge_ = new neoPushButton(this);
    // remove_edge_->setGeometry(100,200,100,20);
    remove_edge_->setText("Remove edge");
    layout->addWidget(remove_edge_, 3, 0);

    node = new QLineEdit();
    node->setText("Node name");
    layout->addWidget(node, 4, 0);

    remove_node = new neoPushButton(this);
    remove_node->setText("Remove node");
    layout->addWidget(remove_node, 5, 0);

    //Nodinfo-ruta
/*
    QLabel *nodePrice1 = new QLabel("Test");

    layout->addWidget(nodePrice1);

    nodeFlow_ = new QGraphicsSimpleTextItem();
    nodeFlow_->setText("Nodflöde: ");
    nodeFlow_->setPos(180,220);
    layout->addItem(nodeFlow_);
*/

    layout->addWidget(start);
    setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);

    setWindowTitle("Add and remove emove edge + remove node");


    wi->setLayout(layout);
    setWidget(wi);
}

QString AddEdgeDock::start_text()
{
    return start->text();
}

QString AddEdgeDock::end_text()
{
    return end->text();
}

QString AddEdgeDock::node_text()
{
  return node->text();
}
