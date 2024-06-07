#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Fruit.h"
#include "Random.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position, int nutrition, sf::Vector2f speed) {
    this->nutrition = nutrition;
    speed_ = speed;
    shape_.setRadius(Fruit::Radius);
    shape_.setOrigin(Fruit::Radius, Fruit::Radius);
    shape_.setPosition(position);
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

void Fruit::move(float dt) {
    shape_.move(speed_.x * dt, speed_.y * dt);
    if (shape_.getPosition().x < 0) {
        shape_.setPosition(shape_.getPosition().x + 2 * (0 - shape_.getPosition().x), shape_.getPosition().y);
        speed_.x = -speed_.x;
    }
    if (shape_.getPosition().x > Game::Width) {
        shape_.setPosition(shape_.getPosition().x - 2 * (shape_.getPosition().x - Game::Width), shape_.getPosition().y);
        speed_.x = -speed_.x;
    }
    if (shape_.getPosition().y < 0) {
        shape_.setPosition(shape_.getPosition().x, shape_.getPosition().y + 2 * (0 - shape_.getPosition().y));
        speed_.y = -speed_.y;
    }
    if (shape_.getPosition().y > Game::Height) {
        shape_.setPosition(shape_.getPosition().x, shape_.getPosition().y - 2 * (shape_.getPosition().y - Game::Height));
        speed_.y = -speed_.y;
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