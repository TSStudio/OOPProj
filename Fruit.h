#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
class Fruit {
public:
    Fruit(sf::Vector2f position = sf::Vector2f(0, 0), int nutrition = 1, sf::Vector2f speed = sf::Vector2f(0, 0));

    void render(sf::RenderWindow& window);

    float getRadius() const;
    sf::Vector2f getPosition() const;
    int nutrition;
    void move(float dt = 1.0 / 60);

private:
    sf::CircleShape shape_;
    sf::Vector2f speed_;

    static const float Radius;
};
}  // namespace sfSnake

#endif