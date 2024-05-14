// Creatures.h

#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Creature {
public:

    string name;

    // Constructor con las estadísticas básicas de una criatura
    Creature(string name, int ac, int hp, int speed,
        int str, int dex, int con, int intl, int wis, int cha);

    // Destructor virtual para la correcta limpieza de la memoria
    virtual ~Creature() {}

    void attack();
    void move();
    void applyDamage(int damage);


    // Display basic stats
    void displayStats()  {
        cout << "Name: " << name
            << "\nArmor Class: " << armorClass
            << "\nHit Points: " << hitPoints
            << "\nSpeed: " << speed
            << "\nStrength: " << strength
            << "\nDexterity: " << dexterity
            << "\nConstitution: " << constitution
            << "\nIntelligence: " << intelligence
            << "\nWisdom: " << wisdom
            << "\nCharisma: " << charisma << endl;
    }


    // Verifica si la criatura está viva
    bool isAlive() {
        return hitPoints > 0;
    }

    // establece la posición de la criatura
    void setPosition(int x, int y) {
        posX = x;   
        posY = y;
    }
    // obtiene la posición de la criatura
    pair<int, int> getPosition()  {
        return { posX, posY };
    }

    int getHitPoints()  {
		return hitPoints;
	}

    int getDexterity() {
		return dexterity;
	}



private:
    int rollDie(int sides, int count);
    int roll4d6DropLowest();
    void calculateHitPoints();

    int armorClass;
    int hitPoints;
    int maxHitPoints;
    int speed;
    int strength, dexterity, constitution, intelligence, wisdom, charisma;
    int posX, posY;  // Coordenadas de la criatura

};

#endif // CREATURE_H
#pragma once
