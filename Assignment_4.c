#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h> 
#include <unistd.h> 

void* requestResource(void*);  //function to request resource
int releaseResource(int*);    //function to release resrouce

//Data structures 
int* available;    //the available amount of each resource
int** maximum;	   //the max demancd of each customer
int** allocation;  //the amount currently allocated to each customer
int** need; 	   //the remaining need of each customer



//synchronization mutex
pthread_mutex_t mutexAvailable;
pthread_mutex_t mutexAllocation;
pthread_mutex_t mutexMax;
pthread_mutex_t mutexNeed;

int main(int argc, char* argv[]) {

	if (argc < 2) 
	{
		printf("Input file name missing...exiting with error code -1\n");
        return -1;
	}
}