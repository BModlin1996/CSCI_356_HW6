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
#include <unistd.h>
#include <stdbool.h>

struct process {
    int id;
    int cpuTime;
    int arrTime;
    int waittime;
};

void fcfs(int numOfProc, struct process proc[]);
void rr(long quantum, int numOfProc, struct process proc[]);
void psjf(int numOfProc, struct process proc[]);

int TIME = 0;

int main(int argc, const char * argv[]) {
   
    char *p;
    long quantum = strtol(argv[2], &p, 10);
    int i = 0;
    int c = 0;
    int totalTime = 0;
    struct process proc[32];
    
    printf("Please enter process data (Enter three 0's to finish): \n");
    do{
        printf("PID: ");
        scanf("%d", &proc[i].id);
        printf("Process Time: ");
        scanf("%d", &proc[i].cpuTime);
        printf("Arival Time: ");
        scanf("%d", &proc[i].arrTime);
        totalTime = proc[i].cpuTime;
        if((proc[i].arrTime == 0) && (proc[i].cpuTime == 0) && (proc[i].id == 0)){
            c = 1;
        }
        i++;
    } while(c != 1);
    
    if(strcmp(argv[1], "FCFS") == 0){
        fcfs(i, proc);
    } else if((strcmp(argv[1], "RR") == 0) && (quantum > 0)){
        rr(quantum, i, proc);
    } else if(strcmp(argv[1], "PSJF") == 0){
        psjf(i, proc);
    } else {
        printf("Error: Incorrect arguements.  Scheduler [FCFS|RR|PSJF] Quantum > 0\n");
        exit(-1);
    }
    
    return 0;
}

/**
 * fcfs() - Simulates the first come first serve CPU scheduling method
 */
void fcfs(int numOfProc, struct process proc[]){

    double avgWait = 0;
    int running = 0, totalTime = 0;
	printf("\nSimulation starting:\n");
    for(int i = 0; i < (numOfProc - 1); i++){
		printf("%d %d arriving\n%d %d running\n", proc[i].arrTime, proc[i].id, TIME, proc[i].id);
        proc[i].waittime = TIME - proc[i].arrTime;
        TIME += proc[i].cpuTime;
        avgWait += proc[i].waittime;
    }
    avgWait = avgWait / (numOfProc - 1);
    printf("Average waiting time: %f\nAverage response time: \nAverage CPU usage: \n", avgWait);
}

/**
 * rr() - Simulates the round robin CPU scheduling method
 */
void rr(long quantum, int numOfProc, struct process proc[]){

    int turnAroundTime[(numOfProc - 1)], rear = (numOfProc - 1);
    double avgWait = 0, avgTurnArnd = 0;
    int remainder = 0, count = 0;
    struct process queue[128];

    printf("\nSimulation starting:\n");
    for(int i = 0; i < (numOfProc - 1); i++){
        queue[i] = proc[i];
    }
    for(int i = 0; i <= 128; i++){
        if(queue[i].cpuTime > quantum)
        {
	    	rear++;
            queue[i].cpuTime = (int) quantum;
            remainder = proc[i].cpuTime - (int) quantum;
            queue[rear].cpuTime = remainder;
			queue[rear].id = proc[i].id;
            count++;
        } else {
            queue[i].cpuTime = proc[i].cpuTime;
        }
        count++;
    }
    for(int i = 0; i < numOfProc; i++){
         printf("Queue: %d", queue[i].cpuTime); 
    }
    //executes processes in round robin manner
    //will execxute all processes one by one repeatedly
        for(int i=0; i < count; i++)
        {
            queue[i].waittime = TIME - queue[i].arrTime;
            TIME += queue[i].cpuTime;
            //Increase the value of t(which shows the value of how much time a process has been executed)
            //waiting time = (current time) - (time used by "this" process)
            printf("Wait time: %d\nCurrent time: %d\nCount: %d\n", queue[i].waittime, TIME, count);
            avgWait += queue[i].waittime;
            //Finding the turn around time = (burtTime) + (waitTime)
            turnAroundTime[i] = queue[i].cpuTime + queue[i].waittime;
            avgTurnArnd += turnAroundTime[i];
        }
    avgWait = avgWait / (numOfProc - 1);
    avgTurnArnd = avgTurnArnd / numOfProc;
    printf("Average waiting time: %f\nAverage response time: \nAverage CPU usage: \n", avgWait);
}

/**
 * psjf() - Simulates the premptive shortest job first CPU scheduling method
 */
void psjf(int numOfProc, struct process proc[]){
        //PSJF from the website!!!    
      int arrival_time[numOfProc], burst_time[numOfProc], temp[numOfProc];
      int i, smallest;
      int count = 0; 
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
    
}


