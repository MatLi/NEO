/*
 * FILNAMN:          datawidget.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * Datawidget är ett fönster som kommer fram vid speciella tillfällen.
*/
#ifndef DATAWIDGET_H
#define DATAWIDGET_H


#include <QtGui/QGraphicsView>
#include <QList>
#include "graphwidget.h"


class DataWidget : public QGraphicsView
{
    Q_OBJECT

public:
    DataWidget(GraphWidget *main_Graph, QWidget *parent = 0);
    void changeTextItem(QString new_text);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QGraphicsSimpleTextItem *myTextItem;
    GraphWidget *mainGraph;
};

#endif // DATAWIDGET_H
