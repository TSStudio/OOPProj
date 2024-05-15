#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>

namespace sfSnake {
class Animation {
public:
    Animation(std::vector<float> init_values, std::vector<float> target_values, float duration);
    Animation();
    std::vector<float> current_values;
    void update(float timeDelta);
    bool finished = false;

private:
    float curve(float t);
    std::vector<float> init_values;
    std::vector<float> target_values;
    float duration;
    float timePassed = 0;
};
}  // namespace sfSnake

#endif