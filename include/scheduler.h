#ifndef SCHEDULER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SCHEDULER_H

#include <iostream>

using namespace std;

class FIFO_scheduler{
	// Variables
public:
	queue<Process> proc_list;
	// Functions
	void run();
};

class RR_scheduler{
	// Variables
public:
	
	// Functions
	void run();
};

class SJF_scheduler{
	// Variables
public:
	
	// Functions
	void run();
};

class SRTF_scheduler{
	// Variables
public:
	
	// Functions
	void run();
};

class MLFQ_scheduler{
	// Variables
public:
	
	// Functions
	void run();
};


#endif
