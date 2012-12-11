//Mari

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>
#include <QList>

class GraphicNode;

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();
    QList<GraphicNode *> return_nodeList();
    void addGraphicNode(GraphicNode *new_node);
    void changeTextItem(QString new_text);
    //void newNode(Node *node);

public slots:
   // void shuffle();
    //void zoomIn();
  //  void zoomOut();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    //void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    //void scaleView(qreal scaleFactor);

private:
    int timerId;
    GraphicNode *centerNode;
    GraphicNode *node10;
    QGraphicsSimpleTextItem *myTextItem;

    //Lista med alla noder i interfacet
    QList<GraphicNode *> nodeList;
};
//! [0]

#endif
