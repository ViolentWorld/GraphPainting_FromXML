#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge(Node* first, Node* second);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void adjust();
private:
    Node* _from;
    Node* _to;
    QPointF _sourcePoint;
    QPointF _destPoint;
};

#endif // EDGE_H
