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
	- '$ make'
	Complies your program with warnings enabled but not fatal. If successful, you should now have a file name 180234400_180565500_a04 (with no extention). 

	- '$ ./180234400_180565500_a04 10 5 7 8'
	Runs the program. The number of each type of resource is passed via command line (i.e. 10 5 7 8). 

	- See screenshots below

## Screenshots

<img width="371" alt="Screen Shot 2020-07-31 at 1 38 31 PM" src="https://user-images.githubusercontent.com/59515118/89107544-b67d2f00-d3ff-11ea-89d4-f0547d9d34d5.png">
<img width="298" alt="Screen Shot 2020-07-31 at 1 39 04 PM" src="https://user-images.githubusercontent.com/59515118/89107545-b7ae5c00-d3ff-11ea-88fe-73cf9f5111d5.png">
<img width="273" alt="Screen Shot 2020-07-31 at 1 40 47 PM" src="https://user-images.githubusercontent.com/59515118/89107546-b846f280-d3ff-11ea-8506-8a6ff81a449f.png">

## Built With

- C programming language 

- Linux environment (Ubuntu machine) 

## Contribution
Function Division: 
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
- [Banker's Algorithm](https://www.studytonight.com/operating-system/bankers-algorithm)
- [Tutorial and Examples](https://www.tutorialandexample.com/bankers-algorithm/)
- [Safety Algorithm](https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/#:~:text=The%20banker's%20algorithm%20is%20a,should%20be%20allowed%20to%20continue)

