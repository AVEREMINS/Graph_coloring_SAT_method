#include "InputReader.h"
#include <iostream>
#include <algorithm>

using namespace std;

void InputReader::read() {
    int n, m;
    cin >> n >> m;
    graph.n = n;
    graph.m = m;
    graph.g.assign(n, vector<int>());
    graph.degree.assign(n, 0);
    graph.edges.clear();

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a < 0 || b < 0 || a >= n || b >= n || a == b) {
            continue;
        }
        graph.edges.push_back({a, b});
        graph.g[a].push_back(b);
        graph.g[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        sort(graph.g[i].begin(), graph.g[i].end());
        graph.g[i].erase(unique(graph.g[i].begin(), graph.g[i].end()), graph.g[i].end());
        graph.degree[i] = (int)graph.g[i].size();
    }

    graph.edges.clear();
    for (int i = 0; i < n; i++) {
        for (int j: graph.g[i]) {
            if (i < j) {
                graph.edges.push_back({i, j});
            }
        }
    }
    graph.m = (int)graph.edges.size();
}

Graph InputReader::getGraph() const {
    return graph;
}
