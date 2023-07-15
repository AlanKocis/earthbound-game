#include "Hero.h"

bool Hero::get_myTurn() const
{
    return myTurn;
}

void Hero::set_myTurn(bool turn)
{
    this->myTurn = turn;
}

Hero::Hero()
{

}