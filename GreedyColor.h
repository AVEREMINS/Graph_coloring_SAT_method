#pragma once

#include "Graph.h"
#include "Answer.h"
#include <vector>

class GreedyColor {
public:
    Answer solve(const Graph& graph, int tries) const;
private:
    Answer dsatur(const Graph& graph) const;
    Answer greedyOrder(const Graph& graph, std::vector<int> order) const;
    std::vector<int> degreeOrder(const Graph& graph) const;
    std::vector<int> randomOrder(const Graph& graph, int seed) const;
};
