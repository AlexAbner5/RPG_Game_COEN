// Game.cpp

#include "Game.h"
#include "TowerLevel.h"
#include "Player.h"
#include "FloatingScreen.h"
#include "Creatures.h"
#include <iostream>
#include <iostream>
#include <random>
#include <memory>
#include <conio.h>

using namespace std;

// Cargar nivel
Game::Game(bool power, Level level, Player player, FloatingScreen screen) : currentLevel(level), _power(power), player(player), screen(screen) {

    if (_power) {
        currentLevel.loadLevel(currentLevel.number); 
    }
} 


void Game::fight(Player player, shared_ptr<Creature>creature) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> d20(1, 20);

    bool playerGoesFirst;

    while (player.isAlive() && creature.isAlive()) {
        // Roll for initiative
        int playerInitiative = d20(gen);
        int creatureInitiative = d20(gen);

        // Re-roll if there's a tie
        while (playerInitiative == creatureInitiative) {
            playerInitiative = d20(gen);
            creatureInitiative = d20(gen);
        }

        playerGoesFirst = playerInitiative < creatureInitiative;

        // Each round of fighting
        if (playerGoesFirst) {
            combatRound(player, creature);
            if (creature.isAlive()) {
                combatRound(creature, player);
            }
        }
        else {
            combatRound(creature, player);
            if (player.isAlive()) {
                combatRound(player, creature);
            }
        }

        // Check for flee
        if (checkForFlee(player, d20, gen)) {
            break;  // Ends the fight if opponent flees
        }

        // Print current health stats
        printHealthStats(player, shared_ptr<Creature> creature);
    }

    // Announce the winner
    announceWinner(player, shared_ptr<Creature> creature);

    // Announce the winner
    if (!player.isAlive()) {
        std::cout << "The player has died. The creature wins.\n";
    }
    else if (!creature.isAlive()) {
        std::cout << "The creature has died. The player wins.\n";
    }
}

bool Game::checkForFlee(Player player, uniform_int_distribution<> d20, mt19937  gen) {
    if (player.getCurrentHitPoints() < player.getMaxHitPoints() * 0.5) {
        int fleeChance = d20(gen);
        if (fleeChance <= 4) {  // 20% chance to flee
            std::cout << "The opponent has fled the battle!\n";
            return true; 
        }
    }
    return false;  // Opponent does not flee
}


void Game::moveLoop() 
{
    currentLevel.displayMap();  // inicializa el mapa

    char key;
    //screen.displayStats();
    //screen.displayInventory();
    //screen.displayRoomDescription();
    while (moveLoopActive)
    {
        cout << "\n\nInsert Your Move [WASD] or Exit [E]: ";

        key = _getch();
        if (key == 'e' || key == 'E')
        {
			moveLoopActive = false;
			break;
		}

        if (currentLevel.movePlayer(key)) {

            cout << "Move successful.\n";
            player.setPlayerPosition(currentLevel.playerX, currentLevel.playerY);
            system("cls");
            currentLevel.displayMap();

            pair<int, int> pos = player.getPlayerPosition();

            //Check for items in this position...
            auto  item = currentLevel.getItemAtPosition(pos.first, pos.second);

            if (item)
            {
                char choice;
                cout << "There is an item here: " << item->name << endl;
                cout << "Do you wnat to pickup this " << item->name << " ? (Y/N):" << endl;
                cin >> choice;

                if (toupper(choice) == 'Y')
                {
                    // Call Pickup
                    player.pickUpItem(item);
                    cout << "Yo have successfully collect the:" << item->name << endl;
                }
            }

            auto creature = currentLevel.getCreatureAtPosition(pos.first, pos.second);


            if (creature)
            {
                char choice;
                cout << "There is an creature here: " << creature->name << endl;
                cout << "Do you wnat to fight? " << creature->name << " ? (Y/N):" << endl;
                cin >> choice;

                if (toupper(choice) == 'Y')
                {
                    // Call Pickup
                    fight(player, creature);
                    cout << "Yo have successfully collect the:" << creature->name << endl;
                }
            }
        }
        else {
            cout << "Invalid move. Walls are '#' and cannot be passed.\n";
        }
    }

    system("cls");
    currentLevel.displayMap();
}

void Game::runGameLoop() {

    cout << "Enter command (stats [s], inventory [i], move [m], quit [q]): ";
    char command = _getch();  // Obtiene la tecla presionada

    cin >> command;

    switch (command) {
    case 's':  // stats
        screen.displayStats();
        break;
    case 'i':  // inventory
        screen.displayInventory();
        break;
    case 'm':  // move
        // Function to move player and update screen should be implemented
        // movePlayer(player, level);
        screen.displayRoomDescription();
        moveLoopActive = true;
        moveLoop();
        break;
    default:
        cout << "Invalid command!\n";
        break;
    }

}

void Game::printHealthStats( Player player, Creature creature) {
    std::cout << "Player HP: " << player.getCurrentHitPoints() << " / " << player.getMaxHitPoints() << std::endl;
    std::cout << "Creature HP: " << creature.getHitPoints() << std::endl;
}

void Game:: announceWinner( Player player,  Creature creature) {
    if (!player.isAlive()) {
        std::cout << "The player has died. The creature wins.\n";
    }
    else if (!creature.isAlive()) {
        std::cout << "The creature has died. The player wins.\n";
    }
}


void Game::combatRound(Player attacker, Creature defender) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> d20(1, 20);

    int attackRoll = d20(gen);

    // Check the results of the attack roll
    if (attackRoll == 1) {
        std::cout << "Epic fail! The attacker hits themselves.\n";
        attacker.applyDamage(5); // Example damage
    } else if (attackRoll == 20) {
        std::cout << "Critical hit! Maximum damage inflicted.\n";
        defender.applyDamage(10); // Example maximum damage
    } else if (attackRoll <= defender.getDexterity()) {
        std::cout << "The attack was evaded.\n";
    } else {
        // Proceed to hit, calculate damage
        int damage = d20(gen); // Simplified damage calculation
        defender.applyDamage(damage);
    }
}

void Game::combatRound(Creature attacker, Player defender) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> d20(1, 20);

    int attackRoll = d20(gen);

    // Check the results of the attack roll
    if (attackRoll == 1) {
        std::cout << "Epic fail! The attacker hits themselves.\n";
        attacker.applyDamage(5); // Example damage
    }
    else if (attackRoll == 20) {
        std::cout << "Critical hit! Maximum damage inflicted.\n";
        defender.applyDamage(10); // Example maximum damage
    }
    else if (attackRoll <= defender.getDexterity()) {
        std::cout << "The attack was evaded.\n";
    }
    else {
        // Proceed to hit, calculate damage
        int damage = d20(gen); // Simplified damage calculation
        defender.applyDamage(damage);
    }
}
