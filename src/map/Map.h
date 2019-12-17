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
    Room* getCurrentRoom();
    bool generateRooms();

private:
    std::string needNorthDoor(int x, int y);
    std::string needEastDoor(int x, int y);
    std::string needSouthDoor(int x, int y);
    std::string needWestDoor(int x, int y);
    bool checkRoomName(std::string name, std::string required_doors);


    Room rooms[5][5] = {{Room(), Room(), Room(), Room(), Room()},
                        {Room(), Room(), Room(), Room(), Room()},
                        {Room(), Room(), Room(), Room(), Room()},
                        {Room(), Room(), Room(), Room(), Room()},
                        {Room(), Room(), Room(), Room(), Room()}};
    int current_room;
    int num_initialised_rooms = 0;
};


#endif //PROJECT_MAP_H
