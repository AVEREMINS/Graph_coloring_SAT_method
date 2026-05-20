#include "GreedyColor.h"
#include "CheckColor.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <random>

using namespace std;

Answer GreedyColor::solve(const Graph& graph, int tries) const {
    Answer best = dsatur(graph);

    Answer cur = greedyOrder(graph, degreeOrder(graph));
    if (cur.colors < best.colors) {
        best = cur;
    }

    for (int i = 0; i < tries; i++) {
        cur = greedyOrder(graph, randomOrder(graph, 17 + i*31));
        if (cur.colors < best.colors) {
            best = cur;
        }
    }

    best.method = "greedy";
    best.colors = countColors(best.color);
    best.isOptimal = 0;
    return best;
}

Answer GreedyColor::dsatur(const Graph& graph) const {
    int n = graph.n;
    vector<int> color(n, -1);
    vector<set<int>> used(n);

    for (int step = 0; step < n; step++) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (color[i] != -1) {
                continue;
            }
            if (v == -1) {
                v = i;
                continue;
            }
            if ((int)used[i].size() > (int)used[v].size()) {
                v = i;
            } else if ((int)used[i].size() == (int)used[v].size() && graph.degree[i] > graph.degree[v]) {
                v = i;
            }
        }

        vector<int> bad(n + 1, 0);
        for (int to: graph.g[v]) {
            if (color[to] != -1) {
                bad[color[to]] = 1;
            }
        }

        int c = 0;
        while (bad[c]) {
            c++;
        }
        color[v] = c;

        for (int to: graph.g[v]) {
            if (color[to] == -1) {
                used[to].insert(c);
            }
        }
    }

    Answer answer;
    answer.color = color;
    answer.colors = countColors(color);
    answer.method = "dsatur";
    return answer;
}

Answer GreedyColor::greedyOrder(const Graph& graph, vector<int> order) const {
    int n = graph.n;
    vector<int> color(n, -1);

    for (int v: order) {
        vector<int> bad(n + 1, 0);
        for (int to: graph.g[v]) {
            if (color[to] != -1) {
                bad[color[to]] = 1;
            }
        }
        int c = 0;
        while (bad[c]) {
            c++;
        }
        color[v] = c;
    }

    Answer answer;
    answer.color = color;
    answer.colors = countColors(color);
    answer.method = "greedyOrder";
    return answer;
}

vector<int> GreedyColor::degreeOrder(const Graph& graph) const {
    vector<int> order(graph.n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (graph.degree[a] != graph.degree[b]) {
            return graph.degree[a] > graph.degree[b];
        }
        return a < b;
    });
    return order;
}

vector<int> GreedyColor::randomOrder(const Graph& graph, int seed) const {
    vector<int> order = degreeOrder(graph);
    mt19937 rnd(seed);
    int block = 10;
    for (int i = 0; i < (int)order.size(); i += block) {
        int r = min((int)order.size(), i + block);
        shuffle(order.begin() + i, order.begin() + r, rnd);
    }
    return order;
}
