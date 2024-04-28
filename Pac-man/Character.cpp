#include <SFML/System/String.hpp>
#include "Character.h"
#include "Board.h"

extern int map[MAP_WIDTH][MAP_HEIGHT];

Character::Character(sf::String texturePath, int row, int col) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setOrigin(16, 16);
    sprite.setPosition(col * TITLE_SIZE + TITLE_SIZE/2, row * TITLE_SIZE + TITLE_SIZE/2);
    direction = 0;
    futureDirection = 0;
}

void Character::move(int direction, int futureDirection) {
    int characterX = static_cast<int>(sprite.getPosition().x/TITLE_SIZE);
    int characterY = static_cast<int>(sprite.getPosition().y/TITLE_SIZE);
    if (futureDirection != direction) {
        switch (futureDirection) {
            case 0: {
                if (map[characterY][characterX + 1] == 0) {
                    sprite.setPosition(sprite.getPosition().x + TITLE_SIZE, sprite.getPosition().y);
                    sprite.setRotation(0);
                    this->direction = futureDirection;
                    return;
                }
                break;
            }
            case 1: {
                if (map[characterY - 1][characterX] == 0) {
                    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - TITLE_SIZE);
                    sprite.setRotation(270);
                    this->direction = futureDirection;
                    return;
                }
                break;
            }
            case 2: {
                if (map[characterY][characterX - 1] == 0) {
                    sprite.setPosition(sprite.getPosition().x - TITLE_SIZE, sprite.getPosition().y);
                    sprite.setRotation(180);
                    this->direction = futureDirection;
                    return;
                }
                break;
            }
            case 3: {
                if (map[characterY + 1][characterX] == 0) {
                    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + TITLE_SIZE);
                    sprite.setRotation(90);
                    this->direction = futureDirection;
                    return;
                }
                break;
            }

        }
    }
    switch (direction) {
        case 0: {
            if (map[characterY][characterX + 1] == 0) {
                sprite.setPosition(sprite.getPosition().x + TITLE_SIZE, sprite.getPosition().y);
                sprite.setRotation(0);
            }
            if (characterX == 20 && characterY == 10) {
                sprite.setPosition(TITLE_SIZE/2, sprite.getPosition().y);
            }
            break;
        }
        case 1: {
            if (map[characterY - 1][characterX] == 0) {
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - TITLE_SIZE);
                sprite.setRotation(270);
            }
            break;
        }
        case 2: {
            if (map[characterY][characterX - 1] == 0) {
                sprite.setPosition(sprite.getPosition().x - TITLE_SIZE, sprite.getPosition().y);
                sprite.setRotation(180);
            }
            if (characterX == 0 && characterY == 10) {
                sprite.setPosition(MAP_WIDTH * TITLE_SIZE - TITLE_SIZE / 2, sprite.getPosition().y);
            }
            break;
        }
        case 3: {
            if (map[characterY + 1][characterX] == 0) {
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + TITLE_SIZE);
                sprite.setRotation(90);
            }
            break;
        }
        default: {}
    }
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

int Character::getDirection() {
    return direction;
}

void Character::setDirection(int direction) {
    this->direction = direction;
}

int Character::getFutureDirection() {
    return futureDirection;
}

void Character::setFutureDirection(int futureDirection) {
    Character::futureDirection = futureDirection;
}

sf::Sprite Character::getSprite() {
    return sprite;
}
