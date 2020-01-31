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

  renderer->setClearColour(ASGE::COLOURS::BLACK);

  if (!scene_handler.init(
        inputs.get(), renderer.get(), game_width, game_height))
  {
    return false;
  }

  map.setupRoomCollision(game_width, game_height);

  std::string texture = "/data/Characters/Danny.png";

  player.init(renderer.get(),
              texture,
              game_width / 2.0f - 17,
              game_height / 2.0f - 24.5f);

  if (!audio_manager.audioSetUp())
  {
    return false;
  }
  audio_manager.playGameMusic();

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

  game_width = 1056;
  game_height = 672;
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
void MyASGEGame::keyHandler(const ASGE::SharedEventData& data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }

  if (!controller_connected)
  {
    playerMovement(data);
    playerShooting(data);
  }

  if (key->key == ASGE::KEYS::KEY_H && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    scene_handler.screenOpen(SceneManager::ScreenOpen::MAIN_MENU);
  }
}

/**
 *   @brief   Detects key press for player movement
 *   @param   data The event data relating to key input
 */
void MyASGEGame::playerMovement(const ASGE::SharedEventData& data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  // vertical movement
  if (key->key == ASGE::KEYS::KEY_DOWN &&
      key->action == ASGE::KEYS::KEY_PRESSED)
  {
    player.moveVertical(1.0f);
    last_shoot_dir[1] = 1;
  }
  else if (key->key == ASGE::KEYS::KEY_UP &&
           key->action == ASGE::KEYS::KEY_PRESSED)
  {
    player.moveVertical(-1.0f);
    last_shoot_dir[1] = -1;
  }
  else if ((key->key == ASGE::KEYS::KEY_DOWN ||
            key->key == ASGE::KEYS::KEY_UP) &&
           key->action == ASGE::KEYS::KEY_RELEASED)
  {
    player.moveVertical(0.0f);
    last_shoot_dir[1] = 0;
  }

  // Horizontal movement
  if (key->key == ASGE::KEYS::KEY_RIGHT &&
      key->action == ASGE::KEYS::KEY_PRESSED)
  {
    player.moveHorizontal(1.0f);
    last_shoot_dir[0] = 1;
  }
  else if (key->key == ASGE::KEYS::KEY_LEFT &&
           key->action == ASGE::KEYS::KEY_PRESSED)
  {
    player.moveHorizontal(-1.0f);
    last_shoot_dir[0] = -1;
  }
  else if ((key->key == ASGE::KEYS::KEY_LEFT ||
            key->key == ASGE::KEYS::KEY_RIGHT) &&
           key->action == ASGE::KEYS::KEY_RELEASED)
  {
    player.moveHorizontal(0.0f);
    last_shoot_dir[0] = 0;
  }
}

/**
 *   @brief   Detects key press for player shooting
 *   @param   data The event data relating to key input
 */
void MyASGEGame::playerShooting(const ASGE::SharedEventData& data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_SPACE &&
      key->action == ASGE::KEYS::KEY_PRESSED &&
      !(last_shoot_dir[0] == 0 && last_shoot_dir[1] == 0))
  {
    // Fire Using Shoot Vector
    ASGE::Sprite* sprite = player.spriteComponent()->getSprite();
    player.weaponComponent()->Fire(renderer.get(),
                                   sprite->xPos() + sprite->width() / 2,
                                   sprite->yPos() + sprite->height() / 2,
                                   last_shoot_dir[0],
                                   last_shoot_dir[1]);
  }
}

/**
 *   @brief   Handles controller input if one is connected
 *   @param   input The ASGE inputs
 */
void MyASGEGame::playerControllerInput(ASGE::Input* input)
{
  if (input->getGamePad(0).is_connected)
  {
    controller_connected = true;
    ASGE::GamePadData data = input->getGamePad(0);

    player.moveHorizontal(data.axis[0]);
    player.moveVertical(-data.axis[1]);

    if (data.axis[2] < -0.2f)
    {
      last_shoot_dir[0] = -1;
    }
    else if (data.axis[2] > 0.2f)
    {
      last_shoot_dir[0] = 1;
    }
    else
    {
      last_shoot_dir[0] = 0;
    }

    if (data.axis[3] < -0.2f)
    {
      last_shoot_dir[1] = 1;
    }
    else if (data.axis[3] > 0.2f)
    {
      last_shoot_dir[1] = -1;
    }
    else
    {
      last_shoot_dir[1] = 0;
    }

    if (!player.weaponComponent()->hasShot() &&
        !(last_shoot_dir[0] == 0 && last_shoot_dir[1] == 0))
    {
      player.weaponComponent()->hasShot(true);
      shoot_pressed = true;
      // Fire Using Shoot Vector
      ASGE::Sprite* sprite = player.spriteComponent()->getSprite();
      player.weaponComponent()->Fire(renderer.get(),
                                     sprite->xPos() + sprite->width() / 2,
                                     sprite->yPos() + sprite->height() / 2,
                                     last_shoot_dir[0],
                                     last_shoot_dir[1]);
    }

    if (!data.buttons[5])
    {
      shoot_pressed = false;
    }
  }
  else
  {
    controller_connected = false;
  }
}

/**
 *   @brief   Resets all the values of the game
 */
void MyASGEGame::resetGame()
{
  floor = 3;
  map.generateRooms(renderer.get(), game_width, game_height);
  player.reset(game_width, game_height);
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

  audio_manager.replayGameMusic(delta_time);
  if (scene_handler.inMenu())
  {
    SceneManager::ReturnValue return_value =
      scene_handler.update(delta_time, inputs.get());
    switch (return_value)
    {
      case SceneManager::ReturnValue::START_GAME:
        resetGame();
        break;
      case SceneManager::ReturnValue::EXIT_GAME:
        signalExit();
        break;
      case SceneManager::ReturnValue::BUY_DAMAGE_POWERUP:
        if (player.addDamagePowerup())
        {
          scene_handler.hideDamagePowerup();
          audio_manager.playPowerUp();
        }
        break;
      case SceneManager::ReturnValue::BUY_HEALTH_POWERUP:
        if (player.addHealthPowerup())
        {
          scene_handler.hideHealthPowerup();
          audio_manager.playPowerUp();
        }
        break;
      case SceneManager::ReturnValue::BUY_MOVE_SPEED_POWERUP:
        if (player.addMoveSpeedPowerup())
        {
          scene_handler.hideMoveSpeedPowerup();
          audio_manager.playPowerUp();
        }
        break;
      case SceneManager::ReturnValue::BUY_SHOT_SIZE_POWERUP:
        if (player.addShotSizePowerup())
        {
          scene_handler.hideShotSizePowerup();
          audio_manager.playPowerUp();
        }
        break;
      case SceneManager::ReturnValue::BUY_SHOT_SPEED_POWERUP:
        if (player.addShotSpeedPowerup())
        {
          scene_handler.hideShotSpeedPowerup();
          audio_manager.playPowerUp();
        }
        break;
      default:
        break;
    }
  }
  else
  {
    if (game_paused && scene_handler.updateGameSplashScreen(delta_time))
    {
      game_paused = false;
    }
    else if (!game_paused)
    {
      playerControllerInput(inputs.get());
      if (player.update(&audio_manager, delta_time, map.getEnemies(true)))
      {
        scene_handler.screenOpen(SceneManager::ScreenOpen::GAME_OVER);
      }
      if (map.axePsycho()->inRoom())
      {
        map.axePsycho()->update(delta_time,
                                player.spriteComponent()->getSprite()->xPos(),
                                player.spriteComponent()->getSprite()->yPos());
      }
      map.handlePlayerCollision(&player);

      std::vector<GameObject*> colliders = map.getEnemies(true);
      map.handleObjectCollision(colliders);

      if (map.updateCurrentRoom(renderer.get(),
                                &audio_manager,
                                delta_time,
                                &player,
                                game_width,
                                game_height))
      {
        // Descend Floor
        floor -= 1;
        map.generateRooms(renderer.get(), game_width, game_height);
        game_paused = true;
        scene_handler.openGameSplashScreen();

        if (floor == 0)
        {
          scene_handler.screenOpen(SceneManager::ScreenOpen::GAME_WON);
        }
      }
    }
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

  scene_handler.render(renderer.get(),
                       floor,
                       player.getCoins(),
                       player.getHealth(),
                       player.getPowerups());
}
