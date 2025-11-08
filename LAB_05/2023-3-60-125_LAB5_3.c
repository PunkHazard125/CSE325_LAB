#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    
    int quantum, size, avg_wt = 0, avg_tat = 0, finish_counter = 0;

    printf("Enter value of time quantum: ");
    scanf("%d", &quantum);

    printf("Enter number of processes: ");
    scanf("%d", &size);
    printf("\n");

    int bt[size], wt[size], tat[size], rem[size];

    for (int i = 0; i < size; i++)
    {
        printf("Burst Time of Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    while (1)
    {
        for (int i = 0; i < size; i++)
        {
            int actual_time;

            if (rem[i] > 0)
            {
                if (rem[i] > quantum)
                {
                    rem[i] -= quantum;
                    actual_time = quantum;
                }
                else
                {
                    actual_time = rem[i];
                    rem[i] = 0;
                    finish_counter++;

                    if (finish_counter == size) break;
                }

                for (int j = 0; j < size; j++)
                {
                    if (j != i && rem[j] != 0)
                    {
                        wt[j] += actual_time;
                    }
                }
            }
        }

        if (finish_counter == size)
        {
            break;
        }
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
