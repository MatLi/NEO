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
#include "datawidget.h"
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
    //GraphicNode *node14 = new GraphicNode(this);
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(centerNode);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);
    scene->addItem(node9);
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
    //node10->setPos(20, 20);
    //node14->setPos(10,10);

    QString textruta="Text111";
    myTextItem = new QGraphicsSimpleTextItem();
    myTextItem->setText(textruta);
    myTextItem->setPos(100,100);

    scene->addItem(myTextItem);

    DataWidget *dwidget = new DataWidget(this);
    widget_one = dwidget;
}

QList<GraphicNode *> GraphWidget::return_nodeList()
{
    return nodeList;
}

void GraphWidget::addEdge(QString start, QString end)
{
    GraphicNode *startn = new GraphicNode(this);;
    GraphicNode *endn = new GraphicNode(this);;
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

    scene()->addItem(new GraphicEdge(startn,endn));
}

void GraphWidget::addGraphicNode(GraphicNode *new_node)
{
    nodeList << new_node;
}

void GraphWidget::changeTextItem(QString new_text)
{
    myTextItem->setText(new_text);
    //widget_one->changeTextItem(new_text);
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000/25);
}

DataWidget* GraphWidget::makeDataWidget()
{
    DataWidget *dwidget = new DataWidget(this);
    widget_one = dwidget;
    return dwidget;
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    GraphicNode *node = new GraphicNode(this);
    node->setPos((event->x()-400),(event->y()-343));
    scene()->addItem(node);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    QList<GraphicNode *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (GraphicNode *node = qgraphicsitem_cast<GraphicNode *>(item))
            nodes << node;
    }
    DataWidget* dwidget;

    switch (event->key()) {
    case Qt::Key_A:
        {
        dwidget = makeDataWidget();
        dwidget->show();
        }
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
