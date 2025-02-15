//round-robin
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, waitingTime, turnaroundTime;
};

void roundRobin(vector<Process>& processes, int timeQuantum) {
    queue<int> readyQueue;
    int currentTime = 0, completed = 0;
    int n = processes.size();

    vector<bool> inQueue(n, false);

    while (completed < n) {
        // Add newly arrived processes to the queue
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();
        inQueue[idx] = false;

        int timeUsed = min(timeQuantum, processes[idx].remainingTime);
        currentTime += timeUsed;
        processes[idx].remainingTime -= timeUsed;

        if (processes[idx].remainingTime == 0) {
            completed++;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
        } else {
            readyQueue.push(idx);
            inQueue[idx] = true;
        }
    }

    // Print results
    cout << "ID \t Arrival \t Burst \t Completion \t Turnaround \t Waiting\n";
    for (const auto& p : processes) {
        cout << p.id << "\t " << p.arrivalTime << "\t\t " << p.burstTime
             << "\t\t " << p.completionTime << "\t\t " << p.turnaroundTime
             << "\t\t " << p.waitingTime << "\n";
    }
}

int main() {
    int n, timeQuantum;
    cout << "Enter number of processes and time quantum: ";
    cin >> n >> timeQuantum;

    vector<Process> processes(n);
    cout << "Enter arrival times: ";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter burst times: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    roundRobin(processes, timeQuantum);

    return 0;
}
