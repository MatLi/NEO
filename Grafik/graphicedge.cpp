/*
 * FILNAMN:          graphicedge.cpp
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda, Li och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * GraphicEdge is the graphical representation of Edge.
*/
#include <QPainter>

#include "graphicedge.h"
#include "graphicnode.h"
#include "graphwidget.h"
#include "mainwindow.h"
#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include <QGraphicsSceneMouseEvent>

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

GraphicEdge::GraphicEdge(GraphicNode *sourceNode, GraphicNode *destNode, GraphWidget *graphWidget)
  : arrowSize(10),
    net_edge(new Edge(sourceNode->net_node, destNode->net_node)),
    graph(graphWidget)
{
  source = sourceNode;
  dest = destNode;
  source->addEdge(this);
  dest->addEdge(this);
  adjust();
  MainWindow* mw = dynamic_cast<MainWindow*>(graph->parent());
  mw->net->add_edge(net_edge);
}

GraphicEdge::~GraphicEdge()
{
  MainWindow* mw = dynamic_cast<MainWindow*>(graph->parent());
  mw->net->remove_edge(net_edge);

  sourceNode()->removeEdge(this);
  destNode()->removeEdge(this);
}

void GraphicEdge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  update();

  QString edge_flow_, edge_cost, edge_reducedCost, min_flow,max_flow;
  
  MainWindow *mwindow = dynamic_cast<MainWindow*>(graph->parent());
  DataDock *ddock = dynamic_cast<DataDock*>(mwindow->return_DataDock());
  
  ddock->change_currentedge(this);
  edge_flow_.setNum(net_edge->flow());
  edge_cost.setNum(net_edge->cost());
  edge_reducedCost.setNum(net_edge->reduced_cost());
  max_flow.setNum(net_edge->maxflow());
  min_flow.setNum(net_edge->minflow());
  
  ddock->editedgeCost(edge_cost);
  ddock->editedgeminFlow(min_flow);
  ddock->editedgemaxFlow(max_flow);
  ddock->editedgeReducedCost(edge_reducedCost);
  ddock->editedgeFlow(edge_flow_);
  QGraphicsItem::mousePressEvent(event);
}

GraphicNode *GraphicEdge::sourceNode() const
{
    return source;
}

GraphicNode *GraphicEdge::destNode() const
{
    return dest;
}

void GraphicEdge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF GraphicEdge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


void GraphicEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                              cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                              cos(angle - Pi + Pi / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

