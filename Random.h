#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <SFML/Graphics.hpp>
namespace sfSnake {
class Random {
public:
    static int randomInt(int min, int max);

    static float randomFloat(float min, float max);

    static sf::Vector2f randomPosition(float xMin, float xMax, float yMin, float yMax);
};
}  // namespace sfSnake
#endif