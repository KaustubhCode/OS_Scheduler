#include <iostream>

using namespace std;

class Process{
	// Variables
public:
	// Needed for execution
	int pid;
	double arrival_time;		// Time when process spawned
	double start_time;			// Time when first run by scheduler
	double end_time;			// Time when completed
	double proc_length;		// Total CPU time needed to complete the job
	double time_left;			// CPU time remaining to be processed
	int status;				// 0: created, 1: after getting scheduled 1st time, 3:completed/killed
	// For reporting
	int turn_around_time;
	int wait_time;
	int response_time;

	Process(int id, double at, double burst){
		arrival_time = at;
		pid = id;
		proc_length = burst;
		time_left = burst; 
		status = 0;
	}

	// Functions
	void kill(double et){
		end_time = et;
		turn_around_time = end_time - arrival_time;
		response_time = start_time - arrival_time;
		status = 3;
	}
	//Run for t seconds
	int run(double t){
		if (status == 0){
			start_time = t;
			status = 1;
		}
		time_left = time_left-t;
		return time_left;
	}
};