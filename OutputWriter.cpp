#include "OutputWriter.h"
#include <iostream>
#include <iomanip>

using namespace std;

void OutputWriter::print(const Answer& answer, bool text) const {
    if (!text) {
        cout << answer.colors << " " << answer.isOptimal << "\n";
        for (int i = 0; i < (int)answer.color.size(); i++) {
            cout << answer.color[i];
            if (i + 1 < (int)answer.color.size()) {
                cout << ' ';
            }
        }
        cout << "\n";
        return;
    }

    cout << "Colors: " << answer.colors << "\n";
    cout << "Optimal: " << answer.isOptimal << "\n";
    cout << "Method: " << answer.method << "\n";
    cout << fixed << setprecision(5);
    cout << "Time: " << answer.time << "\n";
    cout << "Coloring:\n";
    for (int i = 0; i < (int)answer.color.size(); i++) {
        cout << answer.color[i];
        if (i + 1 < (int)answer.color.size()) {
            cout << ' ';
        }
    }
    cout << "\n";
}
