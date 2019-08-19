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
	double proc_length;			// Total CPU time needed to complete the job
	double time_left;			// CPU time remaining to be processed
	int status;					// 0: created, 1: after getting scheduled 1st time, 3:completed/killed
	// For reporting
	double turn_around_time;
	double wait_time;
	double response_time;

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
		wait_time = end_time - arrival_time - proc_length;
		status = 3;
	}
	//Run for t seconds
	double run(double c_t, double t){
		if (status == 0){
			start_time = c_t;
			status = 1;
		}
		time_left = time_left-t;
		return time_left;
	}
};