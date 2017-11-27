//
//  main.c
//  Homework 6
//
//  Created by Bailey Modlin, and Matthew Featherston on 11/7/17.
//
//  This program is designed to simulate thre CPU scheduling techniques (first come first serve, round robin, and preemptive shortest job first).
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
    int id;
    int cpuTime;
    int arrTime;
};

void fcfs(void);
void rr(long quantum);
void psjf(void);

int main(int argc, const char * argv[]) {
   
    char *p;
    long quantum = strtol(argv[2], &p, 10);
    int c = 0;
    struct process proc[32];
    
    do{
        
        c++;
    } while(c > 10);
    
    if(strcmp(argv[1], "FCFS") == 0){
        fcfs();
    } else if((strcmp(argv[1], "RR") == 0) && (quantum > 0)){
        
    } else if(strcmp(argv[1], "PSJF") == 0){
        
    } else {
        printf("Error: Incorrect arguements.  Scheduler [FCFS|RR|PSJF] Quantum > 0\n");
    }
    
    return 0;
}

/**
 * fcfs() - Simulates the first come first serve CPU scheduling method
 */
void fcfs(){
    printf("FCFS");
}

/**
 * rr() - Simulates the round robin CPU scheduling method
 */
void rr(long quantum){
    #include <stdio.h>
#include <stdbool.h>

/*findingWaitTime will find the wait time for all processes*/
void findWaitTime(int processes[], int n, int burstTimes[], int waitTime[], int quantum)
{
    //Creating arry to hold burst times
    int remainingBurstTime[n];
    for(int i =0; i < n; i++)
    {
        remainingBurstTime [i] = burstTimes [i];
    }
    
    int currentTime = 0; //current time
    int done =1;
    //executes processes in round robin manner
    while(done)
    {
       //int done = 1;
        
        //will execxute all processes one by one repeatedly 
        for(int i=0; i < n; i++)
        {
            
            //If burst time of process is greater than 0, then go ahead
            if(remainingBurstTime[i] > quantum)
            {
                    done = 0;
                    //Increase the value of t(which shows how much time a process has bee executed)
                    currentTime = currentTime + quantum;
                    
                    //Decrease the burst_time of the current process by a quantum
                    remainingBurstTime[i];
                
            }
            else//If the burst time is smaller or equal to the quantum. Last cycle for this process
            {
                //Increase the value of t(which shows the value of how much time a process has been executed)
                currentTime = currentTime + remainingBurstTime[currentTime];
                
                //waiting time = (current time) - (time used by "this" process)
                waitTime[i] = currentTime - burstTimes[i];
                
                //As the procees gets fully executed make its remaning burst time = 0
                remainingBurstTime [i] = 0;
            }
        }
        if(done == 1)
        {
            break;
        }
    }
}

/*findTurnAroundTime will find the turn around time of all process */
void findTurnAroundTime(int processes[], int n, int burstTime[], int waitTime[], int trunAroundTime[])
{
    //finding the turn around time = (burtTime) + (waitTime)
    for(int i = 0; i < n; i++)
    {
        trunAroundTime[i] = burstTime[i] + waitTime[i];
    }
}

/*findAvgTime will find the average time of all processes*/
void findingAvgTime(int processes[], int n, int burstTime[], int quantum)
{
    int waitTime [n], turnAroundTime[n], totalWaitTime = 0, totalTurnAroundTime = 0;
    
    //Finding the waiting time for all processes 
    findWaitTime(processes, n, burstTime, waitTime, quantum);
    
    //Finding trun around time for all processes 
    findTurnAroundTime(processes, n, burstTime, waitTime, turnAroundTime);
    
    //Display processes along with all details
    for(int i =0; i<n; i++)
    {
        totalWaitTime       = totalWaitTime + waitTime[i];
        totalTurnAroundTime = totalTurnAroundTime + turnAroundTime[i];
        printf("Processes %d | Burst Time %d | Waiting Time %d | Turn Around Time %d\n ", processes[i], burstTime[i], waitTime[i], turnAroundTime[i]  );
        
    }
    float avgWaitTime       = (float) totalWaitTime/(float) n;
    float avgTurnAroundTime = (float) totalTurnAroundTime/ (float) n;
    printf("The Average Waiting time:     %f\n" , avgWaitTime);
    printf("The Average Turn Around Time: %f\n" , avgTurnAroundTime);
}
int main()
{
    // process id's
    int processes[] = { 1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
 
    // Burst time of all processes
    int burst_time[] = {10, 5, 8};
 
    // Time quantum
    int quantum = 2;
    findingAvgTime(processes, n, burst_time, quantum);
    return 0;
}

    
}
/**
 * psjf() - Simulates the premptive shortest job first CPU scheduling method
 */
void psjf(){
        //PSJF from the website!!!    
      int arrival_time[numOfProc], burst_time[numOfProc], temp[numOfProc];
      int i, smallest;
      int count = 0 
      int time;//, limit;
      int limit = numOfProc;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      //printf("\nEnter the Total Number of Processes:\t");
      //scanf("%d", &limit); 
      //printf("\nEnter Details of %d Processes\n", limit);
      for(i = 0; i < limit; i++)
      {
            //printf("\nEnter Arrival Time:\t");
            //scanf("%d", &arrival_time[i]);
            //printf("Enter Burst Time:\t");
            //scanf("%d", &burst_time[i]); 
            //temp[i] = burst_time[i];
            arrival_time[i] = proc[i].arrTime;
            burst_time[i] = proc[i].cpuTime;
      }
      burst_time[9] = 9999;  
      for(time = 0; count != limit; time++)
      {
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
            }
      }
      average_waiting_time = wait_time / limit; 
      average_turnaround_time = turnaround_time / limit;
      printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
      printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
     // return 0;
    //return 0;
}
}
    
}
