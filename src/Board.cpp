#include "Board.h"

Minesweeper::Board::Board(int w, int h, int mines) {
    width = w;
    height = h;
    mineCount = mines;
    tilesRevealed = 0;
    markedTiles = 0;
    finished = false;
    loadTextures();
}

void Minesweeper::Board::initBoard() {
    int offsetX = (1280 - (32 * width)) / 2;
    tiles = new Tile *[height];
    for (int i = 0; i < height; ++i) {
        tiles[i] = new Tile[width];
        for (int j = 0; j < width; ++j) {
            tiles[i][j].x = j;
            tiles[i][j].y = i;
            tiles[i][j].setOffsetX(offsetX);
        }
    }
    font.loadFromFile(std::experimental::filesystem::current_path().string() +
                      std::string(R"(\src\resources\Lato-Light.ttf)"));
    rsMenu = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
    rsRestart = sf::RectangleShape(sf::Vector2f(200.f, 50.f));
    rsBorder = sf::RectangleShape(sf::Vector2f(width*32.f, height*32.f));
    rsBorder.setOutlineColor(sf::Color(128, 128, 128));
    rsBorder.setOutlineThickness(5);
    rsBorder.setPosition(offsetX,100);
    rsBorder.setFillColor(sf::Color(0, 0, 0,0));
    initButton(&rsMenu, &menuText, 390, 10, 470, 20, "Main Menu", sf::Color(32, 32, 32),
               sf::Color(190, 190, 190), font);
    initButton(&rsRestart, &restartText, 690, 10, 780, 20, "Restart", sf::Color(32, 32, 32),
               sf::Color(190, 190, 190), font);
    gameStatusText.setFont(font);
    gameStatusText.setOrigin(gameStatusText.getLocalBounds().width / 2,
                             gameStatusText.getLocalBounds().height / 2);
    gameStatusText.setPosition(640, 640);
    gameStatusText.setCharacterSize(60);
    gameStatusText.setFillColor(sf::Color(0, 255, 0));
}

void Minesweeper::Board::incrementNearbyFields(int x, int y) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width && (i != 0 || j != 0)) {
                tiles[y + i][x + j].addNearbyMine();
            }
        }
    }
}

void Minesweeper::Board::placeMines(int x, int y) {
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
    gameStarted = true;
}

void Minesweeper::Board::loseGame() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[i][j].lose();
        }
    }
    finished = true;
    gameStatusText.setString("DEFEAT");
    gameStatusText.setOrigin(gameStatusText.getLocalBounds().width / 2,
                             gameStatusText.getLocalBounds().height / 2);
    gameStatusText.setPosition(640, 640);
    gameStatusText.setFillColor(sf::Color(255, 0, 0));
}

void Minesweeper::Board::revealSafeNeighbours(int x, int y, bool recursive) {
    int markedNeighbours = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width && (i != 0 || j != 0)) {
                if (tiles[y + i][x + j].isMarked()) {
                    markedNeighbours++;
                }

            }
        }
    }
    if (markedNeighbours == tiles[y][x].nearbyMines) {
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (y + i >= 0 && y + i < height && x + j >= 0 && x + j < width && (i != 0 || j != 0)) {
                    if (!tiles[y + i][x + j].isRevealed() &&
                        (!tiles[y + i][x + j].isMarked() || !tiles[y + i][x + j].containsMine)) {
                        revealTile(x + j, y + i, recursive);
                    }
                }
            }
        }
    }
}

void Minesweeper::Board::winGame() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[i][j].win();
        }
    }
    finished = true;
    gameStatusText.setString("VICTORY");
    gameStatusText.setOrigin(gameStatusText.getLocalBounds().width / 2,
                             gameStatusText.getLocalBounds().height / 2);
    gameStatusText.setPosition(640, 640);
    gameStatusText.setFillColor(sf::Color(0, 255, 0));
}

void Minesweeper::Board::markTile(int x, int y) {
    if (tiles[y][x].isMarked()) {
        markedTiles--;
    } else {
        markedTiles++;
    }
    tiles[y][x].toggleMark();
    if (tilesRevealed == width * height - mineCount) {
        winGame();
    }
}

void Minesweeper::Board::revealTile(int x, int y, bool recursive) {
    if (tiles[y][x].containsMine) {
        tiles[y][x].detonate();
        loseGame();
    } else {
        if (!tiles[y][x].isRevealed() && !tiles[y][x].isMarked()) {
            tiles[y][x].reveal();
            tilesRevealed++;
            if (recursive || tiles[y][x].nearbyMines == 0) {
                revealSafeNeighbours(x, y, true);
            }
            if (tilesRevealed == width * height - mineCount) {
                winGame();
            }
        } else {
            revealSafeNeighbours(x, y, false);
        }

    }
}

void Minesweeper::Board::draw() {
    window->clear();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[i][j].draw(&textureMap, window);
        }
    }
    window->draw(rsRestart);
    window->draw(rsMenu);
    window->draw(rsBorder);
    window->draw(restartText);
    window->draw(menuText);
    window->draw(gameStatusText);
    window->display();
}

void Minesweeper::Board::resetBoard() {
    gameStatusText.setString("");
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tiles[i][j].reset();
        }
    }
    tilesRevealed = 0;
    markedTiles = 0;
    gameStarted = false;
    finished = false;
}

void Minesweeper::Board::render() {
    if (window == nullptr) {
        exit(EXIT_FAILURE);
    } else {
        draw();
        bool hover;
        while (window->isOpen()) {
            sf::Event event;
            // handle menu exit (break out of render loop)
            if (exitToMenu) {
                window->clear();
                break;
            }
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == sf::Event::MouseMoved) {
                    hover = buttonHover(&event, &rsMenu, &menuText) ||
                            buttonHover(&event, &rsRestart, &restartText);
                    if (!hover) {
                        menuText.setFillColor(sf::Color(255, 255, 255));
                        restartText.setFillColor(sf::Color(255, 255, 255));
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (!finished) {
                        for (int i = 0; i < height; ++i) {
                            for (int j = 0; j < width; ++j) {
                                if (tiles[i][j].sprite.getGlobalBounds().contains(event.mouseButton.x,
                                                                                  event.mouseButton.y)) {
                                    if (event.mouseButton.button == sf::Mouse::Left) {
                                        if (!gameStarted) {
                                            placeMines(j, i);
                                            revealTile(j, i, true);

                                        } else {
                                            revealTile(j, i);

                                        }
                                    } else if (event.mouseButton.button == sf::Mouse::Right && gameStarted) {
                                        markTile(j, i);
                                    }
                                }
                            }
                        }
                    }
                    if (rsRestart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        resetBoard();

                    } else if (rsMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        exitToMenu = true;
                    }
                }
            }
            draw();

        }
    }
}

void Minesweeper::Board::loadTextures() {
    std::string states[14] = {"base", "mine", "flag", "explosion","loss", "0", "1", "2", "3", "4", "5", "6", "7", "8"};
    for (const auto &key: states) {
        textureMap[key] = sf::Texture();
        textureMap[key].loadFromFile(std::experimental::filesystem::current_path().string() +
                                     std::string(R"(\src\resources\)") + key +
                                     std::string(".png"));
    }
}
