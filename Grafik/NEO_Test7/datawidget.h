#ifndef DATAWIDGET_H
#define DATAWIDGET_H


#include <QtGui/QGraphicsView>
#include <QList>
#include "graphwidget.h"

//class GraphicNode;

//! [0]
class DataWidget : public QGraphicsView
{
    Q_OBJECT

public:
    DataWidget(GraphWidget *main_Graph, QWidget *parent = 0);

    //void itemMoved();
    //QList<GraphicNode *> return_nodeList();
    //void addGraphicNode(GraphicNode *new_node);
    void changeTextItem(QString new_text);
    //void newNode(Node *node);

public slots:
   // void shuffle();
    //void zoomIn();
  //  void zoomOut();

protected:
    //void mouseDoubleClickEvent(QMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    //void timerEvent(QTimerEvent *event);
    //void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    //void scaleView(qreal scaleFactor);

private:
    //int timerId;
    //GraphicNode *centerNode;
   // GraphicNode *node10;
    QGraphicsSimpleTextItem *myTextItem;
    GraphWidget *mainGraph;

    //Lista med alla noder i interfacet
    //QList<GraphicNode *> nodeList;
};
//! [0]


#endif // DATAWIDGET_H
