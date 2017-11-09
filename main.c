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
    
}
/**
 * psjf() - Simulates the premptive shortest job first CPU scheduling method
 */
void psjf(){
    
}
