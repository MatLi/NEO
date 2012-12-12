/*
 * FILNAMN:          graphicnode.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * GraphicNode är den grafiska representationen av Node.
*/
#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QString>

#include "Network.h"
#include "Node.h"
#include "Edge.h"

class GraphicEdge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

//! [0]
class GraphicNode : public QGraphicsItem
{
public:
    GraphicNode(GraphWidget *graphWidget);


    void addEdge(GraphicEdge *edge);
    QList<GraphicEdge *> edges() const;

    QString return_name() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void moveHelper();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    Node* net_node;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<GraphicEdge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    QString name;
};


#endif // GRAPHICNODE_H
