#pragma once

#include <vector>
#include <chrono>

class SatSolver {
public:
    enum Result {
        UNSAT = 0,
        SAT = 1,
        TIMEOUT = 2
    };

    Result solve(int vars, const std::vector<std::vector<int>>& cls, double limit);
    std::vector<int> getModel() const;
private:
    int varCount;
    const std::vector<std::vector<int>>* clauses;
    std::vector<int> value;
    std::vector<int> model;
    std::chrono::steady_clock::time_point startTime;
    double timeLimit;
    bool stopped;

    bool timeIsOver() const;
    Result dfs();
    bool unit();
    int chooseVar() const;
    int litValue(int x) const;
};
