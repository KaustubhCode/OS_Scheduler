#include <iostream>
#include <bits/stdc++.h>
// #include "process.cpp"
using namespace std;


bool cmp(Process p1, Process p2){
	return (p1.time_left < p2.time_left);
}

class FIFO_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	queue<Process> proc_q;				// List of processes spawned and queued in Scheduler
	vector<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	// Functions

	void run_block(){
		double time_to_run = 1;		// time to add to global time

		if (!proc_q.empty()){
			Process proc_to_run = proc_q.front();
			Process proc_to_spawn = spawn_list.front();
			time_to_run = proc_to_run.time_left;
			if (time_to_run >= proc_to_spawn.arrival_time - current_time){
				add_process(proc_to_spawn);
				spawn_list.pop_front();
				time_to_run = proc_to_spawn.arrival_time - current_time;
			}
			double time_left = proc_to_run.run(time_to_run);
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
				proc_q.pop();
			}else{
				cout << "ERROR: Shouldnt have happened" << endl;
			}
		}

		current_time += time_to_run;
	}

	vector<Process> run(){
		while(!spawn_list.empty() && !proc_q.empty()){
			run_block();
		}
		return ret_list;
	}

	void add_process(Process &new_proc){
		proc_q.push(new_proc);
	}

	void spawn_process(vector<Process> proc_list){
		spawn_list = proc_list;
	}
};

class RR_scheduler{
	// Variables
public:
	double time_slice = 1;			// Time Slice for RR
	double current_time;					// Global time of scheduler
	queue<Process> proc_q;

	// Functions
	void run(){
		double time_to_run = time_slice;
		if (!proc_q.empty()){
			Process proc_to_run = proc_q.front();
			if (proc_to_run.time_left > time_to_run){
				proc_to_run.run(time_to_run);
			}else{
				time_to_run = proc_to_run.time_left;
				proc_to_run.run(time_to_run);
			}
			double time_left = proc_to_run.run(time_to_run);
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				proc_q.pop();
			}else{
				cout << "ERROR: Shouldnt have happened" << endl;
			}
		}

		current_time += time_to_run;
	}

	void add_process(Process &new_proc){
		proc_q.push(new_proc);
	}
};

class SJF_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	queue<Process> proc_q; 
	
	// Functions
	void run(){
		double time_to_run = 1;		// time to add to global time

		if (!proc_q.empty()){
			Process proc_to_run = proc_q.front();
			time_to_run = proc_to_run.time_left;
			double time_left = proc_to_run.run(time_to_run);
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				proc_q.pop();
			}else{
				cout << "ERROR: Shouldn't have happened" << endl;
			}
		}

		current_time += time_to_run;
	}

	void add_process(Process proc_list[]){
		if (sizeof(proc_list)==0){
			printf("No processes\n");
			return;
		}
		double n = sizeof(proc_list)/sizeof(proc_list[0]);
		sort(proc_list,proc_list+n, cmp);

		for (double i = 0; i < n; i++){
			proc_q.push(proc_list[i]);
		}
	}

};

class SRTF_scheduler{
	// Variables
public:
	
	// Functions
	void run(){
		
	}
};

class MLFQ_scheduler{
	// Variables
public:
	
	// Functions
	void run(){
		
	}
};