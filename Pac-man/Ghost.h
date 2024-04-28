#pragma once
#include "Pacman.h"
#include <queue>
#include <stack>

class Ghost: public Character {
public:
    Ghost(sf::String texturePath, int row, int col): Character(texturePath, row, col) {};
    std::queue<std::pair<int, int>> setNextMoves(Pacman *pacman);
    void approachPacman();

private:
    std::stack<std::pair<int, int>> nextMoves;
};