#include <stdio.h>

int main() {
    int n, tq, bt[20], rem[20], wt[20], tat[20], ct[20];
    int time = 0, done;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i]; // remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Loop until all processes are done
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = 0; // At least one process is pending
                if (rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    ct[i] = time; // completion time
                    rem[i] = 0;
                }
            }
        }
    } while (!done);

    // Calculate TAT and WT
    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i];          // AT = 0
        wt[i] = tat[i] - bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    // Print results
    printf("\nProcess\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}