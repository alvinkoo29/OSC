#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void findWaitingTime(int processes[], int n,int burst_time[], int waiting_time[], int quantum)
{
	// Make a copy of burst_time to calculate waiting time
	int* remaining_burst_time;
	bool* SecondQ;

	SecondQ= (bool*)calloc(n,sizeof(bool));
	remaining_burst_time = (int*)calloc(n, sizeof(int));

	for (int i = 0 ; i < n ; i++)
		remaining_burst_time[i] = burst_time[i];

	int t = 0; // Initialize to ensure consistent calculation

		// Goes through each processes sequentially
		for (int i = 0 ; i < n; i++)
		{
			// If process is still incomplete (has burst time)
			if (remaining_burst_time[i] > 0)
			{

				if (remaining_burst_time[i] > quantum)
				{
					// counter to calculate time taken for each process
					t += quantum;

					// reduces burst time by time quantum
					remaining_burst_time[i] -= quantum;

					// the process will be moved to the second queue
					SecondQ[i]=true;
				}

				// if less than time quantum (final run)
				else
				{
					// adds remainder burst time
					t = t + remaining_burst_time[i];

					// Waiting time is current time minus time used by this process
					waiting_time[i] = t - burst_time[i];

					// To show that the process is completed
					remaining_burst_time[i] = 0;
                }
            }
        }

        // loop for FCFS
        for (int i = 0 ; i < n; i++)
        {
            if (SecondQ[i]==true)
            {
                // completion - burst time
                t=t + remaining_burst_time[i];

                // waiting time = Completion time - burst time
                waiting_time[i] = t - burst_time[i];
            }
        }
    // to prevent memory leak
	free(remaining_burst_time);
}

// Function to calculate turn around time for each process
void findTurnAroundTime(int processes[], int n,int burst_time[], int waiting_time[], int turn_around_time[])
{
	// calculate turnaround time
	for (int i = 0; i < n ; i++)
		turn_around_time[i] = burst_time[i] + waiting_time[i];
}

// Function to calculate average time
void findavgTime(int processes[], int n, int burst_time[],int quantum)
{
	int total_waiting_time = 0, total_turn_around_time = 0,total_burst_time=0;

	int *waiting_time,*turn_around_time;
	waiting_time = (int*)calloc(n, sizeof(int));
	turn_around_time = (int*)calloc(n, sizeof(int));

	// calculate waiting time
	findWaitingTime(processes, n, burst_time, waiting_time, quantum);

	// calculate turn around time
	findTurnAroundTime(processes, n, burst_time, waiting_time,turn_around_time);

	printf("Processes\t"  "Burst time\t"  "Waiting time\t"  "Turn around time\n");

	// Calculate total waiting time and total turn around time
	for (int i=0; i<n; i++)
	{
		total_waiting_time = total_waiting_time + waiting_time[i];
		total_turn_around_time = total_turn_around_time + turn_around_time[i];
		printf(" %d\t\t %d\t\t %d \t\t %d\n",i+1,burst_time[i],waiting_time[i],turn_around_time[i]);
		total_burst_time=total_burst_time+burst_time[i];
	}

	printf("Average waiting time= %.3f\n",(float)total_waiting_time/n);
    printf("Average turn around time = %.3f\n",(float)total_turn_around_time/n);
    printf("Throughput time= %.3f\n",(float)total_burst_time/n);

    // free unused memory
    free(waiting_time);
    free(turn_around_time);
}

int main()
{
	int i=0,quantum=0;
	int *processes,*burst_time;

	printf("Enter number of processes: ");
	scanf("%d",&i);

	// allocate dynamic array according to user input
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
	// free allocated unused memory
	free(processes);
	free(burst_time);
	return 0;
}
