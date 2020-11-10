#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define RESOURCE_NUMBER 50
#define PROC_NUMBER 50

int main(){
    FILE* input = fopen("input.txt", "r");
    char buf[BUF_SIZE];
    int existingResources[RESOURCE_NUMBER]; // existing resource
    int availableResources[RESOURCE_NUMBER]; // available resource
    int currentAllocation[PROC_NUMBER][RESOURCE_NUMBER]; // current allocation
    int requestMatrix[PROC_NUMBER][RESOURCE_NUMBER]; // request matrix

    fgets(buf, BUF_SIZE, input);
    char* p = buf;
    int eCount = 0;
    while (*p != '\n'){
        int temp = strtol(p, &p, 10);
        existingResources[eCount++] = temp;
    }
    getc(input);
    fgets(buf, BUF_SIZE, input);
    p = buf;
    int aCount = 0;
    while (*p != '\n'){
        int temp = strtol(p, &p, 10);
        availableResources[aCount++] = temp;
    }
    getc(input);
    int pCount = 0;
    while(strcmp(fgets(buf, BUF_SIZE, input), "\n") != 0){
        p = buf;
        for (int i = 0; i < eCount; i++){
            int temp = strtol(p, &p, 10);
            currentAllocation[pCount][i] = temp;
        }
        pCount++;
    }

    for (int i = 0; i < pCount; i++){
        fgets(buf, BUF_SIZE, input);
        p = buf;
        for (int j = 0; j < eCount; j++){
            int temp = strtol(p, &p, 10);
            requestMatrix[i][j] = temp;
        }
    }


    int doneProcesses[PROC_NUMBER] = {};

    while(1){
		int done = 0;
		for(int i = 0; i < pCount; i++){
			if(doneProcesses[i]){ continue; }
			int j;
			for(j = 0; j < aCount; j++){
				if(requestMatrix[i][j] > availableResources[j]){
					break;
				}	
			}
			if(j != aCount){ continue; }
			for(j = 0; j < aCount; j++){
				availableResources[j] += requestMatrix[i][j] + currentAllocation[i][j];
			}
			done = 1;	
			doneProcesses[i] = 1;
		}

		if(done == 0){
			break;
        }
	}

    FILE* output = fopen("output.txt", "w");

    int deadlock = 0;
    for (int i = 0; i < pCount; i++){
        if (!doneProcesses[i]){
            deadlock = 1;
            break;
        }
    }

    if (deadlock){
        fprintf(output, "there is a deadlock: ");
        for (int i = 0; i < pCount; i++){
            if (!doneProcesses[i]){ fprintf(output, "%d ", i); }
        }
        
    }else{
        fprintf(output, "no deadlock");
    }

    return 0;

}