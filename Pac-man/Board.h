#pragma once
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include "Ghost.h"

const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 21;
const int TITLE_SIZE = 32;

class Pacman;
class Ghost;

class Board {
public:
    Board(Pacman* pacman, Ghost ghosts[4]);
    void draw(sf::RenderWindow& window);
    bool hasCoin(int row, int col) const;

    void setLost(bool lost);

    void setWon(bool won);

private:
    sf::Texture wallTexture;
    sf::Texture corridorTexture;
    sf::Sprite wallSprite;
    sf::Sprite corridorSprite;
    int coinMap[MAP_WIDTH][MAP_HEIGHT]{};
    int coinEatenCounter;
    Pacman* pacman;
    Ghost* ghosts;
    bool lost;
    bool won;
};