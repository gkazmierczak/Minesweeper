class Tile {
public:
    Tile() {
//        sprite=sf::Sprite();
        revealed = false;
        marked = false;
        containsMine = false;
        nearbyMines = 0;
        detonated = false;
        lost=false;
    }

    int x;
    int y;

    bool isMarked() const {
        return marked;
    }

    bool isRevealed() const {
        return revealed;
    }

    void detonate() {
        detonated = true;
    }

    void setSize(int s) {
        size = s;
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
    void lose(){
        lost=true;
    }
    void draw(std::map<std::string, sf::Texture> *textureMap, sf::RenderWindow *window) {
        if (detonated) {
            sprite.setTexture(textureMap->at(std::string("mineblown")), true);
        }
        else if(lost && containsMine){
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

        sprite.setPosition(x * size, y * size);
        window->draw(sprite);
    }
    int nearbyMines;
    sf::Sprite sprite;

private:

    int size = 32;
    bool detonated;
    bool revealed;
    bool marked;
    bool lost;

};