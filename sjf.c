#include <stdio.h>
#include <limits.h>
#define MAXPROCESS 10
struct Process {
    int id;
    int at; 
    int bt; 
    int rt; 
    int ct; 
};

int main() {
    int time = 0;
    int completed = 0;
    int n;
    int totalWT = 0;
    int totalTAT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAXPROCESS];

   
    for (int i = 0; i < n; i++) {
        processes[i].id = i;

        printf("Enter the arrival time of P%d: ", i);
        scanf("%d", &processes[i].at);
        printf("Enter the burst time of P%d: ", i);
        scanf("%d", &processes[i].bt);

        processes[i].rt = processes[i].bt; 
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");


    while (completed < n) {
        int minRT = INT_MAX;
        int shortest = -1;

        
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].rt > 0 && processes[i].rt < minRT) {
                minRT = processes[i].rt;
                shortest = i;
            }
        }

       
        if (shortest == -1) {
            time++;
            continue;
        }

    
        processes[shortest].rt--;
        time++;


        if (processes[shortest].rt == 0) {
            completed++;
            processes[shortest].ct = time;
            int tat = processes[shortest].ct - processes[shortest].at;
            int wt = tat - processes[shortest].bt; 

            totalWT += wt;
            totalTAT += tat;

           
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                processes[shortest].id,
                processes[shortest].at,
                processes[shortest].bt,
                processes[shortest].ct,
                tat,
                wt);
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT / n);
    
    return 0;
}
