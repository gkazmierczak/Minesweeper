#include <iostream>
#include "Board.h"
namespace Minesweeper {
    class Game {
    public:
        Game() = default;

        explicit Game(sf::RenderWindow *renderWindow) {
            window = renderWindow;
        };

        // initialize the ui
        void init();

        // draw ui
        void draw();

        //render loop
        void render();

    private:
        sf::Font font;
        sf::RenderWindow *window;
        sf::Text titleText;
        sf::RectangleShape rs1;
        sf::RectangleShape rs2;
        sf::RectangleShape rs3;
        sf::Text smallGame;
        sf::Text mediumGame;
        sf::Text largeGame;
        Board gameBoard;
    };
}