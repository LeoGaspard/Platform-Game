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

#include "functions.h"


int getLayer(int tile)
{
    if(tile == 0)
        return 0;
    if(tile < 10)
        return 1;
    if(tile >= 10 && tile < 20)
        return 2;
    if(tile >= 20 && tile < 30)
        return 3;
    if(tile >= 30)
        return 4;
}