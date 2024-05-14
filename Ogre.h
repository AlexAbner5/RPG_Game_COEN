// Ogre.h

#ifndef OGRE_H
#define OGRE_H

#include "Creatures.h"
#include <cstdlib>  
#include <ctime>    

class Ogre : public Creature {
public:
    Ogre() : Creature("Ogre", 11, 59, 40, 19, 8, 16, 5, 7, 7) {
        // Initialize random seed for attack simulation
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        // Ogres are more formidable with higher hit points and strong attacks
    }

    virtual ~Ogre() {}

    //void attack() override {
    //    std::cout << name << " swings mightily with ";
    //    if (rand() % 2) {  // Randomly choose between greatclub and javelin
    //        greatclubAttack();
    //    }
    //    else {
    //        javelinAttack();
    //    }
    //}

    //void move() override {
    //    std::cout << name << " lumbers forward ponderously." << std::endl;
    //    // Implement the movement logic, possibly slower due to size
    //}

private:
    void greatclubAttack() {
        std::cout << "a greatclub." << std::endl;
        int hitRoll = rollToHit(6);  // Greatclub uses +6 to hit
        if (hitRoll >= 10) {  // Assuming target armor class of 10 for demonstration
            int damage = rollDamage(2, 8, 4);  // 2d8 + 4 bludgeoning damage
            std::cout << "Greatclub hits for " << damage << " bludgeoning damage." << std::endl;
        }
        else {
            std::cout << "Greatclub misses the target." << std::endl;
        }
    }

    void javelinAttack() {
        std::cout << "a javelin." << std::endl;
        int hitRoll = rollToHit(6);  // Javelin uses +6 to hit
        if (hitRoll >= 10) {  // Assuming same target armor class
            int damage = rollDamage(2, 6, 4);  // 2d6 + 4 piercing damage
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

#endif // OGRE_H
#pragma once
