/*
 * Richard Poulson
 * Declarations for EdgeTile class
 *
 * EdgeTiles are the tiles on the very outside of the game board.  They do not
 * have an effect on gameplay at this time.
 */

#ifndef EDGE_TILE_H
#define EDGE_TILE_H

#include "ResourceTile.h"
#include <QColor>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygon>
#include <string>

class EdgeTile : public ResourceTile {

public:
    EdgeTile(const int x_translation, const int y_translation, const int row, const int col, const int number);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
public slots:
};

#endif
