// Item.cpp

#include "Item.h"
#include "Player.h"
#include "TowerLevel.h"
#include <iostream>

using namespace std;

void Food::use(Player& player) {
    player.heal(healthRecovery);
}

void HealingPotion::use(Player& player) {
    player.heal(player.getMaxHitPoints());
}

void EnergyPotion::use(Player& player) {
    player.increaseStrength(2);
    player.setPsychosis(true, 10);
}

void eGold::use(Player& player) {
    player.addXP(amount);
}

//void TeleportationStone::use(Player& player) {
//    // Assuming teleport functionality is implemented somewhere
//    teleportPlayer(player);
//}


