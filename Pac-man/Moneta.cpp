#include <iostream>
#include "Moneta.h"

Moneta::Moneta() {
    if (!texture.loadFromFile("token.png")) {
        std::cout << "Failed to load token.png" << std::endl;
    }
    sprite.setTexture(texture);
}

void Moneta::setPosition(int x, int y) {
    sprite.setPosition(x - 32, y - 32);
}

void Moneta::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}