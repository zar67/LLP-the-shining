//
// Created by r3-manning on 29/01/2020.
//

#ifndef THE_SHINING_GAME_GROUP_3_AUDIOMANAGER_H
#define THE_SHINING_GAME_GROUP_3_AUDIOMANAGER_H

#include <Engine/FileIO.h>
#include <Engine/OGLGame.h>
#include <soloud.h>
#include <soloud_wav.h>

class AudioManager
{
 public:
  AudioManager() = default;
  ~AudioManager();

  bool audioSetUp();

  void replayGameMusic(double deltaTime);
  void playGameMusic();

  void playAxeMan();
  void playBox();
  void playCoin();
  void playDemon();
  void playGhost();
  void playDownAFloor();
  void playHeart();
  void playHit();
  void playMaybe();
  void playPowerUp();

  float time = 0;

 private:
  ASGE::FILEIO::File gameMusic;
  SoLoud::Wav gameMusic_MP3;

  ASGE::FILEIO::File axe_Man;
  SoLoud::Wav axe_Man_MP3;

  ASGE::FILEIO::File Box;
  SoLoud::Wav Box_MP3;

  ASGE::FILEIO::File Coin;
  SoLoud::Wav Coin_MP3;

  ASGE::FILEIO::File Demon;
  SoLoud::Wav Demon_MP3;

  ASGE::FILEIO::File Ghost;
  SoLoud::Wav Ghost_MP3;

  ASGE::FILEIO::File DownAFLoor;
  SoLoud::Wav DownAFLoor_MP3;

  ASGE::FILEIO::File Heart;
  SoLoud::Wav Heart_MP3;

  ASGE::FILEIO::File HitHurt;
  SoLoud::Wav HitHurt_MP3;

  ASGE::FILEIO::File Maybe;
  SoLoud::Wav Maybe_MP3;

  ASGE::FILEIO::File PowerUp;
  SoLoud::Wav PowerUp_MP3;

  SoLoud::Soloud soloud;
};

#endif // THE_SHINING_GAME_GROUP_3_AUDIOMANAGER_H
