#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "Item.h"


using namespace std;
class Item;

class Player {
public:
    Player(); // Constructor
    void rollStats(); // Rolls initial stats using the 4d6 drop method
    void calculateHitPoints(); // Calculates hit points based on stats
    void displayStats(); // Displays current stats
    void applyDamage(int damage); // Applies damage to the player
    void heal(int amount); // Heals the player
    void activateAbility(string name); 
    string abilityName; // Activates a special ability
    void updateCooldowns(); // Updates cooldowns each turn

    
    
    void setPsychosis(bool active, int duration);  // To manage psychosis state
    void increaseStrength(int amount);            // To increase player's strength
    void addXP(int xp);                           // To add experience points
    int getMaxHitPoints() const;                  // To get maximum hit points
    void pickUpItem(std::shared_ptr<Item> item);
    void useItem(int index);  // Use item by index in inventory
    void displayInventory() const;
    bool psychosisActive;
    int psychosisDuration;
    void setPlayerPosition(int x, int y);
    pair<int,int> getPlayerPosition();

    int getStrength() { return strength; }
    int getDexterity() { return dexterity; }
    int getConstitution() { return constitution; }
    int getIntelligence() { return intelligence; }
    int getWisdom() { return wisdom; }
    int getCharisma() { return charisma; }
    int getComeliness() { return comeliness; }
    int getPerception() { return perception; }
    int getCurrentHitPoints() { return currentHitPoints; }
    int getExperience() { return experience; }
    bool isAlive() { return currentHitPoints > 0; }

    vector<shared_ptr<Item>> getInventory() { return inventory; }

private:

    std::vector<std::shared_ptr<Item>> inventory;  // Inventory to hold items
    int maxInventorySize = 10;  // Limit to inventory size for simplicity

    int strength, dexterity, constitution, intelligence, wisdom, charisma, comeliness, perception;
    int maxHitPoints;
    int currentHitPoints;
    int level;
    int attackBonus;
    bool canAttackTwice;
    int thunderBreakCooldown;
    int crushingStormCooldown;
    int experience;
    int playerX, playerY; // Coordenadas del jugador

    int rollDie(int sides, int count); // Utility to roll a die with a specified number of sides
    int roll4d6DropLowest(); // Utility to roll 4d6 and drop the lowest result
};

#endif // PLAYER_H
