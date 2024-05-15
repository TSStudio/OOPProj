#include "Animation.h"
#include <cmath>

using namespace sfSnake;

Animation::Animation(std::vector<float> init_values, std::vector<float> target_values, float duration) {
    this->init_values = init_values;
    this->target_values = target_values;
    this->duration = duration;
    this->current_values = init_values;
}
Animation::Animation() {
    this->init_values = {};
    this->target_values = {};
    this->duration = 0;
    this->current_values = {};
}

void Animation::update(float timeDelta) {
    if (finished) return;
    timePassed += timeDelta;
    if (timePassed >= duration) {
        timePassed = duration;
        finished = true;
    }
    float t = timePassed / duration;
    for (int i = 0; i < current_values.size(); i++) {
        current_values[i] = init_values[i] + (target_values[i] - init_values[i]) * curve(t);
    }
}

float Animation::curve(float t) {
    if (t < 0) return 0;
    if (t > 1) return 1;
    return 0.5 - 0.5 * cos(t * M_PI);
}