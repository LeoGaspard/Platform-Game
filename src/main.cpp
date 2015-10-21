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

#include "player.h"
#include <iostream>

using namespace std;

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280,480), "Plateform Game");
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
  Level level;
  Player player;
  
  level.loadMap("levels/1.txt");
  
  while(window.isOpen())
  {
    window.clear();
    level.printMap(window);
    player.movement(level, window);
    
    window.display();
  }
  return 0;
}
