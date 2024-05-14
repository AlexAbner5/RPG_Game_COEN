// Goblin.h

#ifndef GOBLIN_H
#define GOBLIN_H

#include "Creatures.h"
#include <cstdlib> 
#include <ctime>   

class Goblin : public Creature {
public:
    Goblin() : Creature("Goblin", 15, 7, 30, 8, 14, 10, 10, 8, 8) {
        // Initialize random seed for attack simulation
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    virtual ~Goblin() {}

    //void attack() override {
    //    std::cout << name << " attacks with ";
    //    if (rand() % 2) {  // Randomly choose between scimitar and shortbow
    //        scimitarAttack();
    //    }
    //    else {
    //        shortbowAttack();
    //    }
    //}

    //void move() override {
    //    std::cout << name << " moves stealthily to a new position." << std::endl;
    //    // Implementation for Goblin movement, possibly incorporating stealth mechanics
    //}

    void nimbleEscape() {
        std::cout << name << " uses Nimble Escape to avoid danger!" << std::endl;
        // Implementation for Nimble Escape, could involve changing position or dodging an attack
    }

private:
    void scimitarAttack() {
        std::cout << "a scimitar." << std::endl;
        int hitRoll = rollToHit(4);  // Scimitar uses +4 to hit
        if (hitRoll >= 10) {  // Assuming target armor class of 10 for demonstration
            int damage = rollDamage(1, 6, 2);  // 1d6 + 2 slashing damage
            std::cout << "Scimitar hits for " << damage << " slashing damage." << std::endl;
        }
        else {
            std::cout << "Scimitar misses the target." << std::endl;
        }
    }

    void shortbowAttack() {
        std::cout << "a shortbow." << std::endl;
        int hitRoll = rollToHit(4);  // Shortbow uses +4 to hit
        if (hitRoll >= 10) {  // Assuming same target armor class
            int damage = rollDamage(1, 6, 2);  // 1d6 + 2 piercing damage
            std::cout << "Shortbow hits for " << damage << " piercing damage." << std::endl;
        }
        else {
            std::cout << "Shortbow misses the target." << std::endl;
        }
    }

    int rollToHit(int bonus) {
        return rand() % 20 + 1 + bonus;  // Simple D20 roll
    }

    int rollDamage(int diceCount, int diceType, int bonus) {
        int damage = 0;
        for (int i = 0; i < diceCount; ++i) {
            damage += rand() % diceType + 1;
        }
        return damage + bonus;
    }
};

#endif // GOBLIN_H
