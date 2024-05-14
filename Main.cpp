// Main.cpp

#include "Game.h"
#include "Player.h"
#include "FloatingScreen.h"
#include <iostream>
#include <conio.h> 
#include <windows.h>


using namespace std;

int main() {
    
    // Corre el juego
    try {
        Player player = Player();
        Level level = Level(1);  // Crea un nivel inicial 
        FloatingScreen screen(player, level);
        Game myGame = Game(true, level, player, screen);

        myGame.currentLevel.displayMap();  // inicializa el mapa

        // Ejecuta un bucle de movimineto mientras el juego esté activo
        while (myGame._power) {

            myGame.runGameLoop();

        }
    }
    
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

