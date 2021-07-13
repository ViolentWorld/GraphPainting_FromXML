#include "node.h"

#include <QPainter>

Node::Node()
{
}

QRectF Node::boundingRect() const
{
    return shape;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::black, 2.5, Qt::SolidLine));
    painter->drawEllipse(shape);

    QFont font = painter->font();
    font.setBold(true);
    font.setFamily("Arial");
    painter->setFont(font);
    painter->drawText(shape, Qt::AlignCenter, _text);
}

QRectF Node::getShape() const
{
    return shape;
}

void Node::setShape(const QRectF& form)
{
    shape = form;
}

QList <Node*> Node::getChildrien() const
{
    return _childrien;
}

void Node::addChild(Node* node)
{
    _childrien.append(node);
    node->setY_coord(_y_coord + 100);
}

QList<Edge *> Node::getEdges() const
{
    return _edges;
}

void Node::addEdge(Edge *edge)
{
    _edges.append(edge);
    edge->adjust();
}

int Node::getY_coord() const
{
    return _y_coord;
}

void Node::setY_coord(const int& y_coord)
{
    _y_coord = y_coord;
}

int Node::getOffset() const
{
    return _offset;
}

void Node::setOffset(const int& offset)
{
    _offset = offset;
}

void Node::setText(const QString& text)
{
    _text = text;
}
