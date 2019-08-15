#ifndef PROCESS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PROCESS_H

#include <iostream>

using namespace std;

class Process{
	// Variables
public:
	int pid;
	int start_time;
	int proc_length;
	int status;
private:
	bool alive;
	// Functions
	void kill();
	
	void run();
};


#endif
