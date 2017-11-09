//
//  main.c
//  Homework 6
//
//  Created by Bailey Modlin on 11/7/17.
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
void rr(void);
void psjf(void);

int main(int argc, const char * argv[]) {
   
    char *p;
    long quantum = strtol(argv[2], &p, 10);
    int c = 0;
    struct process proc;
    
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

void fcfs(){
    printf("FCFS");
}

void rr(){
    
}

void psjf(){
    
}
