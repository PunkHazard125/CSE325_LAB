#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void swap(int array[][3], int i, int j) {

    int temp0 = array[i][0];
    int temp1 = array[i][1];
    int temp2 = array[i][2];

    array[i][0] = array[j][0];
    array[i][1] = array[j][1];
    array[i][2] = array[j][2];

    array[j][0] = temp0;
    array[j][1] = temp1;
    array[j][2] = temp2;

}

void sort_process(int array[][3], int size) {

    for (int i = 0; i < size - 1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (array[j][2] > array[j + 1][2]) 
            {
                swap(array, j, j + 1);
            }
        }
    }

}

int main() {
    
    int size, avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &size);
    printf("\n");

    int process[size][3], wt[size], tat[size];

    for (int i = 0; i < size; i++)
    {
        printf("Burst Time & Priority of Process %d: ", i + 1);
        scanf("%d %d", &process[i][1], &process[i][2]);
        process[i][0] = i + 1;
    }

    sort_process(process, size);

    wt[0] = 0;

    for (int i = 1; i < size; i++)
    {
        wt[i] = wt[i - 1] + process[i - 1][1];
    }

    printf("\n\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time");
    
    for (int i = 0; i < size; i++)
    {
        tat[i] = wt[i] + process[i][1];
        avg_wt += wt[i];
        avg_tat += tat[i];

        printf("\n%d\t\t%d\t\t%d\t\t%d", process[i][0], process[i][1], wt[i], tat[i]);
    }
    
    avg_wt = avg_wt / size;
    avg_tat = avg_tat / size;

    printf("\n\nAverage Waiting Time: %d", avg_wt);
    printf("\nAverage Turnaround Time: %d\n", avg_tat);

    return 0;

}
