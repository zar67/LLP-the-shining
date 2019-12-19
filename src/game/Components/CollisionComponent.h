//
// Created by Owner on 17/12/2019.
//

#ifndef PROJECT_COLLISIONCOMPONENT_H
#define PROJECT_COLLISIONCOMPONENT_H

class CollisionComponent
{
 public:
  CollisionComponent() = default;

  bool hasCollided(const CollisionComponent& collided);

  void updateBoundingBox(const float rect[4]);

  void setIsTrigger(bool value);
  bool getIsTrigger();

  void const getBoundingBox(float (&out_rect)[4]) const;

 private:
  bool is_trigger = false;

  static const int BOX_SIZE = 4;
  float bounding_box[BOX_SIZE]; // x,y,width,height
};

#endif // PROJECT_COLLISIONCOMPONENT_H
