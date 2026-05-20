#pragma once

#include <vector>
#include <utility>

struct Graph {
    int n = 0;
    int m = 0;
    std::vector<std::pair<int, int>> edges;
    std::vector<std::vector<int>> g;
    std::vector<int> degree;
};
