//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include "Room.h"
#include <vector>

class Map
{
 public:
  Map() = default;
  ~Map() = default;

  void changeRooms(int new_ID);
  Room* getCurrentRoom();
  bool generateRooms();

 private:
  std::string needNorthDoor(int x_pos, int y_pos);
  std::string needEastDoor(int x_pos, int y_pos);
  std::string needSouthDoor(int x_pos, int y_pos);
  std::string needWestDoor(int x_pos, int y_pos);
  bool checkRoomName(std::string name, std::string required_doors);

  Room rooms[5][5] = { { Room(), Room(), Room(), Room(), Room() },
                       { Room(), Room(), Room(), Room(), Room() },
                       { Room(), Room(), Room(), Room(), Room() },
                       { Room(), Room(), Room(), Room(), Room() },
                       { Room(), Room(), Room(), Room(), Room() } };
  int current_room;
  int map_size = 5;
};

#endif // PROJECT_MAP_H
