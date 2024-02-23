#include<stdio.h>
#include<stdlib.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int priority;
    int remaining_time;
};

// Function to perform Priority scheduling
void priority_scheduling(struct Process processes[], int n) {
    int total_execution_time = 0;

    // Calculate total execution time for all processes
    for (int i = 0; i < n; i++) {
        total_execution_time += processes[i].burst_time;
    }

    // Array to store the execution order
    int *execution_order = (int*)malloc(sizeof(int) * total_execution_time);
    int current_time = 0;

    // Execute processes
    while (current_time < total_execution_time) {
        int selected_process = -1;
        int highest_priority = INT_MAX;

        // Select the process with the highest priority
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].priority < highest_priority) {
                selected_process = i;
                highest_priority = processes[i].priority;
            }
        }

        // Update execution order
        execution_order[current_time] = selected_process;

        // Decrement remaining time for the selected process
        processes[selected_process].remaining_time--;

        // Move to the next time unit
        current_time++;
    }

    // Display the order of execution
    printf("Order of execution: ");
    for (int i = 0; i < total_execution_time; i++) {
        printf("P%d ", execution_order[i] + 1);
    }
    printf("\n");

    // Calculate waiting time and turnaround time
    int waiting_time = 0;
    int turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        waiting_time += total_execution_time - processes[i].burst_time;
        turnaround_time += total_execution_time;
        printf("P%d -> Waiting Time: %d, Turnaround Time: %d\n", i + 1, total_execution_time - processes[i].burst_time, total_execution_time);
    }

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = (float)waiting_time / n;
    float avg_turnaround_time = (float)turnaround_time / n;

    // Display average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    // Free dynamically allocated memory
    free(execution_order);
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
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Perform Priority scheduling
    priority_scheduling(processes, n);

    return 0;
}

