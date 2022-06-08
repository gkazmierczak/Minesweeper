#include "Game.h"

void Minesweeper::Game::init() {
    font.loadFromFile(std::experimental::filesystem::current_path().string() +
                      std::string(R"(\src\resources\Lato-Light.ttf)"));
    titleText.setString("Minesweeper");
    titleText.setFont(font);
    titleText.setFillColor(sf::Color(255, 255, 0));
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(590, 20);
    titleText.setCharacterSize(48);
    rs1 = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
    rs2 = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
    rs3 = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
    initButton(&rs1,&smallGame, 540, 150, 630,160,"Easy",sf::Color(32, 32, 32),sf::Color(190, 190, 190),font);
    initButton(&rs2,&mediumGame, 540, 300, 630,310,"Medium",sf::Color(32, 32, 32),sf::Color(190, 190, 190),font);
    initButton(&rs3,&largeGame, 540, 450, 630,460,"Hard",sf::Color(32, 32, 32),sf::Color(190, 190, 190),font);
    draw();
    render();
}

void Minesweeper::Game::draw() {
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

void Minesweeper::Game::render() {
    draw();
    bool hover;
    while (window->isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event)) {
            //get current mouseover
            if (event.type == sf::Event::MouseMoved) {
                hover=buttonHover(&event,&rs1,&smallGame)||buttonHover(&event,&rs2,&mediumGame)||buttonHover(&event,&rs3,&largeGame);
                if(!hover){
                    smallGame.setFillColor(sf::Color(255, 255, 255));
                    mediumGame.setFillColor(sf::Color(255, 255, 255));
                    largeGame.setFillColor(sf::Color(255, 255, 255));
                }
            }
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // get clicked button and handle it accordingly
                    if (rs1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        gameBoard=Board(9,9,10);
                        gameBoard.initBoard();
                        gameBoard.setWindow(window);
                        window->clear();
                        smallGame.setFillColor(sf::Color(255, 255, 255));
                        gameBoard.render();
                    } else if (rs2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        gameBoard=Board(16,16,40);
                        gameBoard.initBoard();
                        gameBoard.setWindow(window);
                        window->clear();
                        mediumGame.setFillColor(sf::Color(255, 255, 255));
                        gameBoard.render();
                    } else if (rs3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        gameBoard=Board(30,16,99);
                        gameBoard.initBoard();
                        gameBoard.setWindow(window);
                        window->clear();
                        largeGame.setFillColor(sf::Color(255, 255, 255));
                        gameBoard.render();
                    }
                }
            }
            draw();
        }
    }
}

