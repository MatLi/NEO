/*
 * FILNAMN:          graphwidget.cpp
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * GraphicWidget är rutan i MainWindow som innehåller noder och bågar och hanterar alla händelser.
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

    QString textruta="";
    myTextItem = new QGraphicsSimpleTextItem();
    myTextItem->setText(textruta);
    myTextItem->setPos(100,100);

    scene->addItem(myTextItem);
}

QList<GraphicNode *> GraphWidget::return_nodeList()
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
      if(this->nodeList.at(i)->return_name()==start)
        {
	  startn=this->nodeList.at(i);
        }
    }

  for (int j=0;j<this->nodeList.size();j++)
    {
      if(this->nodeList.at(j)->return_name()==end)
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
      if(this->nodeList.at(i)->return_name()==start)
        {
	  startn=this->nodeList.at(i);
        }
    }

  for (int j=0;j<this->nodeList.size();j++)
    {
      if(this->nodeList.at(j)->return_name()==end)
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

void GraphWidget::removeNode(GraphicNode *rem_node)
{
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

void GraphWidget::clear_network()
{ 
  foreach (GraphicNode *node, nodeList)
    {
      removeNode(node);
    }
}

void GraphWidget::changeTextItem(QString new_text)
{
    myTextItem->setText(new_text);
   // widget_one->changeTextItem(new_text);
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
      case Qt::Key_R:
	{
	  GraphicNode *rem_node = nodeList[0];
	  removeNode(rem_node);
	}
	break;
      case Qt::Key_C:
	{
	  clear_network();
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
