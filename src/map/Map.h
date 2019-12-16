//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <vector>
#include "Room.h"

class Map
{
public:
    Map() = default;
    ~Map() = default;

    void changeRooms(int new_ID);
    Room getCurrentRoom();

private:
    std::vector<Room> rooms;
    int current_room;
};


#endif //PROJECT_MAP_H
