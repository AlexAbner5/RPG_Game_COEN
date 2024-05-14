

#include "Item.h"
#include "Creatures.h"
#include <iostream>


using namespace std;


// Constructor initializes default values and sets up the player's stats and hit points
Creature::Creature(string name, int ac, int hp, int speed,
    int str, int dex, int con, int intl, int wis, int cha)
    : name(name), armorClass(ac), hitPoints(hp), speed(speed),
    strength(str), dexterity(dex), constitution(con), intelligence(intl),
    wisdom(wis), charisma(cha) {
    calculateHitPoints();  
}


// Utility function to roll a single die with a specified number of sides
int Creature::rollDie(int sides, int count) {
    int total = 0;
    static std::random_device rd;  // Only initialize once
    static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, sides);

    for (int i = 0; i < count; i++) {
        total += dis(gen);  // Roll the die 'count' times and sum the results
    }
    return total;
}

// Calculates the player's hit points using the constitution modifier and dice rolls
void Creature::calculateHitPoints() {
    int rolledHP = rollDie(10, 5); // Roll 5d10 for variable hit point component
    int constitutionModifier = (constitution - 10) / 2; // Calculate the modifier from constitution
    maxHitPoints = 10 + rolledHP + constitutionModifier; // Total hit points include base, roll, and modifier
    hitPoints = maxHitPoints; // Set current hit points to maximum at start
}

// Rolls four 6-sided dice, drops the lowest, and returns the sum of the highest three
int Creature::roll4d6DropLowest() {
    std::vector<int> rolls(4); // Store the four rolls
    for (int& roll : rolls) {
        roll = rollDie(6, 1); // Roll a 6-sided die
    }
    std::sort(rolls.begin(), rolls.end()); // Sort the rolls to find the lowest easily
    return rolls[1] + rolls[2] + rolls[3]; // Sum the three highest rolls
}


// Applies damage to the player and ensures hit points do not drop below zero
void Creature::applyDamage(int damage) {
    hitPoints -= damage; // Subtract damage from current hit points
    if (hitPoints < 0) hitPoints = 0; // Clamp current hit points to zero if below
    std::cout << "Creature takes " << damage << " damage, current HP: " << hitPoints << std::endl;
}