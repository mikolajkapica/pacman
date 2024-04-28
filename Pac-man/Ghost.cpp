#include <queue>
#include "Ghost.h"
#include "Pacman.h"
#include <iostream>
#include <iomanip>
#include <stack>

extern int map[MAP_WIDTH][MAP_HEIGHT];
/*
 * Run BFS to find the shortest path from the ghost to the pacman. Z tym algorytmem pomagał mi kolega
  */
std::queue<std::pair<int, int>> Ghost::setNextMoves(Pacman *pacman) {
    // get the position of pacman and the ghost
    int pacmanX = static_cast<int>(pacman->getSprite().getPosition().x / TITLE_SIZE);
    int pacmanY = static_cast<int>(pacman->getSprite().getPosition().y / TITLE_SIZE);
    int ghostX = static_cast<int>(sprite.getPosition().x / TITLE_SIZE);
    int ghostY = static_cast<int>(sprite.getPosition().y / TITLE_SIZE);

    // initialize distance and prev
    int distance[MAP_WIDTH][MAP_HEIGHT];
    // prev is used to store the direction of the next move
    // 0: left, 1: right, 2: up, 3: down
    int prev[MAP_WIDTH][MAP_HEIGHT];
    for (int i = 0; i < MAP_WIDTH; ++i) {
        for (int j = 0; j < MAP_HEIGHT; ++j) {
            distance[i][j] = -1;
            prev[i][j] = -1;
        }
    }
    distance[ghostY][ghostX] = 0;

    // run BFS
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(ghostX, ghostY));


    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;
        if (x == pacmanX && y == pacmanY) {
            break;
        }
        // go left
        if (x > 0 && map[y][x - 1] == 0 && distance[y][x - 1] == -1) {
            distance[y][x - 1] = distance[y][x] + 1;
            prev[y][x - 1] = 0;
            q.push(std::make_pair(x - 1, y));
        }
        // go right
        if (x < MAP_WIDTH - 1 && map[y][x + 1] == 0 && distance[y][x + 1] == -1) {
            distance[y][x + 1] = distance[y][x] + 1;
            prev[y][x + 1] = 1;
            q.push(std::make_pair(x + 1, y));
        }
        // go up
        if (y > 0 && map[y - 1][x] == 0 && distance[y - 1][x] == -1) {

            distance[y - 1][x] = distance[y][x] + 1;
            prev[y - 1][x] = 2;
            q.push(std::make_pair(x, y - 1));
        }
        // go down
        if (y < MAP_HEIGHT - 1 && map[y + 1][x] == 0 && distance[y + 1][x] == -1) {
            distance[y + 1][x] = distance[y][x] + 1;
            prev[y + 1][x] = 3;
            q.push(std::make_pair(x, y + 1));
        }
    }

    std::stack<std::pair<int, int>> nextMoves;
    std::pair<int, int> current = std::make_pair(pacmanX, pacmanY);
    nextMoves.push(current);
    while (current.first != ghostX || current.second != ghostY) {
        int x = current.first;
        int y = current.second;
        switch (prev[y][x]) {
            case 0:
                current = std::make_pair(x + 1, y);
                break;
            case 1:
                current = std::make_pair(x - 1, y);
                break;
            case 2:
                current = std::make_pair(x, y + 1);
                break;
            case 3:
                current = std::make_pair(x, y - 1);
                break;
            default:
                std::cout << "error" << std::endl;
                break;
        }
        nextMoves.push(current);
    }
    this->nextMoves = nextMoves;
}

void Ghost::approachPacman() {
    if (nextMoves.empty()) {
        return;
    }
    std::pair<int, int> nextMove = nextMoves.top();
    nextMoves.pop();
    int x = nextMove.first;
    int y = nextMove.second;
    sprite.setPosition(x * TITLE_SIZE + TITLE_SIZE/2, y * TITLE_SIZE + TITLE_SIZE/2);
}