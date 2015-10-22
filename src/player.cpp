/**
* ========================
* 
* Filename: player.cpp
* 
* Author: NehZio <leo.gaspard@outlook.fr>
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
stateWalking = stateFalling = stateDying = false;
direction = true;
maxLives = 3;
lives = maxLives;
coins = 0;
jumpSpeed = 0.0f;
spriteX = 0;
spriteY = 0;
spriteChange = 0;
if(!spriteSheet.loadFromFile("pictures/sprite.png"))
cout << "ERROR : Can't load SpriteSheet";
}

/******************
 *   DESTRUCTOR   *
 ******************/

Player::~Player()
{
//nothing
}

/******************
 *    MOVEMENT    *
 ******************/

void Player::movement(Level& level, sf::RenderWindow& window)
{
    if(posY + PLAYER_HEIGHT - (int)jumpSpeed < 480)
    {        
        if(level.bottomCollision(posX, posY, stateDying))
        {
            stateFalling = false;
            jumpSpeed = 0.0f;
        }
        else
            stateFalling = true; 
    }
    
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
                    
                    default:
                        inputMap[event.key.code] = true;
                    break;
                }
                    break;
                    
            case sf::Event::KeyReleased:
                inputMap[event.key.code] = false;
            break;
                    
            default:
                break;	
          }
    }

    if(inputMap[sf::Keyboard::Up])
    {
        if(!stateFalling)
        {
            jumpSpeed = 10.0f;
            stateFalling = true;
        }
    }

    if(inputMap[sf::Keyboard::Left] && !inputMap[sf::Keyboard::Right])
    {
        stateWalking = true;
        direction = false;
    }  
    if(inputMap[sf::Keyboard::Right] && !inputMap[sf::Keyboard::Left])
    {
        stateWalking = true;
        direction = true;
    }
    
    if((inputMap[sf::Keyboard::Right] && inputMap[sf::Keyboard::Left]) || (!inputMap[sf::Keyboard::Right] && !inputMap[sf::Keyboard::Left]))
        stateWalking = false;

    if(stateFalling)
    {
        posY-=(int)jumpSpeed;
        
        jumpSpeed -= 0.5;
        
        while(jumpSpeed > 0 && level.topCollision(posX, posY, stateDying))
        {
            jumpSpeed--;
        }

        if(posY > 480)
            stateDying = true;
        
    }
    
    if(stateWalking)
    {
        speed = 3;
        bool moveTest;
        
        
        if(!direction)
        {
            moveTest = true;
        }

        if(direction && posX < (1280 - PLAYER_WIDTH))
        {
            while(level.rightCollision(posX, posY, speed, stateDying))
            {
                speed--;                
                if(speed == 0)
                    break;                
            }
           
            if(posX > 1000 && level.getScroll() < (level.getMapWidth()*TILE_WIDTH - WINDOW_WIDTH) && direction)
                level.setScroll(speed);
            else
                posX += speed;
        }

        if(!direction && posX > 0 && moveTest)
        {
            while(level.leftCollision(posX, posY, speed, stateDying))
            {
                speed--;
                if(speed == 0)
                    break;
            } 
            
            if(posX < 250 && level.getScroll() > 0)
                level.setScroll(-speed);
            else
                posX -= speed;
        }
    }
    
   if(level.bottomCollision(posX, posY, stateDying) && posY + PLAYER_HEIGHT < 480)
        posY = ((posY + PLAYER_HEIGHT)/ TILE_HEIGHT) * TILE_HEIGHT - PLAYER_HEIGHT;
    
    if(stateDying)
    {
        lives--;
        posX = 0;
        posY = 0;
        if(lives <= 0)
            posX = -1500;
        stateDying = false;
        jumpSpeed = 0.0f;
        level.setScroll(-level.getScroll());
    }
    
    animation(window, level);
    
    
    
}

/******************
 *    ANIMATION   *
 ******************/

void Player::animation(sf::RenderWindow& window,Level& level)
{
    playerSprite.setTexture(spriteSheet);
    
    if(stateWalking && !stateFalling && direction)
    {
        spriteY = 0;
        if(spriteChange == 4)
        {
            spriteX = (spriteX + PLAYER_WIDTH)%114;
            spriteChange = 0;
        }
        
        spriteChange++;
        
    }
    
    if(stateWalking && !stateFalling && !direction)
    {
        spriteY = PLAYER_HEIGHT;
        
        if(spriteChange == 4)
        {
            spriteX = (spriteX + PLAYER_WIDTH)%114;
            spriteChange = 0;
        }
        
        spriteChange++;
    }
    
    if(stateFalling && jumpSpeed > 0 )
    {
        if(direction)
            spriteY = 2*PLAYER_HEIGHT;
        else
            spriteY = 3*PLAYER_HEIGHT;
        if(spriteChange == 4)
        {
            spriteX = (spriteX + PLAYER_WIDTH)%76;
            spriteChange = 0;
        }
        
        spriteChange++;
    }
    
   if(!stateWalking && !stateFalling)
    {
        spriteX = 0;
        if(direction)
            spriteY = 0;
        if(!direction)
            spriteY = PLAYER_HEIGHT;
    }
    
    playerSprite.setTextureRect(sf::IntRect(spriteX,spriteY,PLAYER_WIDTH,PLAYER_HEIGHT));
    playerSprite.setPosition(sf::Vector2f(posX, posY));
   
   level.update(window, playerSprite, lives, coins);
}

/******************
 *   GET SPRITE   *
 ******************/

sf::Sprite Player::getSprite()
{
    return playerSprite;
}