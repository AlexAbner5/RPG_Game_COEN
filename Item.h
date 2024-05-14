// Item.h

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>
#include "Player.h"

using namespace std;

class Player;

class Item {
public:
    Item(const string& itemName) : name(itemName) {}
    virtual ~Item() {}
    virtual void use(Player& player) = 0;
    virtual std::string getDescription() const = 0;
    string name;
};

class Food : public Item {
    int healthRecovery;
public:
    Food() : Item("Food"), healthRecovery(20) {} // Establece el nombre desde el constructor de Item
    void use(Player& player) override;
    std::string getDescription() const override { return "Food: Recovers health."; }
};


class HealingPotion : public Item {
public:
    HealingPotion() : Item("HealingPotion") {}
    void use(Player& player) override;
    std::string getDescription() const override { return "Healing Potion: Restores full health."; }
    string name = "HealingPotion";
};

class EnergyPotion : public Item {
public:
    EnergyPotion() : Item("EnergyPotion") {}
    void use(Player& player) override;
    std::string getDescription() const override { return "Energy Potion: Increases strength and causes psychosis."; }
};

class eGold : public Item {
    int amount;
public:
    eGold(int amt) : Item("eGold"), amount(amt) {}
    void use(Player& player) override;
    std::string getDescription() const override { return "e-Gold: Increases XP."; }
};

class TeleportationStone : public Item {
public:
    TeleportationStone() : Item("TeleportationStone") {}
    void use(Player& player) override;
    std::string getDescription() const override { return "Teleportation Stone: Teleports the player."; }

};

#endif // ITEM_H
#pragma once
