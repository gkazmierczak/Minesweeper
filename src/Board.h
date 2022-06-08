#include <SFML/Graphics.hpp>
#include <random>
#include <experimental/filesystem>
#include "CommonGui.h"
#include "Tile.h"

namespace Minesweeper {

    class Board {
    public:
        Board() = default;

        Board(int w, int h, int mines);

        //initializes game board
        void initBoard() ;

        void setWindow(sf::RenderWindow *renderWindow) {
            window = renderWindow;
        }

        // increments count of nearby mines for each neighbour of mined tile
        void incrementNearbyFields(int x, int y);

        //Places mineCount mines on random positions on board, except for the initially clicked tile.
        void placeMines(int x, int y);

        // handles game loss
        void loseGame() ;

        // handles revealing nearby safe tiles
        void revealSafeNeighbours(int x, int y, bool recursive=false);

        // handles game win
        void winGame();

        // marks a tile, checks if win condition is met
        void markTile(int x, int y);

        // handles tile reveal, recursive for revealing nearby tiles when all neighbours are assumed to be empty or marked
        void revealTile(int x, int y, bool recursive = false);

        void draw();

        // handles game reset
        void resetBoard();

        void render();

        // load textures into a map to reduce memory consumption of the app
        void loadTextures();

    private:
        sf::RenderWindow *window;
        int width;
        int height;
        int mineCount;
        int tilesRevealed;
        int markedTiles;
        bool finished;
        sf::RectangleShape rsRestart;
        sf::RectangleShape rsBorder;
        sf::RectangleShape rsMenu;
        sf::Text menuText;
        sf::Text gameStatusText;
        sf::Font font;
        sf::Text restartText;
        std::map<std::string, sf::Texture> textureMap;
        Tile **tiles;
        bool gameStarted = false;
        bool exitToMenu = false;
    };


}