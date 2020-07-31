# Assignment 4: Banker's Algorithm
This software is composed of a multiple threaded program that implements the Banker's algorithm. Customers request and release bank resources. The banker must have the resources tracked. the banker will grant customers a request if they satisfy the safety algorithm. When a request does not leave the system in a safe state, it is denied by the banker. 
## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites
For development, you will need a linux operating system. If you do not have the linux OS, you can install VirtualBox and Ubuntu on your device. You will also need a text editor of your choice (Notepad++ recommended for Windows users and SublimeText recommended for Mac users), and Git. 

### Installing
- Installation of Git 
Install or update to the latest version of [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git). 

- Installation of VirtualBox: 
	1. Visit [VirtualBox Website](https://www.virtualbox.org/)
	2. Click on "Download VirtualBox 6.1"
	3. Then choose the appropriate platform for installation
	4. Dowload the file for the required Operating System and click to install and follow the installation steps. 

- Installation of Ubuntu machine in VirtualBox 
	1. Click [here](OSC10e.ova) to download the Ubuntu VirtualBox Appliance file  
	2. Double-click on the downloaded file and follow the instruction on to install the appliance in VirtualBox Link
	3. Both the username and password for the Ubuntu Machine is osc.
	4. The steps would install a command-line based Ubuntu Server running version 4.4 of the Linux kernel. It includes standard development tools given as :
		- gcc
		- make
		- java 8
		- python
		- ssh

## Running the tests
- How to Run
	- '$ make Assignment_4'
	Complies your program with warnings enabled but not fatal. If successful, you should now have a file name Assignment_4 (with no extention). 

	- '$ ./Assignment_4 10 5 7 8'
	Runs the program. The number of each type of resource is passed via command line (i.e. 10 5 7 8). 

	- See screenshots below

## Screenshots

## Code Examples 

## Built With

### C programming language 

### Linux environment

##Contribution

Functions divisions: 
- Divya Naiken:
	- isSafe(); 
	- releaseResource(); 
	- allocate(); 
	- bankerRun(); 
	- main(); 

- Raghad Khalil: 
	- printResources(); 
	- init(); 
	- updateNeed(); 
	- isComplete(); 
	- isFinished(); 
	- main();  


## Authors
- Raghad Khalil - 180234400
- Divya Naiken - 180565500
- See also the list of contributors who participated in this project.

## Acknowledgment

