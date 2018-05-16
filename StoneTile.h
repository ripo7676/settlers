/*
 * Richard Poulson
 * Declarations for the StoneTile class
 */

#ifndef STONE_TILE_H
#define STONE_TILE_H

#include "ResourceTile.h"
#include <QColor>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygon>
#include <string>

class StoneTile : public ResourceTile {

public:
    StoneTile(const int x_translation, const int y_translation, const int row, const int col, const int number);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
public slots:
};

#endif
