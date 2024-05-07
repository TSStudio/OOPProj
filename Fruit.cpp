#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position) {
    shape_.setPosition(position);
    shape_.setRadius(Fruit::Radius);
    shape_.setFillColor(sf::Color::Red);
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