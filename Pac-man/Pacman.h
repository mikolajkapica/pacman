#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Character.h"


class Pacman: public Character {
public:
    Pacman(sf::String texturePath, int row, int col) : Character(texturePath, row, col) {};
private:
};


