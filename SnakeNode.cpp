#include <SFML/Graphics.hpp>

#include "SnakeNode.h"
#include "Benchmark.h"

using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

extern Benchmark global_benchmark;

SnakeNode::SnakeNode(sf::Vector2f position, bool head, sf::Color color)
    : position_(position) {
    shape_.setPosition(position_);
    shape_.setFillColor(sf::Color::Black);
    shape_.setSize(sf::Vector2f(SnakeNode::Width / 2, SnakeNode::Height));
    shape_.setOrigin(SnakeNode::Width / 4, SnakeNode::Height / 2);

    innerShape_.setPosition(position_);
    innerShape_.setFillColor(color);
    innerShape_.setRadius(SnakeNode::Width * 0.495);
    innerShape_.setOrigin(SnakeNode::Width * 0.99 / 2, SnakeNode::Height * 0.99 / 2);

    if (head) {
        if (texture_.loadFromFile("Textures/head.png")) {
            head_ = true;
            sprite_ = sf::Sprite(texture_);
            sprite_.setTexture(texture_, true);
            sprite_.setOrigin(sf::Vector2f(7.5f, 7.5f));
        }
    }
}

SnakeNode::SnakeNode(const SnakeNode& old) {
    position_ = old.position_;
    shape_ = old.shape_;
    innerShape_ = old.innerShape_;
    degree_ = old.degree_;
    sprite_ = old.sprite_;
    head_ = old.head_;
    texture_.loadFromFile("Textures/head.png");
    sprite_.setTexture(texture_, true);
}

void SnakeNode::setPosition(sf::Vector2f position) {
    position_ = position;
    shape_.setPosition(position_);
    innerShape_.setPosition(position_);
    sprite_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    shape_.setPosition(position_);
    innerShape_.setPosition(position_);
}

void SnakeNode::setPosition(NodePosition nodePosition) {
    position_ = nodePosition.position;
    shape_.setPosition(position_);
    innerShape_.setPosition(position_);
    degree_ = nodePosition.degree;
    shape_.setRotation(degree_ / 3.1415927 * 180);
    sprite_.setPosition(position_);
    sprite_.setRotation(degree_ / 3.1415927 * 180);
}

void SnakeNode::move(float xOffset, float yOffset) {
    position_.x += xOffset;
    position_.y += yOffset;
    shape_.setPosition(position_);
    innerShape_.setPosition(position_);
    sprite_.setPosition(position_);
}

float SnakeNode::getRadius() const {
    return SnakeNode::Width * 0.99 / 2;
}

sf::Vector2f SnakeNode::getPosition() const {
    return position_;
}

void SnakeNode::render(sf::RenderWindow& window) {
    if (head_) {
        global_benchmark.in_section("SnakeNode::render::head");
        window.draw(sprite_);
        global_benchmark.out_section();
    } else {
        global_benchmark.in_section("SnakeNode::render::body");
        global_benchmark.in_section("SnakeNode::render::body::innerShape");
        window.draw(innerShape_);
        global_benchmark.out_section();
        global_benchmark.in_section("SnakeNode::render::body::shape");
        window.draw(shape_);
        global_benchmark.out_section();
        global_benchmark.out_section();
    }
}