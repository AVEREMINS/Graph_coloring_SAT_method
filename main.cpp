#include <chrono>
#include <iostream>
#include <string>
#include "InputReader.h"
#include "OutputWriter.h"
#include "GreedyColor.h"
#include "ColorSatSolver.h"
#include "CheckColor.h"

using namespace std;

int main(int argc, char** argv) {
    bool text = false;
    bool onlyGreedy = false;
    bool onlySat = false;
    double satLimit = 1.5;
    int tries = 5;
    string dimacsName = "";

    for (int i = 1; i < argc; i++) {
        string s = argv[i];
        if (s == "--text") {
            text = true;
        } else if (s == "--greedy") {
            onlyGreedy = true;
        } else if (s == "--sat") {
            onlySat = true;
        } else if (s == "--limit" && i + 1 < argc) {
            satLimit = stod(argv[++i]);
        } else if (s == "--tries" && i + 1 < argc) {
            tries = stoi(argv[++i]);
        } else if (s == "--dimacs" && i + 1 < argc) {
            dimacsName = argv[++i];
        }
    }

    InputReader input;
    input.read();
    Graph graph = input.getGraph();

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

    GreedyColor greedySolver;
    Answer answer = greedySolver.solve(graph, tries);

    if (!onlyGreedy) {
        ColorSatSolver satSolver;
        answer = satSolver.improve(graph, answer, satLimit, onlySat, dimacsName);
        if (answer.method == "sat") {
            answer.isOptimal = answer.isOptimal;
        }
    }

    chrono::steady_clock::time_point finishTime = chrono::steady_clock::now();
    double passed = chrono::duration<double>(finishTime - startTime).count();
    answer.time = passed;

    if (!checkColoring(graph, answer)) {
        return 1;
    }

    OutputWriter output;
    output.print(answer, text);

    return 0;
}
