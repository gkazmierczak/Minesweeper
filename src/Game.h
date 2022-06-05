#include <SFML/Graphics.hpp>
//#include "Board.h"
namespace Minesweeper {
    class Game {
    public:
        Game() = default;

        explicit Game(sf::RenderWindow *renderWindow) {
            window = renderWindow;
        };

        void init() {
            font.loadFromFile("C:\\Users\\Gabriel\\CLionProjects\\Minesweeper\\src\\resources\\Lato-Light.ttf");
            titleText.setString("Minesweeper");
            titleText.setFont(font);
            titleText.setFillColor(sf::Color(255, 255, 0));
            titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
            titleText.setPosition((window->getSize().x / 2) - 50, 20);
            titleText.setCharacterSize(48);
            rs1 = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
            rs1.setPosition(540, 150);
            rs1.setFillColor(sf::Color(32, 32, 32));
            rs1.setOutlineColor(sf::Color(190, 190, 190));
            rs1.setOutlineThickness(3);
            smallGame.setString("Easy");
            smallGame.setFont(font);
            smallGame.setOrigin(smallGame.getLocalBounds().width / 2, smallGame.getLocalBounds().height / 2);
            smallGame.setPosition((window->getSize().x / 2) - 10, 160);
            smallGame.setCharacterSize(36);
            rs2 = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
            rs2.setPosition(540, 300);
            rs2.setFillColor(sf::Color(32, 32, 32));
            rs2.setOutlineColor(sf::Color(190, 190, 190));
            rs2.setOutlineThickness(3);
            mediumGame.setString("Medium");
            mediumGame.setFont(font);
            mediumGame.setOrigin(mediumGame.getLocalBounds().width / 2, mediumGame.getLocalBounds().height / 2);
            mediumGame.setPosition((window->getSize().x / 2) - 10, 310);
            mediumGame.setCharacterSize(36);
            rs3 = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
            rs3.setPosition(540, 450);
            rs3.setFillColor(sf::Color(32, 32, 32));
            rs3.setOutlineColor(sf::Color(190, 190, 190));
            rs3.setOutlineThickness(3);
            largeGame.setString("Hard");
            largeGame.setFont(font);
            largeGame.setOrigin(largeGame.getLocalBounds().width / 2, largeGame.getLocalBounds().height / 2);
            largeGame.setPosition((window->getSize().x / 2) - 10, 460);
            largeGame.setCharacterSize(36);
            draw();
            render();
        }

        void draw() {
            window->clear();
            window->draw(rs1);
            window->draw(rs2);
            window->draw(rs3);
            window->draw(titleText);
            window->draw(smallGame);
            window->draw(mediumGame);
            window->draw(largeGame);
            window->display();
        }

        void render() {
            draw();
            while (window->isOpen()) {
                // check all the window's events that were triggered since the last iteration of the loop
                sf::Event event;
                while (window->pollEvent(event)) {
                    //get current mouseover
                    if (event.type == sf::Event::MouseMoved) {
                        if (rs1.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                            smallGame.setFillColor(sf::Color(255, 0, 0));
                        } else if (rs2.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                            mediumGame.setFillColor(sf::Color(255, 0, 0));
                        } else if (rs3.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                            largeGame.setFillColor(sf::Color(255, 0, 0));
                        } else {
                            smallGame.setFillColor(sf::Color(255, 255, 255));
                            mediumGame.setFillColor(sf::Color(255, 255, 255));
                            largeGame.setFillColor(sf::Color(255, 255, 255));
                        }
                    }
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (rs1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                gameBoard=Board(9,9,10);
                                gameBoard.initBoard();
                                gameBoard.setWindow(window);
                                window->clear();
                                gameBoard.render();

                            } else if (rs2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                gameBoard=Board(16,16,40);
                                gameBoard.initBoard();
                                gameBoard.setWindow(window);
                                window->clear();
                                gameBoard.render();
                                std::cout << "medium" << std::endl;
                            } else if (rs3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                gameBoard=Board(30,16,99);
                                gameBoard.initBoard();
                                gameBoard.setWindow(window);
                                window->clear();
                                gameBoard.render();
                                std::cout << "large" << std::endl;
                            }
                        }
                    }
                    draw();
                }
            }
        }

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