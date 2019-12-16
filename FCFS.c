#include<stdio.h>

// Function to find the waiting time for all processes
void calWaitingTime(int processes[], int n,int bt[], int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;
    // calculating waiting time
    for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}

// Function to calculate turn around time (tat)
void calTurnAroundTime(int processes[], int n, int bt[],int wt[], int tat[])
{
    // Burst time + waiting time (bt[i]+wt[i])
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}

// Function to calculate average waiting time(wt) and turn-around time(tat)
void calAvgTime(int processes[], int n, int bt[])
{
    int wt[100]={0}, tat[100]={0};

    // Calculate waiting time of all processes
    calWaitingTime(processes, n, bt, wt);

    // Calculate turn around time for all processes
    calTurnAroundTime(processes, n, bt, wt, tat);

    // Display the output result
   	printf("Process \t BurstTime \t Waiting time \t Turnaround Time");
    int total_wt = 0, total_tat = 0, total_bt=0;;
    for (int i = 0 ; i < n ; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        total_bt=total_bt+bt[i];
        printf("\n %d\t\t %d\t\t %d \t\t %d", i+1, bt[i], wt[i], tat[i]);
    };

    printf("\nAverage waiting time = %.2f ", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %.2f", (float)total_tat / (float)n);
    printf("\nThroughput time= %.3f\n",(float)n/total_bt);
}

int main()
{
	int i, processes[100]={0}, burst_t[100]={0};

    //User input prossessers
	printf("Enter Number of Processes: ");
	scanf("%d",&i);

	for(int x=0;x<i;x++)
	{
	    //Insert time for each process
	    printf("Enter the time for process %d: ",x+1);
	    scanf("%d",&burst_t[x]);
	}
	//Calculate the average
	calAvgTime(processes, i, burst_t);

	return 0;
}
