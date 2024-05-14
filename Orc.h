// Orc.h

#ifndef ORC_H
#define ORC_H

#include "Creatures.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

class Orc : public Creature {
public:
    Orc() : Creature("Orc", 13, 15, 30, 16, 12, 16, 7, 11, 10) {
        // Initialize random seed for attack simulation
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    virtual ~Orc() {}

    //void attack() override {
    //    std::cout << name << " attacks fiercely with ";
    //    if (rand() % 2) {  // Randomly choose between greataxe and javelin
    //        greataxeAttack();
    //    }
    //    else {
    //        javelinAttack();
    //    }
    //}

    //void move() override {
    //    std::cout << name << " charges aggressively." << std::endl;
    //    // Orcs can move aggressively towards enemies; you might add mechanics for this behavior.
    //}

    void aggressiveMove() {
        std::cout << name << " uses Aggressive to move swiftly towards an enemy!" << std::endl;
        // Implement specific aggressive movement mechanics for Orcs here
    }

private:
    void greataxeAttack() {
        std::cout << "a greataxe." << std::endl;
        int hitRoll = rollToHit(5);  // Greataxe uses +5 to hit
        if (hitRoll >= 10) {  // Assuming target armor class of 10 for demonstration
            int damage = rollDamage(1, 12, 3);  // 1d12 + 3 slashing damage
            std::cout << "Greataxe hits for " << damage << " slashing damage." << std::endl;
        }
        else {
            std::cout << "Greataxe misses the target." << std::endl;
        }
    }

    void javelinAttack() {
        std::cout << "a javelin." << std::endl;
        int hitRoll = rollToHit(5);  // Javelin uses +5 to hit
        if (hitRoll >= 10) {  // Assuming same target armor class
            int damage = rollDamage(1, 6, 3);  // 1d6 + 3 piercing damage
            std::cout << "Javelin hits for " << damage << " piercing damage." << std::endl;
        }
        else {
            std::cout << "Javelin misses the target." << std::endl;
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

#endif // ORC_H
#pragma once
