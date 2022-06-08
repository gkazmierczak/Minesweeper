#include <SFML/Graphics.hpp>
#include "Game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Minesweeper",sf::Style::Titlebar | sf::Style::Close);
    auto game=Minesweeper::Game(&mainWindow);
    game.init();
    return 0;
}
