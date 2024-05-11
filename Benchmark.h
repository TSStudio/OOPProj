#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <stack>
#include <string>

namespace sfSnake {
class Benchmark {
public:
    Benchmark(bool done = false);
    void in_section(std::string sectionName);
    void out_section();
    void print_result();

private:
    unsigned long long tick_;
    std::stack<std::pair<std::string, float>> sections_stack_;
    std::string result;
    bool is_done = false;
};
}  // namespace sfSnake

#endif