#ifndef PLAYER_H
#define PLAYER_H
#include <QLabel>
#include "ResourceTile.h"
#include "buildingstructure.h"

class Player
{
public:
    Player(QString name, int index);
    void set_index(int new_index) { this->index_ = new_index; }
    void set_name(QString new_name) { this->name_ = new_name; }
    void set_stone(int new_stone) { this->stone_ = new_stone; }
    void set_metal(int new_metal) { this->metal_ = new_metal; }
    void set_petroleum(int new_petroleum) { this->petroleum_ = new_petroleum; }
    void set_points(int new_points) { this->points_ = new_points; }
    int get_index() { return this->index_; }
    QString get_name() { return this->name_; }
    int get_stone() { return this->stone_; }
    int get_metal() { return this->metal_; }
    int get_petroleum() { return this->petroleum_; }
    int get_points() { return this->points_; }

    //void StartConstruction(BuildingStructure structure, ResourceTile tile);
    void RequestTrade();
    void EndTurn();
private:
    int index_; // index value of the Player, used to access arrays containing different objects
    QString name_;
    int stone_; // how much stone the Player has
    int metal_; // how much metal the Player has
    int petroleum_; // how much petroleum the Player has
    int points_; // how many points the Player has
};

#endif // PLAYER_H
