/* 
 * FILENAME:      addedgedock.cpp
 * PROJEKT:       NEO
 * PROGRAMMERS:   Emil, Mari, Li och Linda
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * Creating the dock to the right in the window where you 
 * can add/remove edges and remove nodes.
 */

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

    //Handle edge creation and destruction
    start = new QLineEdit();
    end = new QLineEdit();

    start->setText("Start node");
    layout->addWidget(start, 0, 0);

    end->setText("End node");
    layout->addWidget(end, 1, 0);

    add_edge_ = new neoPushButton(this);
    add_edge_->setText("Add edge");
    layout->addWidget(add_edge_, 2, 0);

    remove_edge_ = new neoPushButton(this);
    remove_edge_->setText("Remove edge");
    layout->addWidget(remove_edge_, 3, 0);

    //Handle node destruction
    node = new QLineEdit();
    node->setText("Node name");
    layout->addWidget(node, 4, 0);

    remove_node = new neoPushButton(this);
    remove_node->setText("Remove node");
    layout->addWidget(remove_node, 5, 0);
    
    //Layout
    layout->addWidget(start);
    setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);

    setWindowTitle("Add and remove emove edge + remove node");

    wi->setLayout(layout);
    setWidget(wi);
}

//Ability to change values in a QLineEdit
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
