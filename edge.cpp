#include "edge.h"
#include "node.h"

#include <QPainter>

Edge::Edge(Node* first, Node* second)
    : _from(first), _to(second)
{
    _from->addEdge(this);
    _to->addEdge(this);
}

QRectF Edge::boundingRect() const
{
    if (!_from || !_to)
        return QRectF();

    return QRectF(_sourcePoint, _destPoint).normalized();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (!_from || !_to)
        return;

    QLineF line(_sourcePoint, _destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 2.5, Qt::SolidLine));
    painter->drawLine(line);
}

void Edge::adjust()
{    
    QPointF firstTemp = _from->getShape().center();
    QPointF secondTemp = _to->getShape().center();

    firstTemp.setY(firstTemp.y() + 30);
    secondTemp.setY(secondTemp.y() - 30);


    _sourcePoint = firstTemp;
    _destPoint = secondTemp;
}
