#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main() {
//    auto board=Board(8,8,8);
//    board.initBoard();
    sf::RenderWindow mainWindow(sf::VideoMode(1280,720),"Minesweeper");

//    board.setWindow(&mainWindow);
////    while(mainWindow.isOpen()){
//    board.render();
//    }
    auto game=Minesweeper::Game(&mainWindow);
    game.init();
    return 0;
}
