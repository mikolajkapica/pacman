#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"


int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0,1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0,1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
        {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0,1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,1},
        {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,1},
        {1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,1},
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0,1},
        {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0,1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0,1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,1},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0,1, 0, 1, 0, 1,1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1,0,1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TITLE_SIZE, MAP_HEIGHT * TITLE_SIZE), "Pac-man");
    Pacman pacman("pacman.png", 10, 0);
    Ghost yellowGhost("yellow_ghost.png", 8, 9);
    Ghost redGhost("red_ghost.png", 9, 9);
    Ghost pinkGhost("pink_ghost.png", 8, 11);
    Ghost blueGhost("blue_ghost.png", 9, 11);
    Ghost ghosts[4] = {yellowGhost, redGhost, pinkGhost, blueGhost};
    Board board(&pacman, ghosts);

    int loopCounter = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                int pacmanX = static_cast<int>(pacman.getSprite().getPosition().x/TITLE_SIZE);
                int pacmanY = static_cast<int>(pacman.getSprite().getPosition().y/TITLE_SIZE);
                if (event.key.code == sf::Keyboard::Right) {
                    if (map[pacmanY][pacmanX + 1] == 0) {
                        pacman.setDirection(0);
                    }
                    pacman.setFutureDirection(0);
                } else if (event.key.code == sf::Keyboard::Up) {
                    if (map[pacmanY - 1][pacmanX] == 0) {
                        pacman.setDirection(1);
                    }
                    pacman.setFutureDirection(1);
                } else if (event.key.code == sf::Keyboard::Left) {
                    if (map[pacmanY][pacmanX - 1] == 0) {
                        pacman.setDirection(2);
                    }
                    pacman.setFutureDirection(2);
                } else if (event.key.code == sf::Keyboard::Down) {
                    if (map[pacmanY + 1][pacmanX] == 0) {
                        pacman.setDirection(3);
                    }
                    pacman.setFutureDirection(3);
                }
            }
        }
        if (loopCounter == 16) loopCounter = 0;
        window.clear();
        int ghostNumber = loopCounter / 4;
        ghosts[ghostNumber].setNextMoves(&pacman);

        board.draw(window);
        window.display();
        loopCounter++;
    }
    return 0;
}



