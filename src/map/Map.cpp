//
// Created by Zoe on 16/12/2019.
//

#include "Map.h"

void Map::changeRooms(int new_ID)
{
    current_room = new_ID;
}

Room Map::getCurrentRoom()
{
    for (auto room : rooms)
    {
        if (room.getId() == current_room)
        {
            return room;
        }
    }

    return Room();
}
