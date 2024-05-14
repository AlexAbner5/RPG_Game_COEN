// FloatingScreen.cpp

#include "FloatingScreen.h"
#include "Player.h"
#include "Item.h"
#include "TowerLevel.h"
#include <iostream>

using namespace std;

FloatingScreen::FloatingScreen(Player& player, Level& level) : player(player), level(level) {}

void FloatingScreen::displayStats() {
    cout << "Player Stats:\n"
        << "Strength: " << player.getStrength() << "\n"
        << "Dexterity: " << player.getDexterity() << "\n"
        << "Constitution: " << player.getConstitution() << "\n"
        << "Intelligence: " << player.getIntelligence() << "\n"
        << "Wisdom: " << player.getWisdom() << "\n"
        << "Charisma: " << player.getCharisma() << "\n"
        << "Comeliness: " << player.getComeliness() << "\n"
        << "Perception: " << player.getPerception() << "\n"
        << "Current Hit Points: " << player.getCurrentHitPoints() << "\n"
        << "Max Hit Points: " << player.getMaxHitPoints() << "\n"
        << "Experience: " << player.getExperience() << "\n";
}

void FloatingScreen::displayInventory() {

    auto inventory = player.getInventory();
    cout << "Inventory (" << inventory.size() << " items):\n";
    for (int i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ": " << inventory[i]->getDescription() << endl;
    }
}

void FloatingScreen::displayRoomDescription() {
    auto pos = player.getPlayerPosition();
    cout << "Room Description: " << level.getRoomDescription(pos.first, pos.second) << endl;
}