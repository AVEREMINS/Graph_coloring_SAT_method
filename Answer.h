#pragma once

#include <vector>
#include <string>

struct Answer {
    int colors = 0;
    int isOptimal = 0;
    double time = 0;
    std::string method;
    std::vector<int> color;
};
