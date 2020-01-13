//
// Created by Zoe on 12/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_SCENE_H
#define THE_SHINING_GAME_GROUP_3_SCENE_H

#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

class Scene
{
 public:
  enum class MenuItem
  {
    NONE = -1
  };

 public:
  Scene() = default;
  ~Scene() = default;

  virtual bool
  init(ASGE::Renderer* renderer, float game_width, float game_height){};
  virtual void render(ASGE::Renderer* renderer){};

 protected:
  bool setupSprite(ASGE::Sprite& sprite,
                   std::string texture,
                   float x_pos,
                   float y_pos,
                   float width,
                   float height);
  bool isInside(ASGE::Sprite* btn, Point2D point);
  virtual void resetOpacity(){};
};

#endif // THE_SHINING_GAME_GROUP_3_SCENE_H
