#pragma once

#include "Graph.h"
#include <vector>
#include <string>

class SatFormula {
public:
    SatFormula();
    SatFormula(const Graph& graph, int k);
    int getVarCount() const;
    int getClauseCount() const;
    int var(int v, int c) const;
    const std::vector<std::vector<int>>& getClauses() const;
    void saveDimacs(const std::string& name) const;
private:
    int n;
    int k;
    int varCount;
    std::vector<std::vector<int>> clauses;
};
