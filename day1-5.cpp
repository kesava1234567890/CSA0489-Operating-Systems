#include<stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int priority;
};

// Function to perform Priority Scheduling
void priority_scheduling(struct Process processes[], int n) {
    int total_time = 0;
    int completed_processes = 0;

    // Loop until all processes are completed
    while (completed_processes < n) {
        int highest_priority_index = -1;
        int highest_priority = 9999;  // Initialize with a large value

        // Find the process with the highest priority among the waiting processes
        for (int i = 0; i < n; i++) {
            if (processes[i].burst_time > 0 && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        // Execute the process with the highest priority
        if (highest_priority_index != -1) {
            printf("Time %d: Process P%d\n", total_time + 1, processes[highest_priority_index].process_id);
            processes[highest_priority_index].burst_time--;

            // Check if the process is completed
            if (processes[highest_priority_index].burst_time == 0) {
                completed_processes++;
            }

            total_time++;
        }
    }

    // Calculate waiting time and turnaround time
    int waiting_time = 0;
    int turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        waiting_time += total_time - processes[i].burst_time;
        turnaround_time += total_time;
    }

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = (float)waiting_time / n;
    float avg_turnaround_time = (float)turnaround_time / n;

    // Display average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time and priority for each process
    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter the burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the priority for process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform Priority Scheduling
    priority_scheduling(processes, n);

    return 0;
}

