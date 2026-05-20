#include "SatSolver.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

SatSolver::Result SatSolver::solve(int vars, const vector<vector<int>>& cls, double limit) {
    varCount = vars;
    clauses = &cls;
    value.assign(varCount + 1, -1);
    model.clear();
    timeLimit = limit;
    stopped = false;
    startTime = chrono::steady_clock::now();

    Result res = dfs();
    if (res == SAT) {
        model = value;
    }
    return res;
}

vector<int> SatSolver::getModel() const {
    return model;
}

bool SatSolver::timeIsOver() const {
    if (timeLimit <= 0) {
        return false;
    }
    double passed = chrono::duration<double>(chrono::steady_clock::now() - startTime).count();
    return passed > timeLimit;
}

SatSolver::Result SatSolver::dfs() {
    if (timeIsOver()) {
        stopped = true;
        return TIMEOUT;
    }

    if (!unit()) {
        if (stopped) {
            return TIMEOUT;
        }
        return UNSAT;
    }

    int v = chooseVar();
    if (v == 0) {
        return SAT;
    }

    vector<int> old = value;
    value[v] = 1;
    Result r1 = dfs();
    if (r1 == SAT || r1 == TIMEOUT) {
        return r1;
    }

    value = old;
    value[v] = 0;
    Result r2 = dfs();
    if (r2 == SAT || r2 == TIMEOUT) {
        return r2;
    }

    value = old;
    return UNSAT;
}

bool SatSolver::unit() {
    bool changed = true;
    int step = 0;
    while (changed) {
        if ((step & 31) == 0 && timeIsOver()) {
            stopped = true;
            return false;
        }
        step++;
        changed = false;

        for (const vector<int>& cl: *clauses) {
            bool ok = false;
            int freeCnt = 0;
            int lastLit = 0;

            for (int x: cl) {
                int val = litValue(x);
                if (val == 1) {
                    ok = true;
                    break;
                }
                if (val == -1) {
                    freeCnt++;
                    lastLit = x;
                }
            }

            if (ok) {
                continue;
            }
            if (freeCnt == 0) {
                return false;
            }
            if (freeCnt == 1) {
                int v = abs(lastLit);
                int need = lastLit > 0 ? 1 : 0;
                if (value[v] != -1 && value[v] != need) {
                    return false;
                }
                if (value[v] == -1) {
                    value[v] = need;
                    changed = true;
                }
            }
        }
    }
    return true;
}

int SatSolver::chooseVar() const {
    vector<int> score(varCount + 1, 0);
    bool allGood = true;

    for (const vector<int>& cl: *clauses) {
        bool ok = false;
        for (int x: cl) {
            if (litValue(x) == 1) {
                ok = true;
                break;
            }
        }
        if (ok) {
            continue;
        }
        allGood = false;
        for (int x: cl) {
            int v = abs(x);
            if (value[v] == -1) {
                score[v]++;
            }
        }
    }

    if (allGood) {
        return 0;
    }

    int best = 0;
    for (int i = 1; i <= varCount; i++) {
        if (value[i] == -1 && (best == 0 || score[i] > score[best])) {
            best = i;
        }
    }
    return best;
}

int SatSolver::litValue(int x) const {
    int v = abs(x);
    if (value[v] == -1) {
        return -1;
    }
    if (x > 0) {
        return value[v];
    }
    return 1 - value[v];
}
