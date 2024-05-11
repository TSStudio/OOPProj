#include "Benchmark.h"
#include <ctime>

using namespace sfSnake;

Benchmark global_benchmark = Benchmark(true);

Benchmark::Benchmark(bool done) {
    is_done = done;
    tick_ = clock();
}

void Benchmark::in_section(std::string sectionName) {
    if (is_done) {
        return;
    }
    for (int i = 0; i < sections_stack_.size(); i++) {
        result += "  ";
    }
    result += sectionName + ":\n";
    sections_stack_.push(std::make_pair(sectionName, clock() * 1000.0 / CLOCKS_PER_SEC));
}

void Benchmark::out_section() {
    if (is_done) {
        return;
    }
    if (sections_stack_.empty()) {
        return;
    }
    auto section = sections_stack_.top();
    sections_stack_.pop();
    for (int i = 0; i < sections_stack_.size(); i++) {
        result += "  ";
    }
    result += section.first + ": " + std::to_string(clock() * 1000.0 / CLOCKS_PER_SEC - section.second) + "ms\n";
}

void Benchmark::print_result() {
    if (is_done) {
        return;
    }
    is_done = true;
    result += "Total: " + std::to_string((clock() - tick_) * 1000.0 / CLOCKS_PER_SEC) + "ms\n";
    printf("%s", result.c_str());
}