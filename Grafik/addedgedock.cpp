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

    addEdgeButton = new NeoPushButton(this);
    addEdgeButton->setText("Add edge");
    layout->addWidget(addEdgeButton, 2, 0);

    removeEdgeButton = new NeoPushButton(this);
    removeEdgeButton->setText("Remove edge");
    layout->addWidget(removeEdgeButton, 3, 0);

    //Handle node destruction
    node = new QLineEdit();
    node->setText("Node name");
    layout->addWidget(node, 4, 0);

    removeNodeButton = new NeoPushButton(this);
    removeNodeButton->setText("Remove node");
    layout->addWidget(removeNodeButton, 5, 0);
    
    //Layout
    layout->addWidget(start);
    setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);

    setWindowTitle("Add and remove emove edge + remove node");

    wi->setLayout(layout);
    setWidget(wi);
}

//Ability to change values in a QLineEdit
QString AddEdgeDock::startText()
{
    return start->text();
}

QString AddEdgeDock::endText()
{
    return end->text();
}

QString AddEdgeDock::nodeText()
{
  return node->text();
}
