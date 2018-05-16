/*
 * Richard Poulson
 * Declarations for MetalTile class
 */

#ifndef METAL_TILE_H
#define METAL_TILE_H

#include "ResourceTile.h"
#include <QColor>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygon>
#include <string>

class MetalTile : public ResourceTile {

public:
    MetalTile(const int x_translation, const int y_translation, const int row, const int col, const int number);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
public slots:
};

#endif
