/*
 * Richard Poulson
 * Definitions for the ResourceTile abstract class
 *
 * The other resource tiles extend this class.
 */

#include "ResourceTile.h"

ResourceTile::ResourceTile(const int x_translation, const int y_translation, const int row, const int col, const int number)
{
    this->set_x(x_translation);
    this->set_y(y_translation);
    this->row_ = row;
    this->col_ = col;
    this->number_ = number;
    this->center_ = QPoint(x_translation + (get_width() / 2), y_translation + (get_height() / 2));
    this->image_ = QImage("download.jpeg");
    this->selected_ = false;
    this->polygon_ = QPolygon(6);
    this->polygon_.setPoint(0, x_translation + (get_width() * 1/2), y_translation); // top
    this->polygon_.setPoint(1, x_translation + get_width(), y_translation + (get_height() * 1/4)); // right-top
    this->polygon_.setPoint(2, x_translation + get_width(), y_translation + (get_height() * 3/4)); // right-bottom
    this->polygon_.setPoint(3, x_translation + (get_width() * 1/2), y_translation + get_height()); // right
    this->polygon_.setPoint(4, x_translation, y_translation + (get_height() * 3/4)); // left-bottom
    this->polygon_.setPoint(5, x_translation, y_translation + (get_height() * 1/4)); // left-top

    this->inner_polygon_ = QPolygon(6);
    this->inner_polygon_.setPoint(0, polygon_.point(0) + QPoint(0, get_height() / 4)); // top
    this->inner_polygon_.setPoint(1, polygon_.point(1) + QPoint(- get_width()/4, 0)); // right-top
    this->inner_polygon_.setPoint(2, polygon_.point(2) + QPoint(- get_width()/4, 0)); // right-bottom
    this->inner_polygon_.setPoint(3, polygon_.point(3) + QPoint(0, -get_width()/4)); // bottom
    this->inner_polygon_.setPoint(4, polygon_.point(4) + QPoint(+ get_width()/4, 0)); // left-bottom
    this->inner_polygon_.setPoint(5, polygon_.point(5) + QPoint(+ get_width()/4, 0)); // left-top

    for(int i = 0; i < 4; i++) { this->structures_[i] = Q_NULLPTR; }
}
QRectF ResourceTile::boundingRect() const { return QRectF(x_, y_, width_, height_); }
QPainterPath ResourceTile::shape() const
{
    QPainterPath path;
    path.addPolygon(get_polygon());
    return path;
}

void ResourceTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QBrush b = painter->brush();
    painter->setBrush(Qt::red);
    painter->setPen(Qt::darkRed);
    painter->drawPolygon(get_polygon());
    painter->setBrush(b);
}

void ResourceTile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit TileMousePressed(this);
}
void ResourceTile::ToggleSelected() {
    if(this->selected_ == true) { this->selected_ = false; }
    else { this->selected_ = true; }
    this->update();
}

