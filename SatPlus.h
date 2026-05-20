#pragma once

#include "Graph.h"
#include "Answer.h"
#include <vector>

class SatPlus {
public:
    std::vector<int> satAiOrder(const Graph& graph, int seed) const;
    Answer randomJump(const Graph& graph, const Answer& start, int seed, int cnt) const;
};
