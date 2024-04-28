#include <iostream>
#include "Board.h"
#include "Moneta.h"
#include "Pacman.h"

extern int map[MAP_WIDTH][MAP_HEIGHT];

Board::Board(Pacman *pacman, Ghost *ghosts) : pacman(pacman), ghosts(ghosts) {
    wallTexture.loadFromFile("Wall1.png");
    corridorTexture.loadFromFile("corridor.png");

    wallSprite.setTexture(wallTexture);
    corridorSprite.setTexture(corridorTexture);

    lost = false;
    won = false;

    // copy inverted map to initialize coinMap
    for (int i = 0; i < MAP_WIDTH; ++i) {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            coinMap[i][j] = 1 - map[i][j];
        }
    }

    // delete coins near start of Pacman
    coinMap[10][0] = 0;
    coinMap[10][1] = 0;

    // delete coins in the center rectangle
    coinMap[7][10] = 0;
    coinMap[8][9] = 0;
    coinMap[9][9] = 0;
    coinMap[8][10] = 0;
    coinMap[9][10] = 0;
    coinMap[8][11] = 0;
    coinMap[9][11] = 0;

    coinEatenCounter = 0;
}

bool Board::hasCoin(int row, int col) const {
    return coinMap[row][col] == 1;
}

void Board::draw(sf::RenderWindow& window) {
    sf::sleep(sf::milliseconds(100));
    if (!lost) {
        for (int i = 0; i < 4; ++i) {
            if (pacman->getSprite().getGlobalBounds().intersects(ghosts[i].getSprite().getGlobalBounds())) {
                lost = true;
            }
        }
        pacman->move(pacman->getDirection(), pacman->getFutureDirection());
        for (int i = 0; i < 4; ++i) {
            ghosts[i].approachPacman();
        }
    }


    int pacmanX = static_cast<int>(pacman->getSprite().getPosition().x/TITLE_SIZE);
    int pacmanY = static_cast<int>(pacman->getSprite().getPosition().y/TITLE_SIZE);
    if (coinMap[pacmanY][pacmanX] == 1) {
        coinEatenCounter++;
    }
    coinMap[pacmanY][pacmanX] = 0;

    // draw the map and coins
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            // map
            if (map[i][j] == 1) {
                wallSprite.setPosition(j * TITLE_SIZE, i * TITLE_SIZE);
                window.draw(wallSprite);
            } else {
                corridorSprite.setPosition(j * TITLE_SIZE, i * TITLE_SIZE);
                window.draw(corridorSprite);
            }
            // coins
            if (hasCoin(i, j)) {
                Moneta moneta;
                moneta.setPosition(j * TITLE_SIZE, i * TITLE_SIZE);
                moneta.draw(window);
            }
        }
    }

    pacman->draw(window);
    for (int i = 0; i < 4; ++i)
        ghosts[i].draw(window);

    // end game
    if (coinEatenCounter == 211) {
        int side = 400;
        sf::RectangleShape rectangle(sf::Vector2f(side, side));
        rectangle.setOrigin(side/2, side/2);
        rectangle.setPosition(MAP_WIDTH * TITLE_SIZE / 2, MAP_HEIGHT * TITLE_SIZE / 2);
        rectangle.setFillColor(sf::Color::White);
        sf::Text victoryMessage;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // Error handling if the font fails to load
        }
        victoryMessage.setFont(font);
        victoryMessage.setCharacterSize(64);
        victoryMessage.setString("You Win!");
        sf::FloatRect textBounds = victoryMessage.getLocalBounds();
        victoryMessage.setOrigin(textBounds.width / 2, textBounds.height / 2 + 15);
        victoryMessage.setPosition(MAP_WIDTH * TITLE_SIZE / 2, MAP_HEIGHT * TITLE_SIZE / 2);
        victoryMessage.setFillColor(sf::Color::Red);

        window.draw(rectangle);
        window.draw(victoryMessage);
    }

    if (lost) {
        int side = 400;
        sf::RectangleShape rectangle(sf::Vector2f(side, side));
        rectangle.setOrigin(side/2, side/2);
        rectangle.setPosition(MAP_WIDTH * TITLE_SIZE / 2, MAP_HEIGHT * TITLE_SIZE / 2);
        rectangle.setFillColor(sf::Color::White);
        sf::Text loseMessage;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // Error handling if the font fails to load
        }
        loseMessage.setFont(font);
        loseMessage.setCharacterSize(64);
        loseMessage.setString("GAMEOVER!");
        sf::FloatRect textBounds = loseMessage.getLocalBounds();
        loseMessage.setOrigin(textBounds.width / 2, textBounds.height / 2 + 15);
        loseMessage.setPosition(MAP_WIDTH * TITLE_SIZE / 2, MAP_HEIGHT * TITLE_SIZE / 2);
        loseMessage.setFillColor(sf::Color::Red);

        window.draw(rectangle);
        window.draw(loseMessage);
    }
}

void Board::setLost(bool lost) {
    Board::lost = lost;
}

void Board::setWon(bool won) {
    Board::won = won;
}
