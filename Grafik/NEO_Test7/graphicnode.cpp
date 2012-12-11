//Mari
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QString>

#include "graphicedge.h"
#include "graphicnode.h"
#include "graphwidget.h"

GraphicNode::GraphicNode(GraphWidget *graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    name.setNum(graph->return_nodeList().size());
    graph->addGraphicNode(this);
}

void GraphicNode::addEdge(GraphicEdge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QString GraphicNode::return_name() const
{
    return name;
}

QList<GraphicEdge *> GraphicNode::edges() const
{
    return edgeList;
}

//Is needed too moove the node
void GraphicNode::moveHelper()
{
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos(); //+ QPointF(xvel, yvel);
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

//Cha
void GraphicNode::MovabilityF()
{
    setFlag(ItemIsMovable, false);
}

void GraphicNode::MovabilityT()
{
    setFlag(ItemIsMovable, true);
}
//! [7]

//! [8]
QRectF GraphicNode::boundingRect() const
{
/*#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
    // Add some extra space around the circle for easier touching with finger
    qreal adjust = 30;
    return QRectF( -10 - adjust, -10 - adjust,
                  20 + adjust * 2, 20 + adjust * 2);
#else*/
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust,
                  23 + adjust, 23 + adjust);
//#endif
}

//! [8]

//! [9]
QPainterPath GraphicNode::shape() const
{
    QPainterPath path;

    path.addEllipse(-10, -10, 20, 20);

    return path;
}
//! [9]

//! [10]
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
//! [10]

//! [11]
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
//! [11]

//! [12]
void GraphicNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();

    //Ändrar textrutan i Widget
    graph->changeTextItem(return_name());

    QGraphicsItem::mousePressEvent(event);
}
void GraphicNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

/*void GraphicNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
    Node *node12 = new Node(graph);
    node12->setPos(100,100);
    scene()->addItem(node12);
    Node *node13 = new Node(graph);
    node13->setPos(-100,100);
    scene()->addItem(node13);
    Edge *edge1 = new Edge(node12,node13);
    scene()->addItem(edge1);

    scene()->blockSignals(true);


}*/
//! [12]
