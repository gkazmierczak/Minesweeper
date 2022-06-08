#include "Tile.h"

void Tile::draw(std::map <std::string, sf::Texture> *textureMap, sf::RenderWindow *window) {
    if (detonated) {
        sprite.setTexture(textureMap->at(std::string("explosion")), true);
    } else if (lost && containsMine) {
        sprite.setTexture(textureMap->at(std::string("loss")), true);
    } else if (won && containsMine){
        sprite.setTexture(textureMap->at(std::string("mine")), true);
    }
    else {
        if (isRevealed()) {
            sprite.setTexture(textureMap->at(std::to_string(nearbyMines)), true);
        } else {
            if (marked) {
                sprite.setTexture(textureMap->at(std::string("flag")), true);
            } else {
                sprite.setTexture(textureMap->at(std::string("base")), true);
            }
        }
    }

    sprite.setPosition(x * size + offsetX, y * size + 100);
    window->draw(sprite);
}