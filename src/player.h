  /**
 * ========================
 * 
 * Filename: player.h
 * 
 * Author: NehZio <leo.gaspard@outlook.fr>
 * 
 * Description: The player header
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
  
private :
  
  
  int posX, posY, speed, lives, maxLives, playerHeight, playerWidth;
  float jumpSpeed;
  bool stateWalking, stateJumping, stateFalling, stateDying, direction;
  std::map<sf::Keyboard::Key, bool> inputMap;
  sf::Texture spriteSheet;
  sf::Sprite playerSprite;
  
};

#endif