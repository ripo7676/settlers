/*
 * Richard Poulson
 * Declarations for PetroleumTile class
 */

#ifndef PETROLEUM_TILE_H
#define PETROLEUM_TILE_H

#include "ResourceTile.h"
#include <QColor>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygon>
#include <string>

class PetroleumTile : public ResourceTile {

public:
    PetroleumTile(const int x_translation, const int y_translation, const int row, const int col, const int number);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
public slots:
};

#endif
