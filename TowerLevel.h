// TowerLevel.h


#ifndef TOWERLEVEL_H
#define TOWERLEVEL_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <map>
#include <utility>
#include <random>
#include "Goblin.h"
#include "Orc.h"
#include "Ogre.h"
#include "Creatures.h"
#include "Item.h"



using namespace std;

// Define la claselevel que gestiona la carga y visualización de los niveles del juego.
class Level {
public:
    map<pair<int, int>, vector<shared_ptr<Item>>> itemsInRoom; // Tracks items in each room

    void distributeItems(); // New function to distribute items across the level
    void pickUpItem(int x, int y, Player& player); // New function for picking up items
    void displayItemsInRoom(int x, int y); // New function to display items in the current room
    void placeItem(std::shared_ptr<Item> item, int x, int y);

    Level(int ln); // Constructor de level que carga el nivel especificado.

    int number;  // Número de nivel actual.

    int playerX, playerY; // Coordenadas del jugador

    bool movePlayer(char key); // Mueve al jugador 

    string loadLevel(int levelNumber); // Carga los niveles

    void displayMap() const; // Muestra el mapa

    string getRoomDescription(int x, int y) const; // Obtiene la descripción de la habitación
    void changeLevel();  // Cambia de nivel

    void setInitialPlayerPosition(); // Establece la posición inicial del jugador en el mapa

    // Da las coordenadas del jugador
    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }

    void spawnCreatures(); // Genera criaturas en el mapa

    template<typename T> void spawnGroup(int count); // Genera un grupo de criaturas

    template<typename T> void spawnSingle(); // Genera una criatura

    void updateCreaturePositions();// Actualiza las posiciones de las criaturas

    bool isValidClusterStart(int x, int y); // Verifica si la posición es válida para un grupo de criaturas

    shared_ptr<Item> getItemAtPosition(int x, int y); // Obtiene el ítem en la posición especificada\

    shared_ptr<Creature> getCreatureAtPosition(int x, int y); // Obtiene la criatura en la posición especificada

    map<int, map<pair<int, int>, string>> descriptions; // Stores descriptions for each room at each level

    map < pair<int, int>, vector<shared_ptr<Creature>>> creatures;  // Almacenamiento con  punteros de las criaturas

private:
    map<int, pair<int, int>> startPositions; // Posiciones iniciales en cada nivel

    vector<string> levelFiles;  // Vector que almacena los archivos de nivel

    vector<vector<int>> grid;  // Vector que almacena el mapa

    void loadMap(); // Carga el mapa desde los archivos de nivel

    void initLevelDescriptions();

    bool isValidPosition(int x, int y) const; // Verifica si la posición es válida

    bool isBlankSpace(int x, int y) const; // Verifica si la posición es un espacio en blanco


    void placeCreature(shared_ptr<Creature> creature, int x, int y); // Pone una criatura en el mapa con las coordenadas especificadas
};

#endif // TOWERLEVEL_H
