#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
const std::vector<sf::Color> avail_bg_color = {sf::Color(240, 240, 240), sf::Color(15, 15, 15), sf::Color(69, 21, 14)};
const std::vector<sf::Color> avail_grid_color = {sf::Color(240, 240, 240), sf::Color(15, 15, 15), sf::Color(69, 21, 14)};
class Background {
public:
    Background();
    Background(const Background& old);
    void render(sf::RenderWindow& window);
    void switch_bg_color();
    void switch_grid_color();
    void switch_grid();
    void updateScore(float _score);

private:
    sf::RectangleShape background_;
    sf::Color bg_color;
    sf::Color grid_color;
    sf::Color score_color = sf::Color(120, 120, 120);
    std::vector<sf::RectangleShape> grid_horizontal;
    std::vector<sf::RectangleShape> grid_vertical;
    sf::Font font_;
    sf::Text score;
    bool grid_on = false;
    unsigned bg_color_idx = 0;
    unsigned grid_color_idx = 1;
};
}  // namespace sfSnake

#endif