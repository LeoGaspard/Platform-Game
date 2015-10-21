 /**
 * ========================
 * 
 * Filename: main.cpp
 * 
 * Author: NehZio <leo.gaspard@outlook.fr>
 * 
 * Created: 28/08/15
 * =========================
 **/ 

#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "main.h"

class Level
{
public :
  
  Level();
  ~Level();
 
  void loadMap(std::string fileName);
  void printMap(sf::RenderWindow& window);
  void setScroll(int scroll);
  int getMap(int x, int y);
  int getScroll();
  int getMapWidth();
  bool bottomCollision(int posX, int posY);
  bool rightCollision(int posX, int posY, int speed);
  bool leftCollision(int posX, int posY, int speed);
  bool topCollision(int posX, int posY);
  
  
  
  
private :
  
  std::vector<std::vector<int> > map;
  
  int windowWidth, windowHeight;
  int tileWidth, tileHeight;
  int tileNumber;
  int mapWidth, mapHeight;
  int scrollX;
  sf::Texture tileSet;
  sf::Texture bg;
  sf::Sprite backGround;
  
  
};

#endif