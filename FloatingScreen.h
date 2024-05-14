#ifndef FLOATINGSCREEN_H
#define FLOATINGSCREEN_H

#include "Player.h"
#include "TowerLevel.h"
#include "Item.h"
#include <iostream>
#include <string>

class FloatingScreen {
public:
    FloatingScreen( Player& player,  Level& level);
    void displayStats() ;
    void displayInventory() ;
    void displayRoomDescription() ;
    Player& player;
    Level& level;
    
    //void runGameLoop(char command);

private:
};

#endif // FLOATINGSCREEN_H
#pragma once
