/*	AUTHORS:  Raghad Khalil- 180234400, Divya Naiken- 180565500
	FILE: 180234400_180565500_a04.c.txt
	PROJECT: Assignment_4
	DATE: 01-August-2020 */

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
int* available;    //the amount of avaliable resources 
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
    }

    //Initialize the arrays and variables 
    //Pass in the values from terminal
    init(argc, argv);

    //Initialize the complete array 
    for(int i=0; i< processes; i++)
    {
      	finish[i] =0;
    }

    int check = 1; 
    while(check ==1)
    {
    	char* in_line = malloc(sizeof(char) * 30);		//variable to store the command taken from terminal

    	//Ask user for the command 
    	printf("\nEnter Command: "); 

    	//Reads line from stream
    	fgets(in_line, 30, stdin);

    	//If user enters '*', output the current state of the avaliable,max,current and need arrays
    	if(in_line[0] =='*')
    	{
    		printResources();
    	}

    	//--------------------run----------------------
    	else if(in_line[0] =='R' && in_line[1] == 'u' && in_line[2] == 'n')
    	{
    		//run the safe algorithm to avoid deadlocks 
    		if (isSafe() == 1) 
    		{
    			printf("Safe Sequence is: < ");
    			//print the safe sequence 
    			for (int i = 0; i < processes; i++) 
    			{
    				printf("%d ", safeseq[i]);
    			}

    			printf(" >\nNow going to execute the threads:\n\n\n\n");

        		//run the banker algorithm 
        		bankerRun(); 

        		printf("\n = Success! = \n");
        		printf("All processes finished without deadlock\n"); 
    		}
    		else 
    		{ 
    			//system is in deadlock 
    			printf("\nSystem is in deadlock state\n"); 

    		}
    		check = 0; 
    	}

    	//-----------request allocation---------------

    	else if (in_line[0] == 'R' && in_line[1] == 'Q') 
    	{
    		int k =0;

			for(k = 0; in_line[k] != '\0'; k++);

			for(int l = 0; l < (k - 2); l++)
			{
				in_line[l] = in_line[l + 2];
			}

			int* com = malloc(sizeof(int) * (resources + 1));
			char* tmp; 
			int m = 0; 

			tmp = strtok(in_line, " ");

			while(tmp != NULL)
			{
				com[m++] = atoi(tmp);
				tmp = strtok(NULL, " ");
			}

			if(finish[com[0]] == 0) 
			{
				//Allocate through thread
				pthread_t tid; 

				pthread_create(&tid, NULL, requestResource, (int*)com);

				pthread_join(tid, NULL); 
			}
    	}

    	//----------release request-----------------

    	else if (in_line[0] == 'R' && in_line[1] == 'L')
    	{
    		for(int t= 0; in_line[t] != '\0'; t++);

    		for(int v =0; v < (v - 2); v++)
    		{
    			in_line[v] = in_line[v + 2]; 
    		}

    		int* com2 = malloc(sizeof(int) * (resources + 1)); 
    		char* tmp2; 
    		int m2;

    		while(tmp2 != NULL)
    		{
    			com2[m2++] = atoi(tmp2);
    			tmp2 = strtok(NULL, " ");
    		}

    		if(finish[com2[0]] == 0) 
    		{ 
    			//Release resource
        		if(releaseResource(com2) == 0)
        		{
        			printf("Request is Denied.\n");
        		}

        		else
        		{
        			printf("Request is Satisfied.\n");
        		}
        	}	
    	}

    	//Free memory 
    	free(in_line); 

    }// end of while 

    //-------free memory-------------------

  	for(int a = 0; a < processes; a++) 			//not sure if you can do it like this review later *** might need seperate for loops 
  	{
  		free(allocation[a]);
  		free(maximum[a]);
  		free(need[a]); 
  	}

  	free(allocation);
  	free(maximum);
  	free(need);
  	free(available); 			//free avaliable
  	free(safeseq); 				//free safe sequence 
  	free(finish); 				//free finish 

  	return 0;      
}

//This function initialized arrays and variables
int init(int argc, char** argv) {
	//Read Data from the input file

	char* line_read = malloc(sizeof(char) * 10); 

	for (int i = 1; i < argc; i++) {
		resources = i - 1; 
	}

	if ((available = malloc(resources * sizeof(int))) == NULL) {
		return -1; 

	}

	//coverts the paramter from a string to an integer. 
	int j = 0; 
	for (int i = 1; i < argc; i++) {
		available[j++] = atoi(argv[i]); 
	}

	//open the file and extract its data 
	FILE* fp; 
	if ((fp = fopen("sample4_in.txt", "r")) == NULL) {
		printf("Error opening file. Please try again\n");
		return -1; 

	}

	processes = 0; 
	char line; 

	while (line != EOF) {
		line = getc(fp); 
		if (line == '\n') {
			processes++; 
		}
	}
	fclose(fp); 
	//file read//

	//Safe sequence dynamic array 
	safeseq = malloc(processes * sizeof(int)); 

	//print number of customers, hence the number of processes
	printf("Number of Customers: %d", processes); 

	//print the available resources
	printf("\nCurrently Available Resources: ");
	for (int i = 0; i < resources; i++) {
		printf("%d", available[i]); 
	}

	printf("Max Resources: \n"); 
	if ((fp = fopen("sample4_in.txt", "r")) == NULL) {
		printf("Error opening file. Please try again\n");
		return -1; 
	}

	//--------Create the maximum array------------------
	char* temp; 
	if ((maximum = malloc(processes * sizeof(int*))) == NULL) {
		return -1; 
	}

	for (int i = 0; i < processes; i++) {
		if ((maximum[i] = malloc(processes * sizeof(int*))) == NULL) {
			return -1; 
	}
	}

	int i = 0; 
	while (i < 5) {
		fgets(line_read, 30, fp); 
		j = 0; 
		//split the string on spaces using a tokenizer 
		temp = strtok(line_read, " "); 
		while (temp != NULL) {
			//convert the value to an integer then add it to the maximum array
			maximum[i][j] = atoi(temp); 
			temp = strtok(NULL, " "); 
			j++; 

		}
		for (j = 0; j < resources; j++) {
			printf("%d ", maximum[i][j]); 
		}
		printf("\n");
		i++; 
	}
	//---------------------------------------------------


	//--------Create the allocation array----------------
	if ((allocation = malloc(processes *sizeof(int*))) == NULL) {
		return -1; 
	}
	for (int i = 0; i < processes; i++) {
		if ((allocation[i] = malloc(processes * sizeof(int*))) == NULL) {
			return -1; 
		}
	}
	//---------------------------------------------------



	//--------Create the need array-----------------------

	if ((need = malloc(processes *sizeof(int*))) == NULL) {
		return -1; 
	}
	for (int i = 0; i < processes; i++) {
		if ((need[i] = malloc(processes * sizeof(int*))) == NULL) {
			return -1; 
		}
	}

	for (int j = 0; j < processes; j++) {
		updateNeed(j); 
	}

	//---------------------------------------------------


	//--------Create the finsih array--------------------
	if ((finish = malloc(processes *sizeof(int*))) == NULL) {
		return -1; 
	}
	//---------------------------------------------------

	//Close the file and free memory
	fclose(fp); 
	free(line_read); 
	return 0; 
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
	int process = Request[0];
	//Check requests and allocation

	for(int j = 0; j < resources; j++)
	{
		if(Request[j] > allocation[process][j])
		{
			return 0; 
		}
	}

	//Mutex part 
	for(int i = 0; i < resources; i++)
	{
		pthread_mutex_lock(&mutexAllocation);
		allocation[process][i] -= Request[i + 1];

		pthread_mutex_unlock(&mutexAllocation);

		pthread_mutex_lock(&mutexAvailable);

		available[i] += Request[i+ 1];
		pthread_mutex_unlock(&mutexAvailable);
	}

	//update Need
	updateNeed(process); 

	return 1; //success

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
	for(int i=0; i < resources; i++)
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

		for(int l = 0; l < processes; l++)
		{
			if(fin[l] ==0)
			{
				check = 0; 

				for(int v = 0; v < resources && check == 0; v++)
				{
					if(need[l][v] > work[v])
					{
						check = 1; 
					}
				}


				if(check ==0)
				{
					safeseq[k] = l; 
					k++; 

					for(int u =0; u < resources; u++)
					{
						work[u] += need[l][u];
					}

					fin[l] = 1; 
				}
			}
			
		}
	}
	//Free memory 
	free(fin);
	free(work); 
	return 1;
}

void bankerRun() 
{
	int i,j;
	int l = 0;
	for (l = 0; l < processes; l++) {
		printf("\t-->Consumer/Threads %d\n", safeseq[l]);
		printf("\tAllocated Resources: ");

		for (j = 0; j < resources; j++) {
			printf("%d ", allocation[safeseq[l]][j]);
		}

		printf("\n\tNeeded: ");

		for (j = 0; j < resources; j++) {
			printf("%d ", need[safeseq[l]][j]);
		}

		printf("\n\tAvailable: ");

		for (j = 0; j < resources; j++) {
			printf("%d ", available[j]);
		}

		int* com = malloc(sizeof(int) * (resources + 1));
		int k = 1;
		com[0] = safeseq[l];

		for (j = 0; j < resources; j++) {
			com[k++] = need[safeseq[l]][j];
		}

		printf("\n\tThread has started\n\t");
		pthread_t thread;
		pthread_create(&thread, NULL, requestResource, (int*)com);
		pthread_join(thread, NULL);
		isComplete(safeseq[l]);
		printf("\tThread has finished");
		printf("\n\tThread is releasing resources");
		printf("\n\tNew Available: ");
		for (j = 0; j < resources; j++) {
			printf("%d ", available[j]);
		}
		
		printf("\n");
		//free memory
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
	printf(" \n");

	for(int i = 0; i < resources; i++) 
	{
		printf("\t%d", available[i]);
	}
	//-------------------------------------

	//-----Print Status of Allocation------
	printf("\n=== Allocation === \n"); 

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
int allocate(int process, int* request)
{
	for(int j = 0; j < resources; j++)
	{
		//Make sure that the request is less than avaliable
		if(request[j] > available[j])
		{
			return 0; 
		}
	}

	for(int i = 0; i < resources; i++)
	{
		//lock
		pthread_mutex_lock(&mutexAllocation);

		//add request 
		allocation[process][i] += request[i]; 

		//unlock
		pthread_mutex_unlock(&mutexAllocation);

		//lock 
		pthread_mutex_lock(&mutexAvailable); 

		//remove request 
		available[i] -= request[i]; 

		//unlock
		pthread_mutex_unlock(&mutexAvailable);
	}
	
	//Update matrix 
	updateNeed(process);
	return 1; 
}

int isComplete(int process){

	//returns 0 if process is not complete
	for (int i = 0; i < resources; i++) {
		if (allocation[process][i] != maximum[process][i]) {
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
	for (int i = 0; i < processes; i++) {
		if (fin[i] == 0) {
			return 0; 
		}
	}

	//returns 1 if process is finished
	return 1; 

}
















