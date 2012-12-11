//Mari
#include "datawidget.h"
#include "graphicedge.h"
#include "graphicnode.h"

#include <QtGui>
#include <math.h>

DataWidget::DataWidget(GraphWidget *main_Graph, QWidget *parent)
    : QGraphicsView(parent)//, timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 250, 500);
    setScene(scene);

    //setCacheMode(CacheBackground);
    //setViewportUpdateMode(BoundingRectViewportUpdate);
    //setRenderHint(QPainter::Antialiasing);
    //setTransformationAnchor(AnchorUnderMouse);
    //scale(0.8, qreal(0.8));
    //setMinimumSize(400, 400);
    //setWindowTitle(tr("Elastic Nodes"));

    mainGraph = main_Graph;

    QString textruta="Text111";
    myTextItem = new QGraphicsSimpleTextItem();
    myTextItem->setText(textruta);
    myTextItem->setPos(100,60);

    scene->addItem(myTextItem);

    start = new QLineEdit();
    end = new QLineEdit();

    start->setText(textruta);
    start->setGeometry(100,80,50,30);
    scene->addWidget(start);

    end->setText(textruta);
    end->setGeometry(100,120,50,30);
    scene->addWidget(end);

    add_edge = new QPushButton();
    add_edge->setGeometry(100,160,100,20);
    add_edge->setText("L�gg till b�ge");
    scene->addWidget(add_edge);

}

void DataWidget::changeTextItem(QString new_text)
{
    QString mfirst = "Nodnamn: ";
    myTextItem->setText(mfirst+=new_text);
}

void DataWidget::on_add_edge_clicked()
{
    mainGraph->addEdge(start->text(),end->text());
}

/*void DataWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000/25);
}
*/

//void DataWidget::keyPressEvent(QKeyEvent *event)
//{

  //  switch (event->key()) {
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
   /* case Qt::Key_E:
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
    }*/
//}

/*void DataWidget::timerEvent(QTimerEvent *event)
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


void DataWidget::drawBackground(QPainter *painter, const QRectF &rect)
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

