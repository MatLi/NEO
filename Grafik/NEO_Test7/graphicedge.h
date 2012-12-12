/*
 * FILNAMN:          graphicedge.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * GraphicEdge är den grafiska representationen av Edge.
*/
#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include "graphwidget.h"

class GraphicNode;

class GraphicEdge : public QGraphicsItem
{
public:
  GraphicEdge(GraphicNode *sourceNode, GraphicNode *destNode, GraphWidget *graphWidget);

    GraphicNode *sourceNode() const;
    GraphicNode *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    Edge* net_edge;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    GraphicNode *source, *dest;

    GraphWidget *graph;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif // GRAPHICEDGE_H
