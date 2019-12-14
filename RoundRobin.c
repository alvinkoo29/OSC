#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void findWaitingTime(int processes[], int n,int bt[], int wt[], int quantum)
{
	// Make a copy of bt[] to store remaining burst time
	int* rem_bt;
	rem_bt = (int*)calloc(n, sizeof(int));

	for (int i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];

	int t = 0; // Current time

	// Loop all the processes until complete
	while (1)
	{
		bool done = true;

		// Goes through each processes sequentially
		for (int i = 0 ; i < n; i++)
		{
			// If process is still incomplete (has burst time)
			if (rem_bt[i] > 0)
			{
				done = false; // There is remaining burst time

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

		// when all processes are done
		if (done == true)
		break;
	}
	free(rem_bt);
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,int bt[], int wt[], int tat[])
{
	// calculating turnaround time
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],int quantum)
{
	int total_wt = 0, total_tat = 0;

	int* wt;
	int* tat;
	wt = (int*)calloc(n, sizeof(int));
	tat = (int*)calloc(n, sizeof(int));


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
	}

	printf("Average waiting time= %.3f\n",(float)total_wt/n);
    printf("Average turn around time = %.3f\n",(float)total_tat/n);

    free(wt);
    free(tat);
}

// Driver code
int main()
{
	// process id's
	int i,quantum;
	int* processes;
    int* burst_time;
	printf("Enter number of processes: ");
	scanf("%d",&i);

	processes = (int*)calloc(i, sizeof(int));
	burst_time = (int*)calloc(i, sizeof(int));

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
                    printf("Incorrect format (Please enter a digit)\n");

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
	free(processes);
	free(burst_time);
	return 0;
}

