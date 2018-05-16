/*
 * Richard Poulson
 * Definitions for the EdgeTile class
 */

#include "EdgeTile.h"

EdgeTile::EdgeTile(const int x_translation, const int y_translation, const int row, const int col, const int number) :
    ResourceTile(x_translation, y_translation, row, col, number) {}
void EdgeTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QBrush b = painter->brush();
    painter->setBrush(QColor(192,192,192, 255));
    QPen pen = QPen();
    pen.setWidthF(1.5);
    pen.setColor(QColor(0, 0, 0, 255));
    painter->setPen(pen);
    painter->drawPolygon(get_polygon());
    painter->setBrush(b);
}

