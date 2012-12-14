/*
 * FILNAMN:          graphicnode.cpp
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda, Li och Emil
 *
 * DATUM:            2012-12-12
 *
 * BESKRIVNING:
 * GraphicNode is the graphic representation of Node
*/
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QString>

#include "graphicedge.h"
#include "graphicnode.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include "mainwindow.h"
#include "datadock.h"

GraphicNode::GraphicNode(GraphWidget *graphWidget)
  : graph(graphWidget),
    net_node(new Node)
{
    setFlag(ItemIsMovable);
    //setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    name.setNum(graph->returnNodeList().size());
    graph->addNode(this);
}

GraphicNode::~GraphicNode()
{
  MainWindow* mw = dynamic_cast<MainWindow*>(graph->parent());
  mw->net->remove_node(net_node);
}

void GraphicNode::addEdge(GraphicEdge *edge)
{
    edgeList << edge;
    edge->adjust();
}

void GraphicNode::removeEdge(GraphicEdge *edge)
{
  edgeList.removeOne(edge);
 }

QString GraphicNode::returnName() const
{
    return name;
}

void GraphicNode::setName(QString new_name)
{
  name = new_name;
}

QList<GraphicEdge *> GraphicNode::edges() const
{
    return edgeList;
}

void GraphicNode::moveHelper()
{
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos();
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

bool GraphicNode::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF GraphicNode::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust,
                  23 + adjust, 23 + adjust);
}

QPainterPath GraphicNode::shape() const
{
    QPainterPath path;

    path.addEllipse(-10, -10, 20, 20);

    return path;
}

void GraphicNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant GraphicNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (GraphicEdge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();

    QString node_flow_, node_price;

    //Changes the textbox in Widget
    graph->changeTextItem(returnName());
    
    MainWindow *mwindow = dynamic_cast<MainWindow*>(graph->parent());
    DataDock *ddock = dynamic_cast<DataDock*>(mwindow->returnDataDock());

    ddock->changeCurrentNode(this);
    node_flow_.setNum(net_node->flow());
    node_price.setNum(net_node->node_price());

    ddock->editNodeName(returnName());
    ddock->editNodeFlow(node_flow_);
    ddock->editNodePrice(node_price);

    QGraphicsItem::mousePressEvent(event);
}
void GraphicNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

GraphicEdge* GraphicNode::getEdge(GraphicNode *end_node)
{
  GraphicEdge *edge;
  for (int i=0; i < this->edgeList.size(); i++)
    {
      if(edgeList.at(i)->destNode() == end_node)
	{
	  edge = this->edgeList.at(i);
	  return edge;
	}
    }
}


