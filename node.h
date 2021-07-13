#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QGraphicsItem>
#include <QList>
#include <QFile>
#include <QDomDocument>

#include "edge.h"

class Node: public QGraphicsItem
{
public:
    Node();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QRectF getShape() const;
    void setShape(const QRectF& form);

    QList <Node*> getChildrien() const;
    void addChild(Node* node);

    QList <Edge*> getEdges() const;
    void addEdge(Edge* edge);

    int getY_coord() const;
    void setY_coord(const int& y_coord);

    int getOffset() const;
    void setOffset(const int& offset);

    void setText(const QString& text);

private:
    QList <Node*> _childrien;
    QList <Edge*> _edges;
    QString _text = "";
    QRectF shape;

    int _y_coord = 100;
    int _offset = 0;
};

#endif // NODE_H
