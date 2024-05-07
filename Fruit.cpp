#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Random.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position, int nutrition) {
    this->nutrition = nutrition;
    shape_.setPosition(position);
    shape_.setRadius(Fruit::Radius);
    switch (nutrition) {
        case 0:
            shape_.setFillColor(Random::randomInt(0, 1) ? sf::Color::Black : sf::Color(185, 122, 87));
            break;
        case 1:
            shape_.setFillColor(sf::Color::Green);
            break;
        case 2:
            shape_.setFillColor(sf::Color::Blue);
            break;
        case 3:
            shape_.setFillColor(sf::Color::Red);
            break;
        default:
            shape_.setFillColor(sf::Color::White);
            break;
    }
}

void Fruit::render(sf::RenderWindow& window) {
    window.draw(shape_);
}

float Fruit::getRadius() const {
    return Fruit::Radius;
}

sf::Vector2f Fruit::getPosition() const {
    return shape_.getPosition();
}