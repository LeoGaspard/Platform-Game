 /**
 * ========================
 * 
 * Filename: level.cpp
 * 
 * Author: NehZio <leo.gaspard@outlook.fr>
 * 
 * Description: The class level
 * 
 * Created: 28/08/15
 * =========================
 **/

#include <iostream>
#include <fstream>
#include "level.h"

using namespace std;

//CONSTRUCTOR   

 
 Level::Level()
 {
   scrollX = 0;   
 }
 
//DESTRUCTOR
 
 Level::~Level()
 {
   //nothing
 }
 
// LOAD MAP
 
 void Level::loadMap(string fileName)
 {
   string parse;
   ifstream flux(fileName.c_str());
   
   if(flux)
   {     
     do
     {
       getline(flux, parse);
     }while(parse != "#size");
     
     flux >> mapWidth;
     flux >> mapHeight;
     
     for(int i = 0; i < mapHeight; i++)
       map.push_back(vector<int>(mapWidth));
     for(int i = 1; i < mapWidth; i++)
       map[0].push_back(0);     
     
     do
     {
       getline(flux, parse);
     }while(parse != "#level");
     
     for(int i = 0; i < mapHeight; i++)
     {
       for(int j = 0; j < mapWidth; j++)
	 flux >> map[i][j];
     }  
   }
   else
     cout << "ERROR : Can't open the file " << fileName << endl;
   
   if(!tileSet.loadFromFile("pictures/tileSet1.png"))
      cout << "ERROR : Can't load image" << endl;
   if(!bg.loadFromFile("pictures/background1.png"))
       cout << "ERROR : Can't load image" << endl;
   
 }
 
//PRINT MAP

 void Level::printMap(sf::RenderWindow& window)
 {
   int posX = 0, posY = 0;
   
   sf::Sprite tile;
   
   backGround.setTexture(bg);
   
   window.draw(backGround);
    
  for(int i = 0; i < mapHeight; i++)
   {
     for(int j = (scrollX/TILE_WIDTH); j < ((scrollX+WINDOW_WIDTH)/TILE_WIDTH); j++)
     {
       int x = 0, y = 0;
       x = map[i][j] * 32;
       while(x > 320)
       {
	 x -= 320;
	 y += 32;	 
       }
       
      posX = 32*(j-(scrollX/TILE_WIDTH));
      posY = 32*i;
      
      tile.setTexture(tileSet);
      tile.setTextureRect(sf::IntRect(x,y,32,32));
      tile.setPosition(sf::Vector2f(posX,posY)); 
      window.draw(tile);
      
    }     
  }
   
 }

//SET SCROLL 

void Level::setScroll(int scroll)
{
  scrollX += scroll;
  if(scrollX > (mapWidth*TILE_WIDTH - WINDOW_WIDTH))
    scrollX = mapWidth*TILE_WIDTH - WINDOW_WIDTH;
  
  if(scrollX < 0)
    scrollX = 0;
}

//GET MAP

int Level::getMap(int x, int y)
{
  return map[x][y];
}

//GET SCROLL

int Level::getScroll()
{
  return scrollX;
}

//GET MAP MAPWIDTH

int Level::getMapWidth()
{
  return mapWidth;
}
