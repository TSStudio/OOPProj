#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <stack>
#include <string>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::_V2::system_clock::time_point time_point;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

namespace sfSnake {
class Benchmark {
public:
    Benchmark(bool done = false);
    void in_section(std::string sectionName);
    void out_section();
    void print_result();

private:
    time_point tick_;
    std::stack<std::pair<std::string, time_point>> sections_stack_;
    std::string result;
    bool is_done = false;
};
}  // namespace sfSnake

#endif