/*
 * FILENAME:         graphwidget.cpp
 * PROJECT:          NEO
 * PROGRAMMERS:      Mari, Linda, Li och Emil
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * GraphicWidget is the main widget in MainWindow that includes edges and nodes.
 * It handles everything that happens in the window.
*/
#include "graphwidget.h"
#include "datadock.h"
#include "graphicedge.h"
#include "graphicnode.h"
#include "mainwindow.h"

#include <QtGui>
#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(parent->normalGeometry());
    setScene(scene);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    QString textbox="";
    myTextItem = new QGraphicsSimpleTextItem();
    myTextItem->setText(textbox);
    myTextItem->setPos(100,100);

    scene->addItem(myTextItem);
}

QList<GraphicNode *> GraphWidget::returnNodeList()
{
    return nodeList;
}

void GraphWidget::removeEdge(QString start, QString end)
{ 
  GraphicNode *startn = nullptr;
  GraphicNode *endn = nullptr;
  GraphicEdge *edge = nullptr;
  QList<GraphicEdge *> edges_;

  for (int i=0; i < this->nodeList.size(); i++)
    {
      if(this->nodeList.at(i)->returnName()==start)
        {
	  startn=this->nodeList.at(i);
        }
    }

  for (int j=0;j<this->nodeList.size();j++)
    {
      if(this->nodeList.at(j)->returnName()==end)
        {
	  endn=this->nodeList.at(j);
        }
    }

  edge = startn->getEdge(endn);

  scene()->removeItem(edge);

  delete edge;
}

void GraphWidget::addEdge(QString start, QString end)
{
  GraphicNode *startn = nullptr;
  GraphicNode *endn = nullptr;
  for (int i=0;i<this->nodeList.size();i++)
    {
      if(this->nodeList.at(i)->returnName()==start)
        {
	  startn=this->nodeList.at(i);
        }
    }

  for (int j=0;j<this->nodeList.size();j++)
    {
      if(this->nodeList.at(j)->returnName()==end)
        {
	  endn=this->nodeList.at(j);
        }
    }

  scene()->addItem(new GraphicEdge(startn,endn,this));
}

void GraphWidget::addNode(GraphicNode *new_node)
{
    nodeList << new_node;
    MainWindow* w = dynamic_cast<MainWindow*>(parent());
    w->net->add_node(new_node->net_node);
}

void GraphWidget::removeNode(QString rem_node_name)
{

  GraphicNode* rem_node; 

  for (int i=0;i<this->nodeList.size();i++)
    {
      if(this->nodeList.at(i)->returnName()==rem_node_name)
        {
	  rem_node=this->nodeList.at(i);
        }
    }

  scene()->removeItem(rem_node);

  QList<GraphicEdge *> edges_;
  edges_ = rem_node->edges();

  foreach (GraphicEdge *edge, edges_)
    {
      scene()->removeItem(edge);
      delete edge;
    }
  delete rem_node;
  
}

void GraphWidget::clearNetwork()
{ 
  foreach (GraphicNode *node, nodeList)
    {
      removeNode(node->returnName());
    }
}

void GraphWidget::changeTextItem(QString new_text)
{
    myTextItem->setText(new_text);
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000/25);
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    GraphicNode *node = new GraphicNode(this);
    QPointF eventPos = mapToScene(event->pos());
    node->setPos(eventPos);
    scene()->addItem(node);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{   
    switch (event->key()) 
      {
      case Qt::Key_C:
	{
      clearNetwork();
	}
	break;
      default:
        QGraphicsView::keyPressEvent(event);
      }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    QList<GraphicNode *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (GraphicNode *node = qgraphicsitem_cast<GraphicNode *>(item))
            nodes << node;
    }

    foreach (GraphicNode *node, nodes)
        node->moveHelper();

    bool itemsMoved = false;
    foreach (GraphicNode *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
    painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
    painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersect(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Hi and welcome to NEO! If this is your first time or if you need help click on the Help-button"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(11);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}
