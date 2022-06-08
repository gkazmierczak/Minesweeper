#pragma once
#include <SFML/Graphics.hpp>

#ifndef MINESWEEPER_COMMON_GUI
#define MINESWEEPER_COMMON_GUI

void initButton(sf::RectangleShape *rectangleShape,sf::Text *text, float rectX, float rectY, float textX,float textY,const sf::String &str, const sf::Color &fillColor,const sf::Color &outlineColor, const sf::Font &font);
bool buttonHover(sf::Event *event, sf::RectangleShape *box, sf::Text *text);
#endif //MINESWEEPER_COMMON_GUI