#include "buildingstructure.h"

BuildingStructure::BuildingStructure(QPoint location)
{
    set_location(location);
}
QRectF BuildingStructure::boundingRect() const { return QRectF(0,0, get_width(), get_height()); }
QPainterPath BuildingStructure::shape() const
{
    QPainterPath path;
    //path.addPolygon(get_polygon());
    return path;
}

void BuildingStructure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QBrush b = painter->brush();
    painter->setBrush(Qt::red);
    painter->setPen(Qt::darkRed);
    //painter->drawPolygon(get_polygon());
    painter->setBrush(b);
}
