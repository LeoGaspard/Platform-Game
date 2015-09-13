 /**
 * ========================
 * 
 * Filename: player.cpp
 * 
 * Author: NehZio <leo.gaspard@outlook.fr>
 * 
 * Description: The player source
 * 
 * Created: 28/08/15
 * =========================
 **/
 
#include <iostream>
#include "player.h"

using namespace std;

//CONSTRUCTOR

Player::Player()
{
  posX = posY = 0;
  stateWalking = stateJumping = stateFalling = stateDying = false;
  direction = true;
  speed = 3;
  lives = 3;
  maxLives = 3; 
  playerHeight = 50;
  playerWidth = 40; 
  if(!spriteSheet.loadFromFile("pictures/SpriteSheet.png"))
    cout << "ERROR : Can't load SpriteSheet";
}

//DESTRUCTOR

Player::~Player()
{
  //nothing
}

//MOVEMENT

void Player::movement(Level& level, sf::RenderWindow& window)
{
  playerSprite.setTexture(spriteSheet);
  playerSprite.setTextureRect(sf::IntRect(0,0,playerWidth,playerHeight));
  
  if(level.getMap((posY+playerHeight) / TILE_HEIGHT, (posX + level.getScroll())/TILE_WIDTH) == 0)
    stateFalling = true;
  
  else if(level.getMap((posY+playerHeight) / TILE_HEIGHT, (posX + level.getScroll())/TILE_WIDTH) != 0)
    stateFalling = false;
  
  sf::Event event;
  while(window.pollEvent(event))
  {
    switch(event.type)
    {
      case sf::Event::Closed:
	window.close();
      break;
      
      case sf::Event::KeyPressed:
	switch(event.key.code)
	{
	  case sf::Keyboard::Escape:
	    window.close();
	  break;
	  
	  case sf::Keyboard::Up:
	  break;
	  
	  case sf::Keyboard::Down:
	  break;
	  
	  case sf::Keyboard::Left:
	    stateWalking = true;
	    direction = false;
	  break;
	  
	  case sf::Keyboard::Right:
	    stateWalking = true;
	    direction = true;
	  break;
	  
	  default:
	    break;
	}
      break;
      
	case sf::Event::KeyReleased:
	switch(event.key.code)
	{
	  case sf::Keyboard::Up:
	  break;
	  
	  case sf::Keyboard::Down:
	  break;
	  
	  case sf::Keyboard::Left:
	    stateWalking = false;
	  break;
	  
	  case sf::Keyboard::Right:
	    stateWalking = false;
	  break;
	  
	  default:
	    break;
	}
      break;
      
      default:
	break;	
    }
  }
  
  if(stateFalling)
  {
    posY+=5;
    if(posY > 480)
      stateDying = true;
  }
  
  if(stateWalking)
  {
    speed = 3;
    bool moveTest;
    
    if(posX > 1000 && level.getScroll() < (level.getMapWidth()*TILE_WIDTH - WINDOW_WIDTH) && direction)
    {
      level.setScroll(speed);
      moveTest = false;
    }    
    else if(direction)
    {
      moveTest = true;
    }    
    else if(!direction && posX < 250 && level.getScroll() > 0)
    {
      level.setScroll(-speed);
      moveTest = false;
    }    
    else if(!direction)
    {
      moveTest = true;
    }
    
    if(direction && posX < (1280-playerWidth) && moveTest)
    {
      if(level.getMap((posY + playerHeight) / TILE_HEIGHT - 1, (posX + playerWidth + speed + level.getScroll() + TILE_WIDTH) / TILE_WIDTH - 1) != 0 && level.getMap((posY + playerHeight -1) / TILE_HEIGHT - 1, (posX + playerWidth + speed + level.getScroll() + TILE_WIDTH) / TILE_WIDTH - 1) != 0)
      {	
	speed--;
	if(speed < 0)
	  speed = 0;
      }
      else
      {
	posX += speed;
      }
    }
    
    if(!direction && posX > 0 && moveTest)
    {
      if(level.getMap((posY + playerHeight) / TILE_HEIGHT - 1, (posX + playerWidth + speed + level.getScroll()) / TILE_WIDTH - 1) != 0 && level.getMap((posY + playerHeight -1) / TILE_HEIGHT - 1, (posX + playerWidth + speed + level.getScroll()) / TILE_WIDTH - 1) != 0)
	{	
	  speed--;
	  if(speed < 0)
	    speed = 0;
	}
      else
	posX -= speed;
    }
    
  }
  
  playerSprite.setPosition(sf::Vector2f(posX, posY));
  window.draw(playerSprite);
}