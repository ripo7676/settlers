#include "player.h"

Player::Player(QString name, int index)
{
    set_index(index);
    set_name(name);
    set_stone(100);
    set_metal(0);
    set_petroleum(0);
    set_points(0);
}
void Player::RequestTrade()
{

}
void Player::EndTurn()
{

}
