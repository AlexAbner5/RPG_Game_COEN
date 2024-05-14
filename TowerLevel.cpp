// TowerLevel.cpp


#include <conio.h> 
#include<windows.h>
#include "TowerLevel.h"
#include "Creatures.h"
#include "Goblin.h"
#include "Orc.h"
#include "Ogre.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <memory>
#include "Item.h"


using namespace std;

// Constructor de level que carga el nivel especificado.
Level::Level(int levelNumber) : number(levelNumber), playerX(0), playerY(0) {

    // Rutas a los archivos de mapa para cada nivel.
    levelFiles.push_back("C:\\Users\\Losma\\Desktop\\Final Coen\\rpg_game\\resources\\levels\\Level01 (1).csv");
    levelFiles.push_back("C:\\Users\\Losma\\Desktop\\Final Coen\\rpg_game\\resources\\levels\\Level02 (1).csv");
    levelFiles.push_back("C:\\Users\\Losma\\Desktop\\Final Coen\\rpg_game\\resources\\levels\\Level03 (1).csv");

    // Posiciones iniciales en cada nivel.
    startPositions[0] = { 5, 15 };
    startPositions[1] = { 13, 17 };
    startPositions[2] = { 3, 9 };

    // Configura el nivel si el número de nivel es válido.
    if (levelNumber > 0 && levelNumber <= levelFiles.size())
    {
        loadMap();
        setInitialPlayerPosition();
        spawnCreatures();
        distributeItems();
        initLevelDescriptions();

    }
}

// Establece la posición inicial del jugador en el mapa.
void Level::setInitialPlayerPosition() {
    auto it = startPositions.find(number - 1);
    if (it != startPositions.end()) {
        playerX = it->second.first;  // column
        playerY = it->second.second; // row
        cout << "Set initial position to (" << playerX << ", " << playerY << ") for Level " << number << endl;
    }
    else {
        cerr << "Level " << number << " does not have a start position defined!" << endl;
    }
}

// Carga el mapa desde los archivos de nivel.
void Level::loadMap() {
    ifstream file(loadLevel(number));
    if (!file.is_open()) {
        cerr << "Failed to open map file: " << loadLevel(number) << endl;
        return;
    }
    grid.clear();  // limpia el mapa antes de cargar uno nuevo
    string line;

    //Lee el archivo de mapa linia por linea y lo almacena en la matriz grid.
    while (getline(file, line)) {
        vector<int> row;
        stringstream linestream(line);
        string cell;
        while (getline(linestream, cell, ',')) {
            row.push_back(stoi(cell));
        }
        grid.push_back(row);
    }
}

// Inicializa las descripciones de las habitaciones.
void Level::initLevelDescriptions() {
    // Level 1 Descriptions
    descriptions[0][{3, 17}] = "This is a 3’ by 9’ room with an entrance to the north west and an exit to the south east. There seems to be something in the middle of the room.";
    descriptions[0][{5, 7}] = "A well lies in the north side of the room, and the floor is covered in square tiles, alternating white and black";
    descriptions[0][{9, 9}] = "A clunking sound can be faintly heard near the east wall, and a rusted axe lies in the south - west corner of the room";

    // Level 2 Descriptions
    descriptions[1][{15, 15}] = "Someone has scrawled 'Gili was here' on the north wall, and several rotten apples are scattered throughout the room";
    descriptions[1][{15, 19}] = "Part of the north wall has collapsed into the room, and the floor is covered with bloodstains";
    descriptions[1][{7, 17}] = "A group of draconic faces have been carved into the west wall, and someone The Guild of the Arrow and Lamp looted this place' on the west wall";

    // Level 3 Descriptions
    descriptions[2][{7, 13}] = "Numerous pillars line the south and east walls, and an iron ornaments are displayed in the north side of the room";
    descriptions[2][{14, 9}] = "Someone has scrawled 'You cannot kill it with magic' in draconic script on the south wall, and knocking can be faintly heard near the west wall";

}


// Da la descripción de una habitación basada en su posición.
string Level::getRoomDescription(int x, int y) const {
    auto itLevel = descriptions.find(number);
    if (itLevel != descriptions.end()) {
        auto itDesc = itLevel->second.find({ x, y });
        if (itDesc != itLevel->second.end()) {
            return itDesc->second;
        }
    }
    return "hola"; // Default description if none is set
}


// Comprueba si una posición en el mapa es válida para moverse.
bool Level::isValidPosition(int x, int y) const {
    return (y >= 0) && (y < grid.size()) && (x >= 0) && (x < grid[y].size()) && (grid[y][x] != 1);
}

// Comprueba la pocisión del item en el mapa
bool Level::isBlankSpace(int x, int y) const {
    return  (grid[y][x] == 0);
}

// Mueve el player en el mapa
bool Level::movePlayer(char key) {
    int newX = playerX;
    int newY = playerY;

    switch (key) {
    case 'W':
    case 'w':
        newY -= 1;
        break;
    case 'S':
    case 's':
        newY += 1;
        break;
    case 'D':
    case 'd':
        newX += 1;
        break;
    case 'A':
    case 'a':
        newX -= 1;
        break;
    default:
        return false;  // Invalid key, no movement
    }

    // Verifica si la nueva posición es válida y actualiza la posición del jugador.
    if (isValidPosition(newX, newY)) {

        //Asignar nueva posicion al player
        playerX = newX;
        playerY = newY;

        cout << getRoomDescription(newX, newY) << endl;

        // Verifica si el jugador ha llegado a un portal.
        if (grid[newY][newX] == 2) {
            changeLevel();
        }

        return true;
    }
    return false;
}


shared_ptr<Item> Level::getItemAtPosition(int x, int y) {

    pair<int, int> pos = make_pair(x, y);

    auto it = itemsInRoom.find(pos); // Buscar la clave en el mapa

    if (it != itemsInRoom.end()) {
        return it->second.front(); // Si la clave existe, devuelve el vector de ítems
    } else {
        return {}; // Si la clave no existe, devuelve un vector vacío
    }
}

shared_ptr<Creature> Level::getCreatureAtPosition(int x, int y) {

    pair<int, int> pos = make_pair(x, y);

    auto it = creatures.find(pos); // Buscar la clave en el mapa

    if (it != creatures.end()) {
        return it->second.front(); // Si la clave existe, devuelve el vector de ítems
    }
    else {
        return {}; // Si la clave no existe, devuelve un vector vacío
    }
}

// Cambia el nivel actual si se encuentra un portal.
void Level::changeLevel() {
    if (number == 3) {  // Caso especial: nivel 3 a nivel 1
        cout << "Portal to Level 1 activated. Returning to start...\n";
        number = 1;  // reset para el nivel 1
        loadMap();
        setInitialPlayerPosition();
        displayMap();
        spawnCreatures();
        cout << "Welcome back to Level 1!\n";
    }
    // Cambia al siguiente nivel si es válido.
    else {

        char choice;
        cout << "You have found a portal. Do you want to go to the next level? (Y/N): ";
        cin >> choice;
        if (toupper(choice) == 'Y' && number + 1 <= levelFiles.size()) {
            number++;
            loadMap();
            setInitialPlayerPosition();
            displayMap();
            spawnCreatures();
            cout << "Welcome to Level " << number << "!\n";
        }
        else {
            cout << "This is the highest level or invalid selection.\n";
        }
    }
}


// Muestra el mapa en la consola
void Level::displayMap() const {
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            // Accessing creatures positioned at (x, y)
            auto itPosition = creatures.find(std::make_pair(x, y)); // This should directly find the vector of creatures at (x, y)

            if (itPosition != creatures.end() && !itPosition->second.empty()) {
                // Now you need to check each creature at this position.
                for (const auto& creature : itPosition->second) {
                    // Use dynamic_cast to determine the type of creature
                    if (dynamic_cast<Goblin*>(creature.get()) != nullptr) {
                        std::cout << 'G' << " ";  // 'G' for Goblins
                        break;  // Assume only one creature type displayed per cell
                    }
                    else if (dynamic_cast<Orc*>(creature.get()) != nullptr) {
                        std::cout << 'O' << " ";  // 'O' for Orcs
                        break;
                    }
                    else if (dynamic_cast<Ogre*>(creature.get()) != nullptr) {
                        std::cout << 'E' << " ";  // 'E' for Ogres
                        break;
                    }
                }
            }
            else if (x == playerX && y == playerY) {
                std::cout << 'P' << " ";  // 'P' for Player
            }
            else {
                auto itItems = itemsInRoom.find({ x, y });
                if (itItems != itemsInRoom.end() && !itItems->second.empty()) {
                    std::cout << 'I' << " ";  // 'I' for Items
                }
                else {
                    // Render the map based on values from a CSV file
                    switch (grid[y][x]) {
                    case 1: std::cout << '#' << " "; break;  // Walls
                    case 0: std::cout << '.' << " "; break;  // Open space
                    case 2: std::cout << '@' << " "; break;  // Portals
                    case 3: std::cout << 'S' << " "; break;  // Safe spots
                    default: std::cout << ' ' << " "; break;  // Default for unexpected values
                    }
                }
            }
        }
        std::cout << std::endl;
    }
}






// Carga el archivo de nivel especificado.
string Level::loadLevel(int levelNumber) {
    if (levelNumber > 0 && levelNumber <= levelFiles.size()) {
        return levelFiles[levelNumber - 1];
    }
    else {
        throw std::out_of_range("Level number is out of valid range.");
        // Or return an empty string or a default path if you prefer not to use exceptions
    }
}

// crea las criaturas en el mapa
void Level::spawnCreatures() {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, grid.size() - 1);

    creatures.clear();  // Limpia las criaturas antes de generar nuevas

    if (number == 1) {  // Level 1 spawns groups of three goblins
        for (int i = 0; i < 3; ++i) {
            spawnGroup<Goblin>(3);
        }
    }
    else if (number == 2) {  // Level 2 spawns orcs
        for (int i = 0; i < 5; ++i) {
            spawnSingle<Orc>();
        }
    }
    else if (number == 3) {  // Level 3 spawns solamente un ogro
        spawnSingle<Ogre>();
    }
}

// Crea los goblins en el mapa
template<typename T>
void Level::spawnGroup(int count) {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, grid.size() - 1);

    int startX, startY;
    do {
        startX = distr(eng);
        startY = distr(eng);
    } while (!isValidClusterStart(startX, startY));

    for (int j = 0; j < count; ++j) {
        int x = startX + (j % 3) - 1;
        int y = startY + (j / 3) - 1;
        if (isBlankSpace(x, y)) {
            auto creature = make_shared<T>();
            creatures[make_pair(x, y)].push_back(creature);
            placeCreature(creature, x, y);
        }
    }
}
// Crea una sola criatura en el mapa
template<typename T>
void Level::spawnSingle() {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, grid.size() - 1);

    int x, y;
    do {
        x = distr(eng);
        y = distr(eng);
    } while (!isBlankSpace(x, y));

    auto creature = make_shared<T>();
    creatures[make_pair(x, y)].push_back(creature);
    placeCreature(creature, x, y);
}


// Verifica si en una determinada ubicación se puede poner un grupo de criaturas.
bool Level::isValidClusterStart(int x, int y) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (!isValidPosition(x + dx, y + dy)) return false;
        }
    }
    return true;
}

// Coloca una criatura en el mapa en una ubicación especificada.
void Level::placeCreature(shared_ptr<Creature> creature, int x, int y) {
    creature->setPosition(x, y);
}




void Level::distributeItems() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99), xPos(0, grid[0].size() - 1), yPos(0, grid.size() - 1);

    for (int i = 0; i < 10; ++i) { // Example: Attempt to place up to 10 items
        int x, y, attempts = 0;
        do {
            x = xPos(gen);
            y = yPos(gen); 
            attempts++; 
        } while (!isBlankSpace(x, y) && attempts < 100);

        if (attempts >= 100) {
            std::cout << "Failed to find a valid position for items after multiple attempts." << std::endl;
            continue; 
        }

        int chance = dis(gen);
        if (chance < 30) {
            itemsInRoom[{x, y}].push_back(make_shared<Food>());
        }
        else if (chance < 40) {
            itemsInRoom[{x, y}].push_back(make_shared<HealingPotion>());
        }
        else if (chance < 50) {
            itemsInRoom[{x, y}].push_back(make_shared<EnergyPotion>());
        }
        else if (chance < 70) {
            itemsInRoom[{x, y}].push_back(make_shared<eGold>(dis(gen) % 20 + 1));
        } // Poner los items en la habitación
    }
}


//void Level::pickUpItem(int x, int y, Player& player) {
//    auto& items = itemsInRoom[{x, y}];
//    if (!items.empty()) {
//        player.pickUpItem(items.front()); // Assume player picks up the first item
//        items.erase(items.begin()); // Remove the item from the room
//    }
//}