#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h> 
#include <unistd.h> 

//Functions
void* requestResource(void*);  //function to request resource
int releaseResource(int*);    //function to release resrouce
int isSafe(); 				//Function to check safe sequence (determines if there is a deadlock)
void bankerRun(); 			//Runs the banker algorithm 
void printResources(); 		//print system status to the screen
int init(int, char**); 		//initialize arrays and variables
void updateNeed(int); 		//update need variable
int allocate(int, int*); 	//allocare resource
int isComplete(int); 		//Check for end process
int isFinsihed(int*);		//Check if process is finished

//Data structures 
int* available;    //the amount of avaliable reasources 
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

	//Ensure an argument was provided
	if (argc < 2) 
	{
		printf("Input file name missing...exiting with error code -1\n");
        return -1;

        //Initialize the arrays and variables 
        //Pass in the values from terminal
        //init(argc, argv)

        //Initialize the complete array 
        for(int i=0; i< processes; i++)
        {
        	finish[i] =0;
        }

        int check = 1; 
        while(check ==1)
        {
        	char * in_line = malloc(sizeof(char) * 30);		//variable to store the command taken from terminal

        	//Ask user for the command 
        	printf("\nEnter Command: "); 

        	//Reads line from stream
        	fgets(in_line, 30, stdin)

        	//If user enters '*', output the current state of the avaliable,max,current and need arrays
        	if(in_line[0] =='*')
        	{
        		printResources();
        	}

        	//If the user enters "Run"
        	else if(in_line[0] =='R' && in_line[1] == 'u' && in_line[2] == 'n')
        	{

        	}

        }
	}
}

//This function initialized arrays and variables
int init(int argc, char** argv){

	//Read Data from the input file

	char* line_read = malloc(sizeof(char) * 10); 

	for (int i = 1; i < argc; i++) {
		resources = i - 1; 
	}

	if ((available = malloc(resources * sizeof(int)) == NULL) {
		return -1; 

	}

	int j = 0; 
	for (int i = 1; i < argc; i++) {
		available[j++] = atoi(argv[i]); 
	}

	//open the file and extract its data 
	FILE* fp; 
	if ((file = fopen("input.txt", "r")) == NULL) {
		printf("Error opening file. Please try again\n");
		return -1; 

	}



void* requestResource(void* proc_in) {
	int Request[resources]; 
	int* proc = (int*)proc_in; 
	int process = proc[0]; 

	for (int k = 0; k < resources; k++){
		Request[k] = proc[k + 1]; 
	}

	//if check if process can be allocated and if process is completed
	if (allocate(process, Request) == 1) {
		printf("Request Satisfied.\n"); 
		if (isComplete(process) == 1) {
			printf("\tProcess %d has completed\n", process);
		}
	}
	else {
		//if proccess is already allocated, deny request. 
		printf("Request Denied.\n");
	}
	//free memory
	free(proc); 
	//exit the thread
	pthread_exit(NULL); 

}

int releaseResource(int* Request) 
{


}

/* Returns 1 if safe, 0 if not*/
int isSafe() 
{
	//Create the work array 
	int* work; 

	//Create the finished array
	int* fin = malloc(sizeof(int) * processes); 

	//Create the work array
	if(!(work = malloc(sizeof(int) * resources)))
	{
		return 0; 
	}

	//Fill up the work array
	for(int i=0; i < reasources; i++)
	{
		work[i] = available[i];
	}

	//Fill up the fin array
	for(int j=0; j < processes; j++)
	{
		fin[j] = finish[j];
	}

	//Set all variables to 0
	int check=0;
	int k =0;
	int counter =0;

	//While not finished 
	while(isFinsihed(fin) ==0)
	{
		counter++;

		//Unsafe condition
		if(counter > processes)
		{
			return 0; 
		}

		for(int l=0; l < processes; l++)
		{
			if(fin[l] ==0)
			{
				
			}
		}
	}

}

void bankerRun() 
{
		int l = 0;

		for(l=0; l<processes; l++)
		{
			printf("\t-->Consumer Threads %d\n", safesq[l]); //From safe sequence 
		}

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

	// need = max - allocation 
	for(int i = 0; i < resources; i++) {
		need[process][i] = maximum[process][i] - allocation[process][i];
	}

}
int allocate(int process, int* Request){

}

int isComplete(int process){

	//returns 0 if process is not complete
	for (int i = 0; i < resources; i++) {
		if (allocation[process][i] != maximum[process[i]]) {
			return 0; 
		}
	}

	for (int i = 0; i < resources; i++) {
		available[i] += maximum[process][i]; 
	}

	//Returns 1 if process is complete
	finish[process] = 1; 
	return 1; 

}
int isFinsihed(int* fin) {

	//returns 0 if process is not finished
	for (int = 0; i < processes; i++) {
		if (fin[i] == 0) {
			return 0; 
		}
	}

	//returns 1 if process is finished
	return 1; 

}
















