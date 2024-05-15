#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score) {
    font_.loadFromFile("Fonts/arial.ttf");
    textsc_.setFont(font_);
    textsc_.setString("Your score: " + std::to_string(score) + "!");
    textsc_.setFillColor(sf::Color::Red);

    sf::FloatRect textScBounds = textsc_.getLocalBounds();
    textsc_.setOrigin(textScBounds.left + textScBounds.width / 2,
                      textScBounds.top + textScBounds.height / 2);
    textsc_.setPosition(Game::Width / 2, Game::Height / 2);

    base = Game::Height / 2 + 80 - lineHeight;
    selectedItemIndex_ = 0;

    text_.setFont(font_);
    text_.setString("Retry");
    text2_.setFont(font_);
    text2_.setString("Menu");
    text3_.setFont(font_);
    text3_.setString("Exit");

    text_.setCharacterSize(30);
    text2_.setCharacterSize(30);
    text3_.setCharacterSize(30);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, base);

    sf::FloatRect text2Bounds = text2_.getLocalBounds();
    text2_.setOrigin(text2Bounds.left + text2Bounds.width / 2,
                     text2Bounds.top + text2Bounds.height / 2);
    text2_.setPosition(Game::Width / 2, base + lineHeight);

    sf::FloatRect text3Bounds = text3_.getLocalBounds();
    text3_.setOrigin(text3Bounds.left + text3Bounds.width / 2,
                     text3Bounds.top + text3Bounds.height / 2);
    text3_.setPosition(Game::Width / 2, base + lineHeight * 2);

    selection_.setPosition(Game::Width / 2, base);

    selection_.setSize(sf::Vector2f(250, 36));
    selection_.setFillColor(sf::Color::Green);
    selection_.setOrigin(125, 18);
}

void GameOverScreen::handleInput(sf::RenderWindow& window) {
    static bool key_up_pressed = false, key_down_pressed = false, key_enter_pressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !key_up_pressed) {
        key_up_pressed = true;
        if (selectedItemIndex_ > 0)
            selectedItemIndex_--;
        else
            selectedItemIndex_ = 2;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        key_up_pressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !key_down_pressed) {
        key_down_pressed = true;
        if (selectedItemIndex_ < 2)
            selectedItemIndex_++;
        else
            selectedItemIndex_ = 0;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        key_down_pressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !key_enter_pressed) {
        key_enter_pressed = true;
        if (selectedItemIndex_ == 0)
            Game::ScreenPtr = std::make_shared<GameScreen>();
        else if (selectedItemIndex_ == 1) {
            Game::ScreenPtr = std::make_shared<MenuScreen>();
        } else if (selectedItemIndex_ == 2)
            window.close();
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        key_enter_pressed = false;
    }
}

void GameOverScreen::update(sf::Time delta) {
    if (selectedItemIndex_ != animatedItemIndex_ && !performingAnimation_) {
        performingAnimation_ = true;
        animation_ = Animation({(float)base + animatedItemIndex_ * lineHeight}, {(float)base + selectedItemIndex_ * lineHeight}, 0.2);
        animatedItemIndex_ = selectedItemIndex_;
    }
    if (performingAnimation_) {
        animation_.update(delta.asSeconds());
        selection_.setPosition(Game::Width / 2, animation_.current_values[0]);
        if (animation_.finished) {
            performingAnimation_ = false;
        }
    }
}

void GameOverScreen::render(sf::RenderWindow& window) {
    window.draw(textsc_);
    window.draw(selection_);
    window.draw(text_);
    window.draw(text2_);
    window.draw(text3_);
}