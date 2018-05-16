/*
 * @author: Richard Poulson
 *
 * This was going to be the declaration for a building structure.
 */
#ifndef BUILDINGSTRUCTURE_H
#define BUILDINGSTRUCTURE_H

#include <QColor>
#include <QGraphicsObject>
#include <QPainter>

class BuildingStructure : public QGraphicsObject
{
    Q_OBJECT
private:
    static const int width_ = 20; // width of the structure
    static const int height_ = 20; // height of the structure
    QPoint location_; // where the structure is located on the board
public:
    BuildingStructure(QPoint location);
    static int get_width() { return BuildingStructure::width_; }
    static int get_height() { return BuildingStructure::height_; }
    void set_location(QPoint new_location) { this->location_ = new_location; }
    QPoint get_location() { return this->location_; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
};

#endif // BUILDINGSTRUCTURE_H
