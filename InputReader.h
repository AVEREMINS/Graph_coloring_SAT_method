#pragma once

#include "Graph.h"

class InputReader {
public:
    void read();
    Graph getGraph() const;
private:
    Graph graph;
};
