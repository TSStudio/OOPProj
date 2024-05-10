#include "Background.h"
#include "Game.h"

using namespace sfSnake;

Background::Background() {
    background_ = sf::RectangleShape(sf::Vector2f(Game::Width, Game::Height));
    bg_color = avail_bg_color[bg_color_idx];
    background_.setFillColor(avail_bg_color[bg_color_idx]);
    grid_color = avail_grid_color[grid_color_idx];

    int grid_size = 20;
    for (int i = 0; i * grid_size < Game::Width; ++i) {
        grid_horizontal.push_back(sf::RectangleShape(sf::Vector2f(1, Game::Height)));
        grid_horizontal[i].setFillColor(grid_color);
        grid_horizontal[i].setPosition(i * grid_size, 0);
    }

    for (int i = 0; i * grid_size < Game::Height; ++i) {
        grid_vertical.push_back(sf::RectangleShape(sf::Vector2f(Game::Width, 1)));
        grid_vertical[i].setFillColor(grid_color);
        grid_vertical[i].setPosition(0, i * grid_size);
    }
}

void Background::switch_bg_color() {
    bg_color_idx = (bg_color_idx + 1) % avail_bg_color.size();
    bg_color = avail_bg_color[bg_color_idx];
    background_.setFillColor(avail_bg_color[bg_color_idx]);
}

void Background::switch_grid_color() {
    grid_color_idx = (grid_color_idx + 1) % avail_grid_color.size();
    grid_color = avail_grid_color[grid_color_idx];
    for (auto& line : grid_horizontal) {
        line.setFillColor(grid_color);
    }
    for (auto& line : grid_vertical) {
        line.setFillColor(grid_color);
    }
}

void Background::switch_grid() {
    grid_on = !grid_on;
}

void Background::render(sf::RenderWindow& window) {
    window.draw(background_);
    if (grid_on) {
        for (auto& line : grid_horizontal) {
            window.draw(line);
        }
        for (auto& line : grid_vertical) {
            window.draw(line);
        }
    }
}