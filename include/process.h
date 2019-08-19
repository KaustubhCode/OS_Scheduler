#ifndef PROCESS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PROCESS_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Process{
	// Variables
public:
	int pid;
	int arrival_time;		// Time when process spawned
	int start_time;			// Time when first run by scheduler
	int end_time;				// Time when completed
	int proc_length;		// Total CPU time needed to complete the job
	int time_left;			// CPU time remaining to be processed
	int status;					// 0: created, 1: after getting scheduled 1st time, 3:completed/killed
	// For reporting
	int turn_around_time;
	int wait_time;
	int response_time;

	Process(int at);
	// Functions
	void kill(int et);
	
	int run(int t);
};


#endif
