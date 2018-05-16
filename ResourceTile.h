/*
 * Richard Poulson
 * Declarations for the ResourceTile abstract class
 */

#ifndef RESOURCE_TILE_H
#define RESOURCE_TILE_H

#include <QColor>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygon>
#include <string>
#include <stdio.h>
#include <iostream>
#include "buildingstructure.h"

class ResourceTile : public QGraphicsObject {
    Q_OBJECT

private:
    static const int width_ = 100;
    static const int height_ = 80;
    int x_; // x-coordinate
    int y_; // y-coordinate
    int row_; // which row the tile is in.
    int col_; // which column the tile is in.
    int number_; // number associated with the tile.  used to determine if tile yields additional resources
    QPoint center_; // the center point of the tile.  used to draw shapes within the tile.
    bool selected_; // indicates whether or not the tile is currently selected.
    QPolygon inner_polygon_;
    QPolygon polygon_; // the polygon representing the shape/outline of the tile.
    QImage image_; // image to be painted on top of the tile.  Illustrates what type of tile it is.
    BuildingStructure * structures_[4];
public:
    static int get_width() { return ResourceTile::width_; }
    static int get_height() { return ResourceTile::height_; }
    ResourceTile(const int x_translation, const int y_translation, const int row, const int col, const int number);
    void set_x(int new_x) { this->x_ = new_x; }
    void set_y(int new_y) { this->y_ = new_y; }
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_row() const { return this->row_; }
    int get_col() const { return this->col_; }
    QString get_num_string() { return QString::number(this->number_); } // returns a QString that represents the tile's number.
    QPoint get_center() const { return this->center_; } // returns the center QPoint of the tile.
    QPolygon get_polygon() const { return this->polygon_; }
    bool isSelected() const { return this->selected_; } // is the tile currently selected?
    void ToggleSelected(); // toggle the value of the selected_ attribute.

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void TileMousePressed(ResourceTile * tile);
public slots:
};

#endif // RESOURCE_TILE_H
