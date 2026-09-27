/*
    CPU SCHEDULING SIMULATOR
    -------------------------
    Simulates four classic CPU scheduling algorithms:
        1. First Come First Serve (FCFS)
        2. Shortest Job First (SJF - Non Preemptive)
        3. Priority Scheduling (Non Preemptive)
        4. Round Robin (with user given time quantum)

    For each algorithm the program calculates:
        - Completion Time (CT)
        - Turn Around Time (TAT = CT - Arrival Time)
        - Waiting Time  (WT = TAT - Burst Time)
        - Average TAT and Average WT

    Author : Anush Choudhary
    Reg No : 12407704
    Course : Summer Training / Internship (DSA in C++)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

// ---------- Process structure ----------
struct Process {
    int pid;
    int at;        // arrival time
    int bt;        // burst time
    int priority;  // lower number = higher priority
    int ct = 0;    // completion time
    int tat = 0;   // turnaround time
    int wt = 0;    // waiting time
    int remaining; // used for round robin
};

// ---------- Utility: print the result table ----------
void printTable(vector<Process> p) {
    cout << left;
    cout << "\n" << setw(6) << "PID" << setw(10) << "Arrival" << setw(10) << "Burst"
         << setw(10) << "Priority" << setw(12) << "Complete" << setw(10) << "TAT"
         << setw(10) << "WT" << "\n";
    cout << string(68, '-') << "\n";

    float totalTAT = 0, totalWT = 0;
    for (auto &pr : p) {
        cout << setw(6) << pr.pid << setw(10) << pr.at << setw(10) << pr.bt
             << setw(10) << pr.priority << setw(12) << pr.ct << setw(10) << pr.tat
             << setw(10) << pr.wt << "\n";
        totalTAT += pr.tat;
        totalWT += pr.wt;
    }
    cout << string(68, '-') << "\n";
    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time = " << (totalTAT / p.size()) << "\n";
    cout << "Average Waiting Time    = " << (totalWT / p.size()) << "\n";
}

// ---------- 1. FCFS ----------
void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) { return a.at < b.at; });

    int time = 0;
    for (auto &pr : p) {
        if (time < pr.at) time = pr.at;
        time += pr.bt;
        pr.ct = time;
        pr.tat = pr.ct - pr.at;
        pr.wt = pr.tat - pr.bt;
    }
    cout << "\n===== FCFS SCHEDULING =====\n";
    printTable(p);
}

// ---------- 2. SJF (Non-Preemptive) ----------
void sjf(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, minBT = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }
    cout << "\n===== SJF (NON-PREEMPTIVE) SCHEDULING =====\n";
    printTable(p);
}

// ---------- 3. Priority Scheduling (Non-Preemptive) ----------
void priorityScheduling(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
    }
    cout << "\n===== PRIORITY (NON-PREEMPTIVE) SCHEDULING =====\n";
    printTable(p);
}

// ---------- 4. Round Robin ----------
void roundRobin(vector<Process> p, int quantum) {
    int n = p.size();
    for (auto &pr : p) pr.remaining = pr.bt;

    sort(p.begin(), p.end(), [](Process a, Process b) { return a.at < b.at; });

    queue<int> q;
    vector<bool> inQueue(n, false);
    int time = 0, completed = 0;

    q.push(0);
    inQueue[0] = true;

    while (completed < n) {
        int idx = q.front(); q.pop();

        if (time < p[idx].at) time = p[idx].at;

        int run = min(quantum, p[idx].remaining);
        time += run;
        p[idx].remaining -= run;

        // enqueue any processes that arrived during this slice
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].at <= time && p[i].remaining > 0 && i != idx) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (p[idx].remaining > 0) {
            q.push(idx);
        } else {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        if (q.empty() && completed < n) {
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && p[i].remaining > 0) {
                    q.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
        }
    }
    cout << "\n===== ROUND ROBIN SCHEDULING (Quantum = " << quantum << ") =====\n";
    printTable(p);
}

// ---------- main ----------
int main() {
    int n;
    cout << "===============================================\n";
    cout << "        CPU SCHEDULING SIMULATOR (C++)\n";
    cout << "===============================================\n";
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "\nProcess P" << i + 1 << "\n";
        cout << "  Arrival Time : "; cin >> processes[i].at;
        cout << "  Burst Time   : "; cin >> processes[i].bt;
        cout << "  Priority (1 = highest) : "; cin >> processes[i].priority;
    }

    int choice;
    do {
        cout << "\n---------------------------------------------\n";
        cout << "Choose Scheduling Algorithm:\n";
        cout << "1. FCFS\n";
        cout << "2. SJF (Non-Preemptive)\n";
        cout << "3. Priority Scheduling (Non-Preemptive)\n";
        cout << "4. Round Robin\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fcfs(processes); break;
            case 2: sjf(processes); break;
            case 3: priorityScheduling(processes); break;
            case 4: {
                int q;
                cout << "Enter Time Quantum: ";
                cin >> q;
                roundRobin(processes, q);
                break;
            }
            case 5: cout << "\nExiting simulator. Goodbye!\n"; break;
            default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 5);

    return 0;
}
