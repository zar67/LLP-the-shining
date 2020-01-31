//
// Created by Zoe on 08/01/2020.
//

#include "Enemy.h"

/**
 *   @brief   Get the enemy's health
 *   @return  hp
 */
int Enemy::health()
{
  return hp;
}

/**
 *   @brief   Get the enemy's attack damage
 *   @return  damage
 */
int Enemy::attackDamage()
{
  return damage;
}

/**
 *   @brief   Render the enemy sprite
 *   @param   renderer The ASGE Renderer
 */
void Enemy::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*spriteComponent()->getSprite());
}

/**
 *   @brief   Damage the enemy
 *   @param   audio The audio manager to play the sound on
 *            hit The amount of damage to take off
 *   @return  True if enemy is dead
 */
bool Enemy::takeDamage(AudioManager* audio, int hit)
{
  audio->playHit();
  hp -= hit;

  return hp <= 0;
}
