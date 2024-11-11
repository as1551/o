#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n_processes, n_resources;
    int Allocation[MAX_PROCESSES][MAX_RESOURCES];
    int Maximum[MAX_PROCESSES][MAX_RESOURCES];
    int Need[MAX_PROCESSES][MAX_RESOURCES];
    int Available[MAX_RESOURCES];
    bool Finish[MAX_PROCESSES] = {false};
    int SafeSequence[MAX_PROCESSES];
    int count = 0;

    // Input number of processes and resources
    printf("Enter the number of processes (<= %d): ", MAX_PROCESSES);
    scanf("%d", &n_processes);
    printf("Enter the number of resources (<= %d): ", MAX_RESOURCES);
    scanf("%d", &n_resources);

    // Input Available vector
    printf("Enter the Available Resources:\n");
    for (int i = 0; i < n_resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &Available[i]);
    }

    // Input Maximum matrix
    printf("Enter the Maximum Resource Matrix:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < n_resources; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &Maximum[i][j]);
        }
    }

    // Input Allocation matrix
    printf("Enter the Allocation Resource Matrix:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < n_resources; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &Allocation[i][j]);
        }
    }

    // Calculate Need matrix
    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_resources; j++) {
            Need[i][j] = Maximum[i][j] - Allocation[i][j];
        }
    }

    // Display Need matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < n_resources; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }

    // Banker's Algorithm
    while (count < n_processes) {
        bool found = false;
        for (int i = 0; i < n_processes; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < n_resources; j++) {
                    if (Need[i][j] > Available[j])
                        break;
                }
                if (j == n_resources) {
                    // The process's needs can be satisfied
                    for (int k = 0; k < n_resources; k++)
                        Available[k] += Allocation[i][k];
                    SafeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return 1;
        }
    }

    // Display Safe Sequence
    printf("\nSystem is in a safe state.\nSafe Sequence is: ");
    for (int i = 0; i < n_processes; i++) {
        printf("P%d", SafeSequence[i]);
        if (i != n_processes -1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}

