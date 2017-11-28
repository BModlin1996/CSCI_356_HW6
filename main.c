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
 int i, total = 0, x, counter = 0; 
      int time_quantum = quantum; 
      int limit = numOfProcesses;
      int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10]; 
      float average_wait_time, average_turnaround_time;
      //printf("\nEnter Total Number of Processes:\t"); 
      //scanf("%d", &limit); 
      x = limit; 
      for(i = 0; i < limit; i++) 
      {
            //printf("\nEnter Details of Process[%d]\n", i + 1);
            //printf("Arrival Time:\t");
            //scanf("%d", &arrival_time[i]);
            //printf("Burst Time:\t");
            //scanf("%d", &burst_time[i]);
            burst_time[i] = proc[i].cpuTime;
            arrival_time[i] = proc[i].arrTime;
            temp[i] = burst_time[i];
      } 
      //printf("\nEnter Time Quantum:\t"); 
      //scanf("%d", &time_quantum); 
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      for(total = 0, i = 0; x != 0;) 
      { 
            if(temp[i] <= time_quantum && temp[i] > 0) 
            { 
                  total = total + temp[i]; 
                  temp[i] = 0; 
                  counter = 1; 
            } 
            else if(temp[i] > 0) 
            { 
                  temp[i] = temp[i] - time_quantum; 
                  total = total + time_quantum; 
            } 
            if(temp[i] == 0 && counter == 1) 
            { 
                  x--; 
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
                  wait_time = wait_time + total - arrival_time[i] - burst_time[i]; 
                  turnaround_time = turnaround_time + total - arrival_time[i]; 
                  counter = 0; 
            } 
            if(i == limit - 1) 
            {
                  i = 0; 
            }
            else if(arrival_time[i + 1] <= total) 
            {
                  i++;
            }
            else 
            {
                  i = 0;
            }
      } 
      average_wait_time = wait_time * 1.0 / limit;
      average_turnaround_time = turnaround_time * 1.0 / limit;
      printf("\n\nAverage Waiting Time:\t%f", average_wait_time); 
      printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time); 
     
    
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


