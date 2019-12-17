//
// Created by Zoe on 16/12/2019.
//

#include "Room.h"

Room::Room(int id, std::string filename, int x, int y, bool n, bool e, bool s, bool w)
{
    ID = id;
    north = n;
    east = e;
    south = s;
    west = w;

    // Setup Sprite
    // Load Sprite
    // Set Position

    // Setup Collision
}

int Room::getId()
{
    return ID;
}

bool Room::getNorth()
{
    return north;
}

bool Room::getEast()
{
    return east;
}

bool Room::getSouth()
{
    return south;
}

bool Room::getWest()
{
    return west;
}