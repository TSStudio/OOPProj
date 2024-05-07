#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
class Fruit {
public:
    Fruit(sf::Vector2f position = sf::Vector2f(0, 0), int nutrition = 1);

    void render(sf::RenderWindow& window);

    float getRadius() const;
    sf::Vector2f getPosition() const;
    int nutrition;

private:
    sf::CircleShape shape_;

    static const float Radius;
};
}  // namespace sfSnake

#endif