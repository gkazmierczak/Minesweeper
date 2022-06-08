#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile() {
        revealed = false;
        marked = false;
        containsMine = false;
        nearbyMines = 0;
        detonated = false;
        lost = false;
        won = false;
    }

    int x{};
    int y{};

    bool isMarked() const {
        return marked;
    }

    bool isRevealed() const {
        return revealed;
    }

    void detonate() {
        detonated = true;
    }

    void setOffsetX(int offset) {
        offsetX = offset;
    }

    bool containsMine;

    void addNearbyMine() {
        nearbyMines++;
    }

    void reveal() {
        revealed = true;
        marked = false;
    }

    void toggleMark() {
        marked = !marked;
    }

    void lose() {
        lost = true;
    }
    void win() {
        won = true;
    }
    void draw(std::map<std::string, sf::Texture> *textureMap, sf::RenderWindow *window);

    int nearbyMines;
    sf::Sprite sprite;

    void reset() {
        detonated = false;
        revealed = false;
        marked = false;
        lost = false;
        containsMine = false;
        nearbyMines = 0;
        won = false;
    }

private:
    int offsetX;
    int size = 32;
    bool detonated;
    bool revealed;
    bool marked;
    bool lost;
    bool won;

};