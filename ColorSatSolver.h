#pragma once

#include "Graph.h"
#include "Answer.h"
#include "SatFormula.h"
#include "SatSolver.h"
#include <string>

class ColorSatSolver {
public:
    Answer improve(const Graph& graph, const Answer& start, double limit, bool onlySat, const std::string& dimacsName) const;
    bool solveForK(const Graph& graph, int k, double limit, Answer& answer, bool& timeout) const;
private:
    Answer answerFromModel(const Graph& graph, int k, const SatFormula& formula, const std::vector<int>& model) const;
};
