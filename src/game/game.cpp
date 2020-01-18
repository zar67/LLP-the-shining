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

  scene_handler.disableInputs(inputs.get());
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

  // toggleFPS();

  // input handling functions
  inputs->use_threads = false;

  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &MyASGEGame::keyHandler, this);

  mouse_callback_id = inputs->addCallbackFnc(
    ASGE::E_MOUSE_CLICK, &MyASGEGame::clickHandler, this);

  renderer->setClearColour(ASGE::COLOURS::BLACK);

  if (!scene_handler.init(
        inputs.get(), renderer.get(), game_width, game_height))
  {
    return false;
  }

  player.init(
    renderer.get(), "/data/Characters/Demon.png", 300, 300, 50.0f, 50.0f);

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
    scene_handler.screenOpen(SceneManager::ScreenOpen::MAIN_MENU);
  }
  if (key->key == ASGE::KEYS::KEY_H && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    map.getCurrentRoom()->removeGhostFromRoom(0);
  }

  // player movement
  playerKeyboardInput(data);
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

  ASGE::DebugPrinter() << x_pos << std::endl;
  ASGE::DebugPrinter() << y_pos << std::endl;
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

  if (scene_handler.inMenu())
  {
    SceneManager::ReturnValue return_value =
      scene_handler.update(delta_time, inputs.get());
    switch (return_value)
    {
      case SceneManager::ReturnValue::START_GAME:
        map.generateRooms(renderer.get(), game_width, game_height);
        break;
      case SceneManager::ReturnValue::EXIT_GAME:
        signalExit();
        break;
      case SceneManager::ReturnValue::BUY_DAMAGE_POWERUP:
        scene_handler.hideDamagePowerup();
        break;
      case SceneManager::ReturnValue::BUY_HEALTH_POWERUP:
        scene_handler.hideHealthPowerup();
        break;
      case SceneManager::ReturnValue::BUY_MOVE_SPEED_POWERUP:
        scene_handler.hideMoveSpeedPowerup();
        break;
      case SceneManager::ReturnValue::BUY_SHOT_SIZE_POWERUP:
        scene_handler.hideShotSizePowerup();
        break;
      case SceneManager::ReturnValue::BUY_SHOT_SPEED_POWERUP:
        scene_handler.hideShotSpeedPowerup();
        break;
      default:
        break;
    }
  }
  else // In Game
  {
    playerControllerInput(delta_time, inputs.get());
    player.Movement(delta_time, map.getCurrentRoom()->getEnemies());

    map.updateCurrentRoom(delta_time,
                          player.spriteComponent()->getSprite()->xPos(),
                          player.spriteComponent()->getSprite()->yPos());
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

  if (!scene_handler.inMenu())
  {
    map.renderCurrentRoom(renderer.get());
    map.renderMiniMap(renderer.get());
    player.weaponComponent()->render(renderer.get());
    renderer->renderSprite(*player.spriteComponent()->getSprite());
  }

  bool abilities[5] = { true, true, true, true, true };
  scene_handler.render(renderer.get(), 1, 10, 50, abilities);
}

void MyASGEGame::playerKeyboardInput(ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (!controller_connected)
  {
    // vertical movement
    if (key->key == ASGE::KEYS::KEY_DOWN &&
        key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.moveVertical(1.0f);
    }
    else if (key->key == ASGE::KEYS::KEY_UP &&
             key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.moveVertical(-1.0f);
    }
    else if ((key->key == ASGE::KEYS::KEY_DOWN ||
              key->key == ASGE::KEYS::KEY_UP) &&
             key->action == ASGE::KEYS::KEY_RELEASED)
    {
      player.moveVertical(0.0f);
    }
    // Horizontal movement
    if (key->key == ASGE::KEYS::KEY_RIGHT &&
        key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.moveHorizontal(1.0f);
    }
    else if (key->key == ASGE::KEYS::KEY_LEFT &&
             key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.moveHorizontal(-1.0f);
    }
    else if ((key->key == ASGE::KEYS::KEY_LEFT ||
              key->key == ASGE::KEYS::KEY_RIGHT) &&
             key->action == ASGE::KEYS::KEY_RELEASED)
    {
      player.moveHorizontal(0.0f);
    }

    if (key->key == ASGE::KEYS::KEY_SPACE &&
        key->action == ASGE::KEYS::KEY_PRESSED)
    {
      // fire bullet using players vector
      player.weaponComponent()->Fire(
        renderer.get(),
        player.spriteComponent()->getSprite()->xPos() +
          player.spriteComponent()->getSprite()->width() / 2,
        player.spriteComponent()->getSprite()->yPos() +
          player.spriteComponent()->getSprite()->height() / 2);
    }
  }
}

void MyASGEGame::playerControllerInput(double delta_time, ASGE::Input* input)
{
  if (input->getGamePad(0).is_connected)
  {
    controller_connected = true;
    ASGE::GamePadData data = input->getGamePad(0);

    if (data.axis[0] < -0.2f)
    {
      player.moveHorizontal(-1.0f);
    }
    else if (data.axis[0] > 0.2f)
    {
      player.moveHorizontal(1.0f);
    }
    else
    {
      player.moveHorizontal(0.0f);
    }

    if (data.axis[1] < -0.2f)
    {
      player.moveVertical(1.0f);
    }
    else if (data.axis[1] > 0.2f)
    {
      player.moveVertical(-1.0f);
    }
    else
    {
      player.moveVertical(0.0f);
    }

    if (!shoot_pressed && data.buttons[0])
    {
      shoot_pressed = true;
      player.weaponComponent()->Fire(
        renderer.get(),
        player.spriteComponent()->getSprite()->xPos() +
          player.spriteComponent()->getSprite()->width() / 2,
        player.spriteComponent()->getSprite()->yPos() +
          player.spriteComponent()->getSprite()->height() / 2);
    }

    if (!data.buttons[0])
    {
      shoot_pressed = false;
    }
  }
  else
  {
    controller_connected = false;
  }
}
