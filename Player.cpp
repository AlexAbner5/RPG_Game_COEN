//Playaer.cpp


#include "Item.h"
#include "Player.h"
#include <iostream>


using namespace std;


// Constructor initializes default values and sets up the player's stats and hit points
Player::Player() : level(5), attackBonus(3), canAttackTwice(true), thunderBreakCooldown(0), crushingStormCooldown(0), abilityName() {
    rollStats();  // Roll for initial attribute values
    calculateHitPoints();  // Calculate initial hit points based on rolled stats
}

// Rolls attributes for the player using the 4d6-drop-the-lowest method for each stat
void Player::rollStats() {
    strength = roll4d6DropLowest();
    dexterity = roll4d6DropLowest();
    constitution = roll4d6DropLowest();
    intelligence = roll4d6DropLowest();
    wisdom = roll4d6DropLowest();
    charisma = roll4d6DropLowest();
    comeliness = roll4d6DropLowest();
    perception = roll4d6DropLowest();
}

// Calculates the player's hit points using the constitution modifier and dice rolls
void Player::calculateHitPoints() {
    int rolledHP = rollDie(10, 5); // Roll 5d10 for variable hit point component
    int constitutionModifier = (constitution - 10) / 2; // Calculate the modifier from constitution
    maxHitPoints = 10 + rolledHP + constitutionModifier; // Total hit points include base, roll, and modifier
    currentHitPoints = maxHitPoints; // Set current hit points to maximum at start
}

// Utility function to roll a single die with a specified number of sides
int Player::rollDie(int sides, int count) {
    int total = 0;
    static std::random_device rd;  // Only initialize once
    static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, sides);

    for (int i = 0; i < count; i++) {
        total += dis(gen);  // Roll the die 'count' times and sum the results
    }
    return total;
}

// Rolls four 6-sided dice, drops the lowest, and returns the sum of the highest three
int Player::roll4d6DropLowest() {
    std::vector<int> rolls(4); // Store the four rolls
    for (int& roll : rolls) {
        roll = rollDie(6, 1); // Roll a 6-sided die
    }
    std::sort(rolls.begin(), rolls.end()); // Sort the rolls to find the lowest easily
    return rolls[1] + rolls[2] + rolls[3]; // Sum the three highest rolls
}


// Applies damage to the player and ensures hit points do not drop below zero
void Player::applyDamage(int damage) {
    currentHitPoints -= damage; // Subtract damage from current hit points
    if (currentHitPoints < 0) currentHitPoints = 0; // Clamp current hit points to zero if below
    std::cout << "Player takes " << damage << " damage, current HP: " << currentHitPoints << std::endl;
}

// Heals the player and ensures hit points do not exceed maximum
void Player::heal(int amount) {
    currentHitPoints += amount; // Add healing amount to current hit points
    if (currentHitPoints > maxHitPoints) currentHitPoints = maxHitPoints; // Clamp current hit points to maximum if exceeded
    std::cout << "Player heals " << amount << " HP, current HP: " << currentHitPoints << std::endl;
}

// Activates a special ability if it's ready, resetting its cooldown
void Player::activateAbility(string name) {
    // Check if ability can be activated (cooldown is zero)
    if ((abilityName == "SHAZAM!" && thunderBreakCooldown == 0) || (abilityName == "FIREBLASTER!" && crushingStormCooldown == 0)) {
        std::cout << abilityName << " activated!" << std::endl;
        // Reset cooldowns for respective abilities
        if (abilityName == "SHAZAM!") {
            thunderBreakCooldown = 150;
            // Add effect logic here for SHAZAM!
        }
        else if (abilityName == "FIREBLASTER!") {
            crushingStormCooldown = 150;
            // Add effect logic here for FIREBLASTER!
        }
    }
    else {
        std::cout << "Ability not ready or unknown." << std::endl;
    }
}

// Updates cooldowns for abilities each turn
void Player::updateCooldowns() {
    if (thunderBreakCooldown > 0) thunderBreakCooldown--; // Decrement if cooldown is active
    if (crushingStormCooldown > 0) crushingStormCooldown--; // Decrement if cooldown is active
}


// New Item Interaction Methods
void Player::pickUpItem(shared_ptr<Item> item) {
    if (inventory.size() < maxInventorySize) {
        inventory.push_back(item);
        cout << "Picked up: " << item->getDescription() << endl;
    }
    else {
        cout << "Inventory full!" << endl;
    }
}

void Player::useItem(int index) {
    if (index >= 0 && index < inventory.size()) {
        inventory[index]->use(*this);  // Use the item
        inventory.erase(inventory.begin() + index);  // Remove it from inventory
    }
}

void Player::displayInventory() const {
    cout << "Inventory:\n";
    for (int i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ": " << inventory[i]->getDescription() << endl;
    }
}

void Player::setPsychosis(bool active, int duration) {
    psychosisActive = active;
    psychosisDuration = duration;
}

void Player::increaseStrength(int amount) {
    strength += amount;
}

void Player::addXP(int xp) {
    experience += xp;
}

int Player::getMaxHitPoints() const {
    return maxHitPoints;
}

void Player::setPlayerPosition(int x, int y)
 {
    playerX = x;
    playerY = y;
}

pair<int, int> Player:: getPlayerPosition() {
    return {playerX, playerY};
}