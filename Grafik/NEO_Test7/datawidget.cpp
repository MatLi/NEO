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
    add_edge->setText("Lägg till båge");
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
