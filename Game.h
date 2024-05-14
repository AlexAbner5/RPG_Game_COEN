// Game.h

#ifndef GAME_H
#define GAME_H

#include "TowerLevel.h"
#include "FloatingScreen.h"
#include "Player.h"
#include "Creatures.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

// Prende y apaga el juego
class Game {

public:
    Game(bool power, Level level, Player player, FloatingScreen screen); // Constructor de Game que inicia el juego con un nivel específico.
    bool _power = false; // Variable para controlar el estado de encendido del juego.
    Level currentLevel;  // Nivel actual del juego.
    Player player;
    FloatingScreen screen;
    void runGameLoop();



private:
    void fight(Player player, Creature creature);
    void combatRound(Player attacker, Creature defender);
    void combatRound(Creature attacker, Player defender);
    void announceWinner(Player player, Creature creature);
    void printHealthStats(Player player, Creature creature);
    bool heckForFlee(Player player, uniform_int_distribution<> d20,mt19937 gen);
    bool checkForFlee(Player player, std::uniform_int_distribution<> d20, std::mt19937  gen);
    void moveLoop();
    bool moveLoopActive = false;
};

#endif // GAME_H
#pragma once