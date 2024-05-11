#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;
extern Game game;

float velocity = game.TimePerFrame.asSeconds() * 10;

double Direction::get_dx() {
    return cos(degree);
}
double Direction::get_dy() {
    return sin(degree);
}

Snake::Snake(bool player) : direction_(Direction()), hit_(false) {
    if (player) {
        this->player = true;
        pickupBuffer_.loadFromFile("Sounds/pickup.wav");
        pickupSound_.setBuffer(pickupBuffer_);
        pickupSound_.setVolume(30);

        dieBuffer_.loadFromFile("Sounds/die.wav");
        dieSound_.setBuffer(dieBuffer_);
        dieSound_.setVolume(50);
    } else {
        this->player = false;
    }
    score_ = InitialSize;
}

void Snake::initNodes(float init_x, float init_y) {
    for (int i = 0; i < Snake::InitialSize; ++i) {
        nodes_.push_back(SnakeNode(sf::Vector2f(
                                       init_x,
                                       init_y + (SnakeNode::Height * i)),
                                   i == 0, player ? sf::Color::Green : sf::Color::Red));
    }
    for (int i = 0; i <= 6 * Snake::InitialSize; ++i) {
        float x = init_x;
        float y = init_y + (SnakeNode::Height * i / 6);
        nodePositions_.push_back(NodePosition{sf::Vector2f(x, y), 0});
    }
}

void Snake::initNodes() {
    initNodes(Game::Width / 2, Game::Height / 2);
}

void Snake::handleInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(game.window_);
        sf::Vector2f headPos = nodes_[0].getPosition();
        double dx = mousePos.x - headPos.x;
        double dy = mousePos.y - headPos.y;
        direction_.degree = atan2(dy, dx);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        accelerating_ = true;
    } else {
        accelerating_ = false;
    }
}

void Snake::update(sf::Time delta) {
    score_ -= 0.002;
    if (accelerating_ && score_ > 2) {
        score_ -= 0.002;
    }
    sync_length();
    move();
    checkEdgeCollisions();

    //checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits) {
    decltype(fruits.begin()) toRemove = fruits.end();

    for (auto it = fruits.begin(); it != fruits.end(); ++it) {
        if (nodes_[0].getRadius() + it->getRadius() > sqrt(pow(nodes_[0].getPosition().x - it->getPosition().x, 2) + pow(nodes_[0].getPosition().y - it->getPosition().y, 2)))
            toRemove = it;
    }

    if (toRemove != fruits.end()) {
        if (player)
            pickupSound_.play();
        for (int i = 0; i < fruits[toRemove - fruits.begin()].nutrition; ++i)
            grow();
        fruits.erase(toRemove);
    }
}

void Snake::grow() {
    score_ += 1;
}

void Snake::melt() {
    score_ -= 1;
}

void Snake::sync_length() {
    int length = floor(score_);
    if (length == 0) {
        die();
        return;
    }
    while (nodes_.size() > length) {
        nodes_.pop_back();
        for (int i = 0; i < 6; ++i) {
            nodePositions_.pop_back();
        }
    }
    while (nodes_.size() < length) {
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - direction_.get_dx() * SnakeNode::Height, nodes_[nodes_.size() - 1].getPosition().y - direction_.get_dy() * SnakeNode::Height), false, player ? sf::Color::Green : sf::Color::Red));
        for (int i = 1; i <= 6; ++i) {
            float x = nodes_[nodes_.size() - 1].getPosition().x - direction_.get_dx() * SnakeNode::Height * i / 6;
            float y = nodes_[nodes_.size() - 1].getPosition().y - direction_.get_dy() * SnakeNode::Height * i / 6;
            nodePositions_.push_back(NodePosition{sf::Vector2f(x, y), direction_.degree});
        }
    }
}

unsigned Snake::getSize() const {
    return nodes_.size();
}

bool Snake::hit() const {
    return hit_;
}

// void Snake::checkSelfCollisions() {
//     SnakeNode& headNode = nodes_[0];
//     return;

//     for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i) {
//         if (headNode.getRadius() + nodes_[i].getRadius() > sqrt(pow(headNode.getPosition().x - nodes_[i].getPosition().x, 2) + pow(headNode.getPosition().y - nodes_[i].getPosition().y, 2))) {
//             dieSound_.play();
//             sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
//             hitSelf_ = true;
//         }
//     }
// }

void Snake::checkOtherSnakeCollisions(Snake& otherSnake) {
    SnakeNode& headNode = nodes_[0];
    SnakeNode& otherHeadNode = otherSnake.nodes_[0];

    for (decltype(otherSnake.nodes_.size()) i = 0; i < otherSnake.nodes_.size(); ++i) {
        if (headNode.getRadius() + otherSnake.nodes_[i].getRadius() > sqrt(pow(headNode.getPosition().x - otherSnake.nodes_[i].getPosition().x, 2) + pow(headNode.getPosition().y - otherSnake.nodes_[i].getPosition().y, 2))) {
            die();
        }
    }
}

void Snake::checkEdgeCollisions() {
    SnakeNode& headNode = nodes_[0];
    if (headNode.getPosition().x <= 0 || headNode.getPosition().x >= Game::Width || headNode.getPosition().y <= 0 || headNode.getPosition().y >= Game::Height) {
        die();
    }
}

void Snake::die() {
    hit_ = true;
    if (player) {
        dieSound_.play();
        sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
    }
}

void Snake::move() {
    float head_x = nodePositions_[0].position.x + direction_.get_dx() * SnakeNode::Width * velocity;
    float head_y = nodePositions_[0].position.y + direction_.get_dy() * SnakeNode::Width * velocity;
    double head_degree = direction_.degree;
    nodePositions_.push_front(NodePosition{sf::Vector2f(head_x, head_y), head_degree});
    if (accelerating_ && score_ > 2) {
        float head_x = nodePositions_[0].position.x + direction_.get_dx() * SnakeNode::Width * velocity;
        float head_y = nodePositions_[0].position.y + direction_.get_dy() * SnakeNode::Width * velocity;
        double head_degree = direction_.degree;
        nodePositions_.push_front(NodePosition{sf::Vector2f(head_x, head_y), head_degree});
    }
    for (decltype(nodes_.size()) i = nodes_.size() - 1;; --i) {
        nodes_[i].setPosition(nodePositions_[i * 6]);
        //nodes_[i].shape_.setRotation(nodePositions_[i * 6].degree * 180 / 3.1415926);
        //TODO rotation
        //printf("Pos of Node %lu is %f %f\n", i, nodes_[i].getPosition().x, nodes_[i].getPosition().y);
        if (i == 0) break;
    }
    nodePositions_.pop_back();
}

void Snake::doAIMovement(sf::Vector2f target) {
    sf::Vector2f headPos = nodes_[0].getPosition();
    double dx = target.x - headPos.x;
    double dy = target.y - headPos.y;
    direction_.degree = atan2(dy, dx);
}

void Snake::render(sf::RenderWindow& window) {
    for (auto& node : nodes_)
        node.render(window);
}