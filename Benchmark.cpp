#include "Benchmark.h"

using namespace sfSnake;

Benchmark global_benchmark = Benchmark(true);

Benchmark::Benchmark(bool done) {
    is_done = done;
    tick_ = Clock::now();
}

void Benchmark::in_section(std::string sectionName) {
    if (is_done) {
        return;
    }
    for (int i = 0; i < sections_stack_.size(); i++) {
        result += "  ";
    }
    result += sectionName + ":\n";
    sections_stack_.push(std::make_pair(sectionName, Clock::now()));
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
    fsec fs = Clock::now() - section.second;
    result += std::format("{}: {:.3f}ms\n", section.first, fs.count() * 1000);
}

void Benchmark::print_result() {
    if (is_done) {
        return;
    }
    is_done = true;
    fsec fs = Clock::now() - tick_;
    result += std::format("Total: {:.3f}ms\n", fs.count() * 1000);
    printf("%s", result.c_str());
}