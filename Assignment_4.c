#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h> 
#include <unistd.h> 

void* requestResource(void*);  //function to request resource
int releaseResource(int*);    //function to release resrouce




//Data structures 
pthread_mutex_t available; 
pthread_mutex_t allocation; 
pthread_mutex_t max; 
pthread_mutex_t need; 
