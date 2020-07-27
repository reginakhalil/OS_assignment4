#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h> 
#include <unistd.h> 

//Functions
void* requestResource(void*);  //function to request resource
int releaseResource(int*);    //function to release resrouce
int isSafe(); 				//safe algorithm 
void bankerRun(); 			//Runs the banker algorithm 
void printResources(); 		//print system status to the screen
int init(int, char**); 		//initialize arrays and variables
void updateNeed(int); 		//update need variable
int allocate(int, int*); 	//allocare resource
int isComplete(int); 		//Check for end process
int isFinsihed(int*);		//Check if process is finished

//Data structures 
int* available;    //the available amount of each resource
int** maximum;	   //the max demancd of each customer
int** allocation;  //the amount currently allocated to each customer
int** need; 	   //the remaining need of each customer
int resources; 
int processes; 
int* finish; 
int* safeseq; 

//synchronization mutex
pthread_mutex_t mutexAvailable;
pthread_mutex_t mutexAllocation;
pthread_mutex_t mutexMax;
pthread_mutex_t mutexNeed;

//Main Function
int main(int argc, char* argv[]) {

	if (argc < 2) 
	{
		printf("Input file name missing...exiting with error code -1\n");
        return -1;
	}
}

int init(int argc, char** argv){

}

void* requestResource(void* proc_in) {
	int Request[resources]; 
	int* proc = (int*)proc_in; 
	int process = proc[0]; 

	for (int k = 0; k < resources; k++){
		Request[k] = proc[k + 1]; 
	}

	if (allocate(process, Request) == 1) {
		printf("Request Satisfied.\n"); 
		if (isComplete(process) == 1) {
			printf("\tProcess %d has completed\n", process);
		}
	}
	else {
		printf("Request Denied.\n");
	}
	//free memory
	free(proc); 
	//exit the thread
	pthread_exit(NULL); 

}

int releaseResource(int* Request) {

}

int isSafe() {

}

void bankerRun() {

}


void printResources() {
	printf("\n==Current System Resources =="); 

	//------Print Status of Available------
	printf("\n=== Available ===\n");

	for(int i = 0; i < resources; i++) 
	{
		printf("\tR%d", i); 
	} 
	printf("\n");

	for(int i = 0; i < resources; i++) 
	{
		printf("\t%d", available[i]);
	}
	//-------------------------------------

	//-----Print Status of Allocation------
	printf("\n=== Allocation ===\n"); 

	for (int i = 0; i < resources; i++) {
		printf("\tR%d", i);
	}
	printf("\n"); 

	for (int i = 0; i < processes; i++) {
		if (finish[i] == 0) {
			printf("P%d\t", i);
			for (int j = 0; j < resources; j++) {
				printf("%d\t", allocation[i][j]);
			}
			printf("\n");
		}
	}
	//-------------------------------------
	

	//-----Print Status of Maximum---------
	printf("\n=== Maximum ===\n");
	for (int i = 0; i < resources; i++) {
		printf("\tR%d", i);
	}
	printf("\n"); 
	for (int i = 0; i < processes; i++) {
		if (finish[i] == 0) {
			printf("P%d\t", i);
			for (int j = 0; j < resources; j++) {
				printf("%d\t", maximum[i][j]);
			}
			printf("\n");
		}
	}
	//-------------------------------------

	//-----Print Status of Need------------
	printf("\n=== Need ===\n");
	for (int i = 0; i < resources; i++) {
		printf("\tR%d", i);
	}
	printf("\n"); 
	for (int i = 0; i < processes; i++) {
		if (finish[i] == 0) {
			printf("P%d\t", i);
			for (int j = 0; j < resources; j++) {
				printf("%d\t", need[i][j]);
			}
			printf("\n");
		}
	}
	//-------------------------------------



}

void updateNeed(int process) {

}
int allocate(int process, int* Request){

}
int isComplete(int process){

}
int isFinsihed(int* fin) {

}
















