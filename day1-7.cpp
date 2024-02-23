#include<stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
};

// Function to perform SJF scheduling
void sjf_scheduling(struct Process processes[], int n) {
    // Sort processes based on burst time in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Display the order of execution
    printf("Order of execution: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].process_id);
    }
    printf("\n");

    // Calculate waiting time and turnaround time
    int waiting_time = 0;
    int turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        turnaround_time += processes[i].burst_time;
        printf("P%d -> Waiting Time: %d, Turnaround Time: %d\n", processes[i].process_id, waiting_time, turnaround_time);
        waiting_time += processes[i].burst_time;
    }

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = (float)waiting_time / n;
    float avg_turnaround_time = (float)turnaround_time / n;

    // Display average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time for each process
    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter the burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Perform SJF scheduling
    sjf_scheduling(processes, n);

    return 0;
}

