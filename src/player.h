/**
 * ========================
 * 
 * Filename: player.h
 * 
 * Author: NehZio <leo.gaspard@outlook.fr>
 * 
 * Created: 28/08/15
 * =========================
 **/
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include "level.h"
#include "main.h"

class Player
{
public :
  
  Player();
  ~Player();
  
 void movement(Level& level, sf::RenderWindow& window);
 void animation(sf::RenderWindow& window, Level& level);
 sf::Sprite getSprite();
  
private :
  
  
  int posX, posY, speed, lives, maxLives, spriteX, spriteY, spriteChange, coins;
  float jumpSpeed;
  bool stateWalking, stateJumping, stateFalling, stateDying, direction, done;
  std::map<sf::Keyboard::Key, bool> inputMap;
  sf::Texture spriteSheet;
  sf::Sprite playerSprite;
  
};

#endif