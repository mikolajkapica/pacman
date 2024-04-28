#pragma once
#include <SFML/Graphics.hpp>

class Moneta {
public:
    Moneta();
    void setPosition(int x, int y);
    void draw(sf::RenderWindow& window);
private:
    sf::Texture texture;
    sf::Sprite sprite;
};