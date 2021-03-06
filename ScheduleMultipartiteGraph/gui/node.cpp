#include "edge.h"
#include "node.h"
#include "graphwidget.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
Node::Node(GraphWidget *graphWidget, double size, QColor color)
    :graph(graphWidget),size(size),color(color)
{
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}


QRectF Node::boundingRect() const
{
    //Прямоугольникая граница , окрушающая фигуру

    qreal adjust = 2;
    return QRectF( -size/2 - adjust, -size/2 - adjust, size+ 3 + adjust, size + 3 + adjust); //to do сделать масштабируемость
}

QPainterPath Node::shape() const
{
    //хитбокс, если не переписывать эту функцию ,то она даст boundingRect
    QPainterPath path;
    path.addEllipse(-size/2, -size/2, size, size);
    return path;
}


void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    // Эллипс
    painter->setPen(QPen(Qt::black, 0));
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-size/2, -size/2, size, size);

}

QVariant  Node::itemChange(GraphicsItemChange change, const QVariant &value){
   // qDebug()<<change;
    switch (change) {
    case ItemPositionHasChanged: //если изменилась позиция , то все ребра перемещаются
        foreach (Edge *edge, edgeList) {

            edge->adjust();
        }
        break;
    case ItemVisibleHasChanged:

        foreach (Edge *edge, edgeList) {
            changeEdgeVisibility(edge);
        }
        break;
    default:
        break;
    }
    update();
    return QGraphicsItem::itemChange(change, value);
}
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Для демонстрации. При нажатии мышкой на вершину она "прячется" вместе с ребрами
    this->hide();
    qDebug()<<this->pos();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
// Если хотя бы 1 вершина стпрятана , то  необходимо спрятать ребро
void Node::changeEdgeVisibility(Edge *edge)
{
    edge->changeEdgeVisibility();
}

