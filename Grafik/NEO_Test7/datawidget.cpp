/*
 * FILNAMN:          datawidget.cpp
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * Datawidget är ett fönster som kommer fram vid speciella tillfällen.
*/
#include "datawidget.h"
#include "graphicedge.h"
#include "graphicnode.h"
#include "neopushbutton.h"

#include <QtGui>
#include <math.h>

DataWidget::DataWidget(GraphWidget *main_Graph, QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 250, 500);
    setScene(scene);

    mainGraph = main_Graph;



    start = new QLineEdit();
    end = new QLineEdit();

    start->setText("Startnod");
    start->setGeometry(100,80,50,30);
    scene->addWidget(start);

    end->setText("Slutnod");
    end->setGeometry(100,120,50,30);
    scene->addWidget(end);

    add_edge_ = new neoPushButton(this);
    add_edge_->setGeometry(100,160,100,20);
    add_edge_->setText("Lägg till båge");
    scene->addWidget(add_edge_);

    //Nodinfo-ruta
    QString textruta="Nodnamn: ";
    nodeName_ = new QGraphicsSimpleTextItem();
    nodeName_->setText(textruta);
    nodeName_->setPos(100,200);
    scene->addItem(nodeName_);

    nodePrice_ = new QGraphicsSimpleTextItem();
    nodePrice_->setText("Nodpris: ");
    nodePrice_->setPos(100,220);
    scene->addItem(nodePrice_);

    nodeFlow_ = new QGraphicsSimpleTextItem();
    nodeFlow_->setText("Nodflöde: ");
    nodeFlow_->setPos(180,220);
    scene->addItem(nodeFlow_);
}

void DataWidget::changeTextItem(QString new_text)
{
    QString mfirst = "Nodnamn: ";
    nodeName_->setText(mfirst+=new_text);
}


void DataWidget::add_edge()
{
    mainGraph->addEdge(start->text(),end->text());
}

void DataWidget::drawBackground(QPainter *painter, const QRectF &rect)
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
    QString message(tr("Add your edges here"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(11);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);

}
