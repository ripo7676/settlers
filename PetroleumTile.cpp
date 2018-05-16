/*
 * Richard Poulson
 * Definitions for the PetroleumTile class
 */

#include "PetroleumTile.h"

PetroleumTile::PetroleumTile(const int x_translation, const int y_translation, const int row, const int col, const int number) :
    ResourceTile(x_translation, y_translation, row, col, number) {}
void PetroleumTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QBrush b = painter->brush();
    painter->setBrush(QColor(64, 64, 64, 255));
    QPen pen = QPen();
    pen.setWidthF(1.5);
    if(this->isSelected()) { pen.setColor(QColor(0, 255, 255, 255)); }
    else { pen.setColor(QColor(0, 0, 0, 255)); }
    painter->setPen(pen);
    painter->drawPolygon(get_polygon());
    painter->setBrush(QColor(200, 200, 200, 220));
    painter->setPen(QColor(0, 0, 0, 200));
    painter->drawEllipse(get_center(), (get_height() / 5), (get_height() / 5));
    painter->drawText(get_center(), get_num_string());
    painter->setBrush(b);
}

