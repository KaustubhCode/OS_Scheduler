#ifndef PROCESS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PROCESS_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Process{
	// Variables
public:
	// Needed for execution
	int pid;
	double arrival_time;		// Time when process spawned
	double start_time;			// Time when first run by scheduler
	double end_time;			// Time when completed
	double proc_length;			// Total CPU time needed to complete the job
	double time_left;			// CPU time remaining to be processed
	int status;					// 0: created, 1: after getting scheduled 1st time, 3:completed/killed
	int qu;
	// For reporting
	double turn_around_time;
	double wait_time;
	double response_time;

	double time_allotment_left;

	Process(int id, double at, double burst);
	Process();
	// Functions
	void kill(double et);
	
	double run(double c_t, double t);
};


#endif
