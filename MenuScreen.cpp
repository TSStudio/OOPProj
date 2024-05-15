#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen() {
    bgMusic_.openFromFile("Music/menu_music.wav");
    bgMusic_.setLoop(true);
    bgMusic_.play();
    base = Game::Height / 2 + 80 - lineHeight;
    selectedItemIndex_ = 0;

    font_.loadFromFile("Fonts/arial.ttf");

    text_.setFont(font_);
    text_.setString("Singleplayer");
    text2_.setFont(font_);
    text2_.setString("Multiplayer");
    text3_.setFont(font_);
    text3_.setString("Exit");

    text_.setCharacterSize(30);
    text2_.setCharacterSize(30);
    text3_.setCharacterSize(30);

    snakeText_.setFont(font_);
    snakeText_.setString("Snake!");
    snakeText_.setFillColor(sf::Color::Green);
    snakeText_.setCharacterSize(64);
    snakeText_.setStyle(sf::Text::Bold);

    selection_.setSize(sf::Vector2f(250, 36));
    selection_.setFillColor(sf::Color::Green);
    selection_.setOrigin(125, 18);

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

    sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
    snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
                         snakeTextBounds.top + snakeTextBounds.height / 2);
    snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window) {
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
            //todo: multiplayer
        } else if (selectedItemIndex_ == 2)
            window.close();
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        key_enter_pressed = false;
    }
}

void MenuScreen::update(sf::Time delta) {
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

    static bool movingLeft = false;
    static bool movingRight = true;

    if (movingRight) {
        snakeText_.rotate(delta.asSeconds());

        if (static_cast<int>(snakeText_.getRotation()) == 10) {
            movingRight = false;
            movingLeft = true;
        }
    }

    if (movingLeft) {
        snakeText_.rotate(-delta.asSeconds());

        if (static_cast<int>(snakeText_.getRotation()) == (360 - 10)) {
            movingLeft = false;
            movingRight = true;
        }
    }
}

void MenuScreen::render(sf::RenderWindow& window) {
    window.draw(selection_);
    window.draw(text_);
    window.draw(text2_);
    window.draw(text3_);
    window.draw(snakeText_);
}