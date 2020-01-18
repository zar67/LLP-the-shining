//
// Created by Zoe on 16/12/2019.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include "../game/SceneObjects/GameObject.h"
#include "Room.h"
#include <vector>

const int STARTING_ROOM = 12;

class Map
{
 public:
  Map() = default;
  ~Map();

  void setupRoomCollision();
  void handlePlayerCollision(Player* player);
  void handleObjectCollision(std::vector<GameObject*> colliders);
  void fixCollision(GameObject* object,
                    CollisionComponent* collided,
                    CollisionComponent::CollisionSide side);

  bool moveNorth();
  bool moveEast();
  bool moveSouth();
  bool moveWest();

  Room* getRoom(int id);
  Room* getCurrentRoom();
  void renderCurrentRoom(ASGE::Renderer* renderer);
  void updateCurrentRoom(ASGE::Renderer* renderer,
                         double delta_time,
                         Player* player);
  void renderMiniMap(ASGE::Renderer* renderer);
  void generateStartingRoom(ASGE::Renderer* renderer);
  void generateRooms(ASGE::Renderer* renderer, int game_width, int game_height);
  void setupMinimap(ASGE::Renderer* renderer, int game_width, int game_height);

  std::vector<GameObject*> getEnemies();

 private:
  void setupBoundingBox(CollisionComponent* component,
                        float x_pos,
                        float y_pos,
                        float width,
                        float height);
  void checkDoorCollision(Player* player);

  void generateItemRooms();
  void
  generateEnemies(ASGE::Renderer* renderer, int game_width, int game_height);
  void updateMiniMap();
  std::string needNorthDoor(int x_pos, int y_pos);
  std::string needEastDoor(int x_pos, int y_pos);
  std::string needSouthDoor(int x_pos, int y_pos);
  std::string needWestDoor(int x_pos, int y_pos);
  bool checkRoomName(std::string name, std::string required_doors);

  int map_size = 5;
  Room rooms[5][5];
  std::vector<GameObject*> mini_map;
  std::vector<int> mini_map_ids;
  int current_room = STARTING_ROOM;

  CollisionComponent* room_wall_collision[8];
  CollisionComponent* room_door_collision[4];
};

#endif // PROJECT_MAP_H
