/*
 * FILNAMN:          graphwidget.h
 * PROJEKT:          NEO
 * PROGRAMMERARE:    Mari, Linda, Li och Emil
 *
 * DATUM:            2012-12-11
 *
 * BESKRIVNING:
 * GraphicWidget is the main widget in MainWindow that includes edges and nodes.
 * It handles everything that happens in the window.
*/

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui>
#include <QList>

#include "Network.h"
#include "Node.h"
#include "Edge.h"

class GraphicNode;
class DataWidget;


class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();
    QList<GraphicNode *> return_nodeList();
    void addNode(GraphicNode *new_node);
    void removeNode(QString);
    void changeTextItem(QString new_text);
    void addEdge(QString start, QString end);
    void removeEdge(QString start, QString end);
    void clear_network();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    //void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    int timerId;
    GraphicNode *centerNode;
    QGraphicsSimpleTextItem *myTextItem;

    //List holding all the nodes in the interface
    QList<GraphicNode *> nodeList;
};

#endif //GRAPHWIDGET_H
