#include "SatPlus.h"
#include "CheckColor.h"
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

vector<int> SatPlus::satAiOrder(const Graph& graph, int seed) const {
    vector<int> order(graph.n);
    iota(order.begin(), order.end(), 0);
    mt19937 rnd(seed);
    shuffle(order.begin(), order.end(), rnd);

    for (int i = 0; i < graph.n; i++) {
        int j = rnd()%graph.n;
        if (graph.degree[order[j]] > graph.degree[order[i]]) {
            swap(order[i], order[j]);
        }
    }

    return order;
}

Answer SatPlus::randomJump(const Graph& graph, const Answer& start, int seed, int cnt) const {
    Answer cur = start;
    if (graph.n == 0) {
        return cur;
    }

    mt19937 rnd(seed);
    int k = max(1, start.colors);

    for (int step = 0; step < cnt; step++) {
        int v = rnd()%graph.n;
        int old = cur.color[v];
        int c = rnd()%k;
        cur.color[v] = c;

        bool good = true;
        for (int to: graph.g[v]) {
            if (cur.color[to] == c) {
                good = false;
                break;
            }
        }

        if (!good) {
            cur.color[v] = old;
        }
    }

    cur.colors = countColors(cur.color);
    cur.method = "sat_plus";
    return cur;
}
