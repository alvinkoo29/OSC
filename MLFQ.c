#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void findWaitingTime(int processes[], int n,int bt[], int wt[], int quantum)
{
	// Make a copy of bt[] to store remaining burst time
	int rem_bt[1000]={0};
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];

	int t = 0; // Current time

		// Goes through each processes sequentially
		for (int i = 0 ; i < n; i++)
		{
			// If process is still incomplete (has burst time)
			if (rem_bt[i] > 0)
			{

				if (rem_bt[i] > quantum)
				{
					// counter to calculate time taken for each process
					t += quantum;

					// reduces by allocated quantum time
					rem_bt[i] -= quantum;
				}

				// If remaining is less than quantum (last pass)
				else
				{
					// adds remaining time needed (less than quantum)
					t = t + rem_bt[i];

					// Waiting time is current time minus time used by this process
					wt[i] = t - bt[i];

					// The process is completed (burst time=0)
					rem_bt[i] = 0;
				}
            }
		}
        for (int i = 1; i < n ; i++)
        {
            // Add burst time of previous processes
            wt[i] = rem_bt[i-1] + wt[i-1];
        }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,int bt[], int wt[], int tat[])
{
	// calculating turnaround time
	for (int i = 0; i < n ; i++){
		tat[i] = bt[i] + wt[i];
	}
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],int quantum)
{
	int wt[1000]={0}, tat[1000]={0}, total_wt = 0, total_tat = 0,total_bt=0;

	// calculate waiting time
	findWaitingTime(processes, n, bt, wt, quantum);

	// calculate turn around time
	findTurnAroundTime(processes, n, bt, wt, tat);

	printf("Processes\t"  "Burst time\t"  "Waiting time\t"  "Turn around time\n");

	// Calculate total waiting time and total turn around time
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf(" %d\t\t %d\t\t %d \t\t %d\n",i+1,bt[i],wt[i],tat[i]);
		total_bt=total_bt+bt[i];
	}

	printf("Average waiting time= %.3f\n",(float)total_wt/n);
    printf("Average turn around time = %.3f\n",(float)total_tat/n);
    printf("Throughput time= %.3f\n",(float)total_bt/n);

}

// Driver code
int main()
{
	// process id's
	int i=0,quantum=0;
	printf("Enter number of processes: ");
	scanf("%d",&i);
	int processes[1000]={0},burst_time[1000]={0};
	if (i<1)
	{
	    printf("Input is not accepted");
	}
    else
    {
        for(int x=0;x<i;x++)
        {
            processes[x]=x+1;
            do
            {
            printf("Enter burst time of process %d: ",x+1);
            scanf("%d",&burst_time[x]);
            if (burst_time[x]<1)
                {
                    printf("Incorrect format (Please enter a non-negative digit)\n");

                }
            }while (burst_time[x]<1);
        }
    }
    printf("Please enter time quantum: ");
    scanf("%d",&quantum);
	if (i>0)
	{
	    findavgTime(processes, i, burst_time, quantum);
	}
	return 0;
}

