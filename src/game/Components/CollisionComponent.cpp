//
// Created by Owner on 17/12/2019.
//

#include "CollisionComponent.h"

#include <iostream>
#include <string>
/*
 * pass in the objects colliderc_componenet so you can check collision status
 */
bool CollisionComponent::hasCollided(const CollisionComponent& collided)
{
  float collided_box[4];
  collided.getBoundingBox(collided_box);

  std::string s = std::to_string(collided_box[0]) + " (bullet) " +
                  std::to_string(collided_box[1]) + " : " +
                  std::to_string(collided_box[2]) + " (bullet) " +
                  std::to_string(collided_box[3]);
  std::string t = std::to_string(bounding_box[0]) + " (enemy) " +
                  std::to_string(bounding_box[1]) + " : " +
                  std::to_string(bounding_box[2]) + " (enemy) " +
                  std::to_string(bounding_box[3]);

  if ((bounding_box[0] >= collided_box[0] &&
         bounding_box[0] <= collided_box[0] + collided_box[2] ||
       bounding_box[0] + bounding_box[2] >= collided_box[0] &&
         bounding_box[0] + bounding_box[2] <=
           collided_box[0] + collided_box[2]) &&
      (bounding_box[1] >= collided_box[1] &&
         bounding_box[1] <= collided_box[1] + collided_box[3] ||
       bounding_box[1] + bounding_box[3] >= collided_box[1] &&
         bounding_box[1] + bounding_box[3] <=
           collided_box[1] + collided_box[3]))
  {
    return true;
  }
  return false;
}

CollisionComponent::CollisionSide
CollisionComponent::getCollisionSide(const CollisionComponent& collided)
{
  if (hasCollided(collided))
  {
    float other_box[4];
    collided.getBoundingBox(other_box);

    float left_depth = bounding_box[0] + bounding_box[2] - other_box[0];
    float right_depth = other_box[0] + other_box[2] - bounding_box[0];
    float top_depth = bounding_box[1] + bounding_box[3] - other_box[1];
    float bottom_depth = other_box[1] + other_box[3] - bounding_box[1];

    if (left_depth < right_depth && left_depth < top_depth &&
        left_depth < bottom_depth)
    {
      return CollisionSide::SIDE_LEFT;
    }

    if (right_depth < left_depth && right_depth < top_depth &&
        right_depth < bottom_depth)
    {
      return CollisionSide::SIDE_RIGHT;
    }

    if (top_depth < left_depth && top_depth < right_depth &&
        top_depth < bottom_depth)
    {
      return CollisionSide::SIDE_TOP;
    }

    if (bottom_depth < left_depth && bottom_depth < right_depth &&
        bottom_depth < top_depth)
    {
      return CollisionSide::SIDE_BOTTOM;
    }
  }

  return CollisionSide::SIDE_NONE;
}

void CollisionComponent::setIsTrigger(bool value)
{
  is_trigger = value;
}

bool CollisionComponent::getIsTrigger()
{
  return is_trigger;
}

/*
 * each time checking collision update collision bounding box
 */
void CollisionComponent::updateBoundingBox(const float rect[4])
{
  for (int i = 0; i < BOX_SIZE; ++i)
  {
    bounding_box[i] = rect[i];
  }
}

void const CollisionComponent::getBoundingBox(float (&out_rect)[4]) const
{
  for (int i = 0; i < BOX_SIZE; ++i)
  {
    out_rect[i] = bounding_box[i];
  }
}
