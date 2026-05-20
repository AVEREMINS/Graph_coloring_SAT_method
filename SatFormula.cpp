#include "SatFormula.h"
#include <fstream>

using namespace std;

SatFormula::SatFormula() {
    n = 0;
    k = 0;
    varCount = 0;
}

SatFormula::SatFormula(const Graph& graph, int colorCount) {
    n = graph.n;
    k = colorCount;
    varCount = n*k;
    clauses.clear();

    for (int v = 0; v < n; v++) {
        vector<int> cur;
        for (int c = 0; c < k; c++) {
            cur.push_back(var(v, c));
        }
        clauses.push_back(cur);
    }

    for (int v = 0; v < n; v++) {
        for (int c1 = 0; c1 < k; c1++) {
            for (int c2 = c1 + 1; c2 < k; c2++) {
                clauses.push_back({-var(v, c1), -var(v, c2)});
            }
        }
    }

    for (auto e: graph.edges) {
        for (int c = 0; c < k; c++) {
            clauses.push_back({-var(e.first, c), -var(e.second, c)});
        }
    }
}

int SatFormula::getVarCount() const {
    return varCount;
}

int SatFormula::getClauseCount() const {
    return (int)clauses.size();
}

int SatFormula::var(int v, int c) const {
    return v*k + c + 1;
}

const vector<vector<int>>& SatFormula::getClauses() const {
    return clauses;
}

void SatFormula::saveDimacs(const string& name) const {
    ofstream out(name);
    out << "p cnf " << varCount << " " << clauses.size() << "\n";
    for (const vector<int>& cl: clauses) {
        for (int x: cl) {
            out << x << " ";
        }
        out << "0\n";
    }
}
