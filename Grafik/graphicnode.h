/*
 * FILNAMN:          graphicnode.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda, Li och Emil
 *
 * DATUM:            2012-12-12
 *
 * BESKRIVNING:
 * GraphicNode is the graphic representation of Node
*/
#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QString>
#include "graphicedge.h"

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

    ~GraphicNode();

    void addEdge(GraphicEdge *edge);
    void removeEdge(GraphicEdge *edge);
    QList<GraphicEdge *> edges() const;

    QString return_name() const;
    void set_name(QString new_name);

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void moveHelper();
    bool advance();
    GraphicEdge* getEdge(GraphicNode *end_node);

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
