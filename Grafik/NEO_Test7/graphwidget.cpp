//Mari
#include "graphwidget.h"
#include "graphicedge.h"
#include "graphicnode.h"

#include <QtGui>
#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-340, -340, 680, 680);
    setScene(scene);

    //setCacheMode(CacheBackground);
    //setViewportUpdateMode(BoundingRectViewportUpdate);
    //setRenderHint(QPainter::Antialiasing);
    //setTransformationAnchor(AnchorUnderMouse);
    //scale(0.8, qreal(0.8));
    //setMinimumSize(400, 400);
    //setWindowTitle(tr("Elastic Nodes"));


    GraphicNode *node1 = new GraphicNode(this);
    GraphicNode *node2 = new GraphicNode(this);
    GraphicNode *node3 = new GraphicNode(this);
    GraphicNode *node4 = new GraphicNode(this);
    centerNode = new GraphicNode(this);
    GraphicNode *node6 = new GraphicNode(this);
    GraphicNode *node7 = new GraphicNode(this);
    GraphicNode *node8 = new GraphicNode(this);
    GraphicNode *node9 = new GraphicNode(this);
    node10 = new GraphicNode(this);
    GraphicNode *node14 = new GraphicNode(this);
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(centerNode);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);
    scene->addItem(node9);
    //scene->addItem(node10);
    scene->addItem(new GraphicEdge(node1, node2));
    scene->addItem(new GraphicEdge(node2, node3));
    scene->addItem(new GraphicEdge(node2, centerNode));
    scene->addItem(new GraphicEdge(node3, node6));
    scene->addItem(new GraphicEdge(node4, node1));
    scene->addItem(new GraphicEdge(node4, centerNode));
    scene->addItem(new GraphicEdge(centerNode, node6));
    scene->addItem(new GraphicEdge(centerNode, node8));
    scene->addItem(new GraphicEdge(node6, node9));
    scene->addItem(new GraphicEdge(node7, node4));
    scene->addItem(new GraphicEdge(node8, node7));
    scene->addItem(new GraphicEdge(node9, node8));

    //Lägger till en båge med hjälp av nodeList
    scene->addItem(new GraphicEdge(this->return_nodeList().at(3), this->return_nodeList().at(8)));

    node1->setPos(-50, -50);
    node2->setPos(0, -50);
    node3->setPos(50, -50);
    node4->setPos(-50, 0);
    centerNode->setPos(0, 0);
    node6->setPos(50, 0);
    node7->setPos(-50, 50);
    node8->setPos(0, 50);
    node9->setPos(50, 50);
    node10->setPos(20, 20);
    node14->setPos(10,10);

    QString textruta="Text111";
    myTextItem = new QGraphicsSimpleTextItem();
    myTextItem->setText(textruta);
    myTextItem->setPos(100,100);

    scene->addItem(myTextItem);
}

QList<GraphicNode *> GraphWidget::return_nodeList()
{
    return nodeList;
}

void GraphWidget::addGraphicNode(GraphicNode *new_node)
{
    nodeList << new_node;
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
   // if (!(!scene() || scene()->mouseGrabberItem()))
    //{
    //QPoint p = scene()->mapFromGlobal(QCursor::pos());
    GraphicNode *node234 = new GraphicNode(this);

    //node234->setPos(this->pos());

    node234->setPos((event->x()-400),(event->y()-343));
    scene()->addItem(node234);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    GraphicNode *node = new GraphicNode(this);// node10->newNode();
   // Node *node = new Node(node10->newNode());
    node->setPos(30,-99);
    //Edge *edge = new Edge(node, centerNode);
    QList<GraphicNode *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (GraphicNode *node = qgraphicsitem_cast<GraphicNode *>(item))
            nodes << node;
    }


    switch (event->key()) {
    /*case Qt::Key_Up:
        node10->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        scene()->addItem(node10);
        scene()->addItem(node);
        scene()->addItem(edge);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;*/
    case Qt::Key_E:
        foreach (GraphicNode *node, nodes)
        {
            node->MovabilityF();
        }
        break;
    case Qt::Key_N:
        foreach (GraphicNode *node, nodes)
        {
            node->MovabilityT();
        }
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    //Q_UNUSED(event);

    QList<GraphicNode *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (GraphicNode *node = qgraphicsitem_cast<GraphicNode *>(item))
            nodes << node;
    }

    foreach (GraphicNode *node, nodes)
        node->calculateForces(); //Byt namn :)

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

/*void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}*/


void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    //Q_UNUSED(rect);

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

//#if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_MAEMO_5)
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
//#endif
}


/*void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}*/
//! [7]

/*void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}*/

/*void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}*/
