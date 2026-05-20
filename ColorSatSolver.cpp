#include "ColorSatSolver.h"
#include "CheckColor.h"
#include <algorithm>

using namespace std;

Answer ColorSatSolver::improve(const Graph& graph, const Answer& start, double limit, bool onlySat, const string& dimacsName) const {
    Answer best = start;
    int startK = start.colors;

    if (onlySat) {
        startK = min(startK, graph.n);
    }

    for (int k = startK - 1; k >= 1; k--) {
        long long vars = 1LL*graph.n*k;
        long long cls = graph.n + 1LL*graph.n*k*(k - 1)/2 + 1LL*graph.m*k;
        if (vars > 7000 || cls > 350000) {
            break;
        }

        if (!dimacsName.empty()) {
            SatFormula formula(graph, k);
            formula.saveDimacs(dimacsName);
        }

        bool timeout = false;
        Answer cur;
        bool ok = solveForK(graph, k, limit, cur, timeout);
        if (ok && checkColoring(graph, cur)) {
            best = cur;
            best.method = "sat";
            best.isOptimal = 0;
            continue;
        }
        if (timeout) {
            break;
        }
        best.isOptimal = 1;
        break;
    }

    return best;
}

bool ColorSatSolver::solveForK(const Graph& graph, int k, double limit, Answer& answer, bool& timeout) const {
    SatFormula formula(graph, k);
    SatSolver solver;
    SatSolver::Result result = solver.solve(formula.getVarCount(), formula.getClauses(), limit);
    timeout = result == SatSolver::TIMEOUT;

    if (result != SatSolver::SAT) {
        return false;
    }

    answer = answerFromModel(graph, k, formula, solver.getModel());
    return true;
}

Answer ColorSatSolver::answerFromModel(const Graph& graph, int k, const SatFormula& formula, const vector<int>& model) const {
    Answer answer;
    answer.color.assign(graph.n, 0);
    answer.colors = k;
    answer.method = "sat";

    for (int v = 0; v < graph.n; v++) {
        for (int c = 0; c < k; c++) {
            int id = formula.var(v, c);
            if (id < (int)model.size() && model[id] == 1) {
                answer.color[v] = c;
                break;
            }
        }
    }

    answer.colors = countColors(answer.color);
    return answer;
}
