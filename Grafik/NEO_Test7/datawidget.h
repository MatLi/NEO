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
#include <QLineEdit>
#include <QPushButton>
#include "graphwidget.h"


class DataWidget : public QGraphicsView
{
    Q_OBJECT

public:
    DataWidget(GraphWidget *main_Graph, QWidget *parent = 0);
    void changeTextItem(QString new_text);
    void add_edge();


protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
   // void editLineText(QString *start_node,QString *end_node);

private:
    QGraphicsSimpleTextItem *nodeName_, *nodePrice_, *nodeFlow_;
    GraphWidget *mainGraph;
    QLineEdit *start, *end;
    QPushButton *add_edge_;
    //Lista med alla noder i interfacet
    //QList<GraphicNode *> nodeList;
};

#endif // DATAWIDGET_H
