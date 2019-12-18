//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

#include "../game/SceneObjects/GameObject.h"
#include <string>

class Room : public GameObject
{
 public:
  Room() = default;
  Room(int id,
       std::string* filename,
       int x_pos,
       int y_pos,
       bool n_door,
       bool e_door,
       bool s_door,
       bool w_door);
  ~Room() = default;

  bool setup(ASGE::Renderer* renderer, std::string* filename);
  int getId();
  bool getNorth();
  bool getEast();
  bool getSouth();
  bool getWest();

 private:
  int ID = -1;
  bool north = false;
  bool east = false;
  bool south = false;
  bool west = false;
};

#endif // PROJECT_ROOM_H
