//
// Created by Owner on 17/12/2019.
//

#ifndef PROJECT_SPRITECOMPONENT_H
#define PROJECT_SPRITECOMPONENT_H

#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <string>

class SpriteComponent
{
 public:
  SpriteComponent() = default;
  ~SpriteComponent();

  bool loadSpriteComponent(ASGE::Renderer* renderer,
                           const std::string& texture_location);
  ASGE::Sprite* getSprite();

 private:
  ASGE::Sprite* sprite = nullptr;
};

#endif // PROJECT_SPRITECOMPONENT_H
