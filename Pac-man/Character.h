#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class  Character {
public:
    Character(sf::String texturePath, int row, int col);
    void move(int direction, int futureDirection);
    int getDirection();
    void setDirection(int direction);
    int getFutureDirection();
    void setFutureDirection(int futureDirection);
    sf::Sprite getSprite();
    void draw(sf::RenderWindow &window);
protected:
    sf::Texture texture;
    sf::Sprite sprite;
private:
    int direction;
    int futureDirection;
};