#include "Tile.h"
#include <random>

class Board {
public:
    Board() = default;

    Board(int w, int h, int mines) {
        width = w;
        height = h;
        mineCount = mines;
        tilesRevealed = 0;
        markedTiles=0;
        loadTextures();
    }

    void initBoard() {
        tiles = new Tile *[height];
        for (int i = 0; i < height; ++i) {
            tiles[i] = new Tile[width];
            for (int j = 0; j < width; ++j) {
                tiles[i][j].x = j;
                tiles[i][j].y = i;
            }
        }
    }

    void setWindow(sf::RenderWindow *renderWindow) {
        window = renderWindow;
    }

    void incrementNearbyFields(int x, int y) {
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width && (i != 0 || j != 0)) {
                    tiles[y + i][x + j].addNearbyMine();
                }
            }
        }
    }

//Places mineCount mines on random positions on board, except for the initially clicked tile.
    void placeMines(int x, int y) {
        int minesPlaced = 0;
        int randomX;
        int randomY;
        while (minesPlaced < mineCount) {
            randomX = std::rand() % width;
            randomY = std::rand() % height;
            if (!tiles[randomY][randomX].containsMine && (randomY != y || randomX != x)) {
                tiles[randomY][randomX].containsMine = true;
                incrementNearbyFields(randomX, randomY);
                minesPlaced++;
            }
        }
        gameStarted=true;
    }
    void loseGame(){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                tiles[i][j].lose();
            }
        }
        std::cout <<"mina "<< std::endl;
    }
    void revealSafeNeighbours(int x,int y,bool recursive=false){
        int markedNeighbours=0;
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width && (i != 0 || j != 0)) {
                    if(tiles[y+i][x+j].isMarked()){
                        markedNeighbours++;
                    }

                }
            }
        }
        if(markedNeighbours==tiles[y][x].nearbyMines){
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width && (i != 0 || j != 0) ) {
                        if(!tiles[y+i][x+j].isRevealed() &&(!tiles[y+i][x+j].isMarked()||!tiles[y+i][x+j].containsMine)){
                            revealTile(x+j,y+i,recursive);
                        }
                    }
                }
            }
        }
    }
    void winGame(){
        std::cout <<"ez win"<< std::endl;
    }
    void markTile(int x,int y){
        if(tiles[y][x].isMarked()){
            markedTiles--;
        }
        else{
            markedTiles++;
        }
        tiles[y][x].toggleMark();
        if(markedTiles+tilesRevealed==width*height||tilesRevealed==width*height-mineCount){
            winGame();
        }
    }
    void revealTile(int x, int y,bool recursive=false){
        if(tiles[y][x].containsMine){
            tiles[y][x].detonate();
            loseGame();
        }
        else{
            if(!tiles[y][x].isRevealed()&& !tiles[y][x].isMarked()){
                tiles[y][x].reveal();
                tilesRevealed++;
                if(recursive || tiles[y][x].nearbyMines==0){
                    revealSafeNeighbours(x,y,true);
                }
                if(markedTiles+tilesRevealed==width*height||tilesRevealed==width*height-mineCount){
                    winGame();
                }
            }
            else{
                revealSafeNeighbours(x,y,false);
            }

        }
    }
    void draw(){
        window->clear();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                tiles[i][j].draw(&textureMap,window);
            }
        }
        window->display();
    }

    void render() {
        if (window == nullptr) {
            exit(EXIT_FAILURE);
        }
        else {
            draw();
            while (window->isOpen()) {
                // check all the window's events that were triggered since the last iteration of the loop
                sf::Event event;
                while (window->pollEvent(event)) {
                    // "close requested" event: we close the window
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (event.type == sf::Event::MouseButtonPressed) {
                        for (int i = 0; i < height; ++i) {
                            for (int j = 0; j < width; ++j) {
                                if (tiles[i][j].sprite.getGlobalBounds().contains(event.mouseButton.x,
                                                                                  event.mouseButton.y)) {
                                    if(event.mouseButton.button == sf::Mouse::Left){
                                        if(!gameStarted){
                                            std::cout <<"start "<< i << " " << j << std::endl;

                                            placeMines(j,i);
                                            revealTile(j,i,true);

                                        }
                                        else{
                                            revealTile(j,i);

                                        }
                                        std::cout << i << " " << j << std::endl;
                                    }
                                    else if(event.mouseButton.button == sf::Mouse::Right && gameStarted){
                                        std::cout <<"rmb "<< i << " " << j << std::endl;
                                        markTile(j,i);
                                    }
                                }
                            }
                        }
                        draw();
                    }
                }
            }
//            }
        }
    }

    void loadTextures() {
        std::string states[13] = {"base", "mine", "flag", "mineblown", "0", "1", "2", "3", "4", "5", "6", "7", "8"};
        for (auto key: states) {
            textureMap[key] = sf::Texture();
            textureMap[key].loadFromFile(
                    std::string("C:\\Users\\Gabriel\\CLionProjects\\Minesweeper\\src\\resources\\") + key +
                    std::string(".png"));
        }
    }

private:
    sf::RenderWindow *window;
    int width;
    int height;
    int mineCount;
    int tilesRevealed;
    int markedTiles;
    std::map<std::string, sf::Texture> textureMap;
    Tile **tiles;
    bool gameStarted = false;
};


