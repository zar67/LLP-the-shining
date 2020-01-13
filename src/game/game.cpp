#include <iostream>
#include <string>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

#include "game.h"
/**
 *   @brief   Default Constructor.
 *   @details Consider setting the game's width and height
 *            and even seeding the random number generator.
 */
MyASGEGame::MyASGEGame()
{
  game_name = "ASGE Game";
  srand(time(nullptr));
}

/**
 *   @brief   Destructor.
 *   @details Remove any non-managed memory and callbacks.
 */
MyASGEGame::~MyASGEGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));

  this->inputs->unregisterCallback(
    static_cast<unsigned int>(mouse_callback_id));
}

/**
 *   @brief   Initialises the game.
 *   @details The game window is created and all assets required to
 *            run the game are loaded. The keyHandler and clickHandler
 *            callback should also be set in the initialise function.
 *   @return  True if the game initialised correctly.
 */
bool MyASGEGame::init()
{
  setupResolution();
  if (!initAPI())
  {
    return false;
  }

  toggleFPS();

  // input handling functions
  inputs->use_threads = false;

  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &MyASGEGame::keyHandler, this);

  mouse_callback_id = inputs->addCallbackFnc(
    ASGE::E_MOUSE_CLICK, &MyASGEGame::clickHandler, this);

  if (!map.generateRooms(renderer.get(), game_width, game_height))
  {
    return false;
  }

  player.init(renderer.get(),
              "/data/Characters/Demon.png",
              player_x,
              player_y,
              50.0f,
              50.0f);

  ASGE::DebugPrinter{} << "SETUP COMPLETE" << std::endl;
  return true;
}

/**
 *   @brief   Sets the game window resolution
 *   @details This function is designed to create the window size, any
 *            aspect ratio scaling factors and safe zones to ensure the
 *            game frames when resolutions are changed in size.
 *   @return  void
 */
void MyASGEGame::setupResolution()
{
  // how will you calculate the game's resolution?
  // will it scale correctly in full screen? what AR will you use?
  // how will the game be framed in native 16:9 resolutions?
  // here are some arbitrary values for you to adjust as you see fit
  // https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/
  // Scaling_and_MultiResolution_in_2D_Games.php

  game_width = 704;
  game_height = 448;
}

/**
 *   @brief   Processes any key inputs
 *   @details This function is added as a callback to handle the game's
 *            keyboard input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as
 *            you see fit.
 *   @param   data The event data relating to key input.
 *   @see     KeyEvent
 *   @return  void
 */
void MyASGEGame::keyHandler(ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
  if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.moveNorth();
    // player_y -= 10;
  }
  if (key->key == ASGE::KEYS::KEY_A && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.moveWest();
    // player_x -= 10;
  }
  if (key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.moveSouth();
    // player_y += 10;
  }
  if (key->key == ASGE::KEYS::KEY_D && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.moveEast();
    // player_x += 10;
  }
  if (key->key == ASGE::KEYS::KEY_G && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.generateRooms(renderer.get(), game_width, game_height);
    // map.getCurrentRoom()->addGhostToRoom(
    // renderer.get(), rand() % 400, rand() % 400);
  }
  if (key->key == ASGE::KEYS::KEY_H && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.getCurrentRoom()->removeGhostFromRoom(0);
  }

  // player movement
  playerInput(data);
}

/**
 *   @brief   Processes any click inputs
 *   @details This function is added as a callback to handle the game's
 *            mouse button input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as you
 *            see fit.
 *   @param   data The event data relating to key input.
 *   @see     ClickEvent
 *   @return  void
 */
void MyASGEGame::clickHandler(ASGE::SharedEventData data)
{
  auto click = static_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;

  ASGE::DebugPrinter{} << "x_pos: " << x_pos << std::endl;
  ASGE::DebugPrinter{} << "y_pos: " << y_pos << std::endl;
}

/**
 *   @brief   Updates the scene
 *   @details Prepares the renderer subsystem before drawing the
 *            current frame. Once the current frame is has finished
 *            the buffers are swapped accordingly and the image shown.
 *   @return  void
 */
void MyASGEGame::update(const ASGE::GameTime& game_time)
{
  double delta_time = game_time.delta.count() / 1000.0;

  map.updateCurrentRoom(delta_time, player_x, player_y);
  player.Movement(delta_time);

  if (!in_menu)
  {
  }
}

/**
 *   @brief   Renders the scene
 *   @details Renders all the game objects to the current frame.
 *            Once the current frame is has finished the buffers are
 *            swapped accordingly and the image shown.
 *   @return  void
 */
void MyASGEGame::render(const ASGE::GameTime&)
{
  renderer->setFont(0);

  map.renderCurrentRoom(renderer.get());
  map.renderMiniMap(renderer.get());

  renderer->renderSprite(*player.spriteComponent()->getSprite());
  player.weaponComponent()->render(renderer.get());

  // std::vector<Projectile> projectiles =
  // player.weaponComponent()->getProjectiles();
  // for(auto &bullet : projectiles)
  //  {
  //     renderer->renderSprite(*bullet.spriteComponent()->getSprite());
  //  }

  if (in_menu)
  {
  }
}

void MyASGEGame::playerInput(ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  // vertical movement
  if (key->key == ASGE::KEYS::KEY_DOWN &&
      key->action == ASGE::KEYS::KEY_PRESSED)
  {
    vec[1] = 1.0f;
    player.weaponComponent()->setLastDirection(0.0f, vec[1]);
  }
  else if (key->key == ASGE::KEYS::KEY_UP &&
           key->action == ASGE::KEYS::KEY_PRESSED)
  {
    vec[1] = -1.0f;
    player.weaponComponent()->setLastDirection(0.0f, vec[1]);
  }
  else if ((key->key == ASGE::KEYS::KEY_DOWN ||
            key->key == ASGE::KEYS::KEY_UP) &&
           key->action == ASGE::KEYS::KEY_RELEASED)
  {
    vec[1] = 0.0f;
  }
  // Horizontal movement
  if (key->key == ASGE::KEYS::KEY_RIGHT &&
      key->action == ASGE::KEYS::KEY_PRESSED)
  {
    vec[0] = 1.0f;
    player.weaponComponent()->setLastDirection(vec[0], 0.0f);
  }
  else if (key->key == ASGE::KEYS::KEY_LEFT &&
           key->action == ASGE::KEYS::KEY_PRESSED)
  {
    vec[0] = -1.0f;
    player.weaponComponent()->setLastDirection(vec[0], 0.0f);
  }
  else if ((key->key == ASGE::KEYS::KEY_LEFT ||
            key->key == ASGE::KEYS::KEY_RIGHT) &&
           key->action == ASGE::KEYS::KEY_RELEASED)
  {
    vec[0] = 0.0f;
  }
  player.setMovementVec(vec);

  if (key->key == ASGE::KEYS::KEY_SPACE &&
      key->action == ASGE::KEYS::KEY_PRESSED)
  {
    // fire bullet using players vector
    player.weaponComponent()->Fire(
      renderer.get(),
      player.spriteComponent()->getSprite()->xPos(),
      player.spriteComponent()->getSprite()->yPos());
  }
}
