#include "Random.h"

using namespace sfSnake;
int Random::randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

float Random::randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mt);
}

sf::Vector2f Random::randomPosition(float xMin, float xMax, float yMin, float yMax) {
    return sf::Vector2f(randomFloat(xMin, xMax), randomFloat(yMin, yMax));
}