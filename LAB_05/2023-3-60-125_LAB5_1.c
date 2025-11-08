#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    
    int size, avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &size);
    printf("\n");

    int bt[size], wt[size], tat[size];

    for (int i = 0; i < size; i++)
    {
        printf("Burst Time of Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;

    for (int i = 1; i < size; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
    
    for (int i = 0; i < size; i++)
    {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];

        printf("\n%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }
    
    avg_wt = avg_wt / size;
    avg_tat = avg_tat / size;

    printf("\n\nAverage Waiting Time: %d", avg_wt);
    printf("\nAverage Turnaround Time: %d\n", avg_tat);

    return 0;

}
