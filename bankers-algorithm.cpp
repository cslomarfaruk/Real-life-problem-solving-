//bankers-algorithm
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_RESOURCES = 10;

struct Banker {
    int numProcesses;
    int numResources;
    vector<vector<int>> max;
    vector<vector<int>> allocation;
    vector<vector<int>> need;
    vector<int> available;

    void input() {
        cout << "Enter the number of processes: ";
        cin >> numProcesses;
        cout << "Enter the number of resources: ";
        cin >> numResources;

        max.resize(numProcesses, vector<int>(numResources));
        allocation.resize(numProcesses, vector<int>(numResources));
        need.resize(numProcesses, vector<int>(numResources));
        available.resize(numResources);

        cout << "Enter the Max Matrix:\n";
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                cin >> max[i][j];
            }
        }

        cout << "Enter the Allocation Matrix:\n";
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                cin >> allocation[i][j];
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }

        cout << "Enter the Available Resources:\n";
        for (int i = 0; i < numResources; i++) {
            cin >> available[i];
        }
    }

    bool isSafe() {
        vector<bool> finished(numProcesses, false);
        vector<int> work = available;
        vector<int> safeSequence;

        while (safeSequence.size() < numProcesses) {
            bool progress = false;

            for (int i = 0; i < numProcesses; i++) {
                if (!finished[i]) {
                    bool canAllocate = true;

                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }

                    if (canAllocate) {
                        for (int j = 0; j < numResources; j++) {
                            work[j] += allocation[i][j];
                        }
                        safeSequence.push_back(i);
                        finished[i] = true;
                        progress = true;
                    }
                }
            }

            if (!progress) {
                cout << "The system is in an unsafe state.\n";
                return false;
            }
        }

        cout << "The system is in a safe state.\n";
        cout << "Safe Sequence: ";
        for (int i : safeSequence) {
            cout << "P" << i << " ";
        }
        cout << endl;
        return true;
    }
};

int main() {
    Banker banker;
    banker.input();
    banker.isSafe();
    return 0;
}
