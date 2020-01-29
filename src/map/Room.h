//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_ROOM_H
#define PROJECT_ROOM_H

#include "../game/Components/AudioManager.h"
#include "../game/SceneObjects/Enemies/AxePsycho.h"
#include "../game/SceneObjects/Enemies/Demon.h"
#include "../game/SceneObjects/Enemies/Ghost.h"
#include "../game/SceneObjects/GameObject.h"
#include "../game/SceneObjects/InteractableObjects.h"
#include "../game/SceneObjects/Item.h"

#include <string>
#include <vector>

class Room : public GameObject
{
 public:
  enum RoomType
  {
    NORMAL,
    ITEM,
    EXIT
  };

  Room() = default;
  Room(int id,
       RoomType room_type,
       bool n_door,
       bool e_door,
       bool s_door,
       bool w_door);
  ~Room();

  bool setup(ASGE::Renderer* renderer, std::string* filename);

  int getId();
  RoomType getType();
  void setType(RoomType room_type);

  bool getNorth();
  bool getEast();
  bool getSouth();
  bool getWest();

  bool canMove();
  void canMove(bool movement);
  bool found();
  void found(bool found);

  void renderObjectsInRoom(ASGE::Renderer* renderer);
  bool updateObjectsInRoom(ASGE::Renderer* renderer,
                           AudioManager* audio,
                           double delta_time,
                           Player* player,
                           int game_width,
                           int game_height);

  void addDemonToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos);
  void addGhostToRoom(ASGE::Renderer* renderer, float x_pos, float y_pos);

  std::vector<InteractableObjects*> getObjectsInRoom();
  std::vector<GameObject*> getEnemies(bool inlcude_objects);
  void checkEnemyHealth();

  void addItemToRoom(ASGE::Renderer* renderer,
                     std::string filename,
                     Item::GameItems item_type,
                     float x_pos,
                     float y_pos);
  void addItemToRoom(Item* new_item);
  void removeItemFromRoom(int item_index);

  bool axeManPresent(AxePsycho* axe_man, int game_width, int game_height);

 private:
  int ID = -1;
  RoomType type = NORMAL;
  bool north = false;
  bool east = false;
  bool south = false;
  bool west = false;
  bool movement_enabled = true;
  bool revealed = false;

  // wise
  std::vector<Demon*> demons;
  std::vector<Ghost*> ghosts;

  // objects in the room
  std::vector<InteractableObjects*> interactable_objs;
  std::vector<Item*> items;
};

#endif // PROJECT_ROOM_H
