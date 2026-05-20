#include "CheckColor.h"
#include <algorithm>

using namespace std;

int countColors(const vector<int>& color) {
    int ans = 0;
    for (int x: color) {
        ans = max(ans, x + 1);
    }
    return ans;
}

bool checkColoring(const Graph& graph, const Answer& answer) {
    if ((int)answer.color.size() != graph.n) {
        return false;
    }
    for (int i = 0; i < graph.n; i++) {
        if (answer.color[i] < 0 || answer.color[i] >= answer.colors) {
            return false;
        }
    }
    for (auto e: graph.edges) {
        if (answer.color[e.first] == answer.color[e.second]) {
            return false;
        }
    }
    return true;
}
