#include <iostream>
#include <bits/stdc++.h>
// #include "process.cpp"
using namespace std;

struct time_obj
{
	int pid;
	double s_t;
	double e_t;
	time_obj(int id, double s, double e){
		pid = id;
		s_t = s;
		e_t = e;
	}
};


bool cmp(Process p1, Process p2){
	return (p1.time_left < p2.time_left);
}

class FIFO_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	queue<Process> proc_q;				// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	// Functions

	void run_block(){
		double time_to_run = 1;		// time to add to global time
		// Process proc_to_run;
		// Process proc_to_spawn;
		if ( !proc_q.empty() && spawn_list.empty() ){
			Process proc_to_run = proc_q.front();					// Process to be run
			time_to_run = proc_to_run.time_left;
			// Running Process
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// Killing Process if needed
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
				proc_q.pop();
			}else{
				cout << "ERROR: Shouldnt have happened" << endl;
			}
		}else if ( proc_q.empty() && !spawn_list.empty() ){
			Process proc_to_spawn = spawn_list.front();		// Process to be spawned
			add_process(proc_to_spawn);
			spawn_list.pop_front();
			time_to_run = proc_to_spawn.arrival_time - current_time;
		}else if ( !proc_q.empty() && !spawn_list.empty() ){
			Process proc_to_spawn = spawn_list.front();		// Process to be spawned
			Process proc_to_run = proc_q.front();					// Process to be run
			time_to_run = proc_to_run.time_left;
			// If process is to be spawned first
			if (time_to_run >= proc_to_spawn.arrival_time - current_time){
				add_process(proc_to_spawn);
				spawn_list.pop_front();
				time_to_run = proc_to_spawn.arrival_time - current_time;
			}
			// Running Process
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// Killing Process if needed
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
				proc_q.pop();
			}else{
				cout << "ERROR: Shouldnt have happened" << endl;
			}
		}else{
			// Scheduler should exit
		}

		current_time += time_to_run;
	}

	vector<time_obj> run(){
		while(!spawn_list.empty() || !proc_q.empty()){
			run_block();
		}
		return timeline;
	}

	void add_process(Process new_proc){
		proc_q.push(new_proc);
	}

	void spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
};

class RR_scheduler{
	// Variables
public:
	double time_slice = 1;
	double current_time;					// Global time of scheduler
	queue<Process> proc_q;				// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	// Functions

	void run_block(){
		double time_to_run = time_slice;		// time to add to global time
		if ( !proc_q.empty() && spawn_list.empty() ){
			Process proc_to_run = proc_q.front();					// Process to be run
			if (time_to_run > proc_to_run.time_left){
				time_to_run = proc_to_run.time_left;
			}
			// Running Process
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// Killing Process if needed
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
				proc_q.pop();
			}else{
				// Again queue back process
				proc_q.pop();
				proc_q.push(proc_to_run);
			}
		}else if ( proc_q.empty() && !spawn_list.empty() ){
			Process proc_to_spawn = spawn_list.front();		// Process to be spawned
			add_process(proc_to_spawn);
			spawn_list.pop_front();
			time_to_run = proc_to_spawn.arrival_time - current_time;
		}else if ( !proc_q.empty() && !spawn_list.empty() ){
			Process proc_to_run = proc_q.front();					// Process to be run
			if (time_to_run > proc_to_run.time_left){
				time_to_run = proc_to_run.time_left;
			}
			// If process is to be spawned first
			while(current_time+time_to_run > spawn_list.front().arrival_time){
				Process proc_to_spawn = spawn_list.front();		// Process to be spawned
				add_process(proc_to_spawn);
				spawn_list.pop_front();
			}
			// Running Process
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// Killing Process if needed
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
				proc_q.pop();
			}else{
				// Again queue back process
				proc_q.pop();
				proc_q.push(proc_to_run);
			}
		}else{
			// Scheduler should exit
		}

		current_time += time_to_run;
	}

	vector<time_obj> run(){
		while(!spawn_list.empty() || !proc_q.empty()){
			run_block();
		}
		return timeline;
	}

	void add_process(Process new_proc){
		proc_q.push(new_proc);
	}

	void spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
};

class SJF_scheduler{
	// Variables
// public:
// 	double current_time;					// Global time of scheduler
// 	queue<Process> proc_q; 
	
// 	// Functions
// 	void run(){
// 		double time_to_run = 1;		// time to add to global time

// 		if (!proc_q.empty()){
// 			Process proc_to_run = proc_q.front();
// 			time_to_run = proc_to_run.time_left;
// 			double time_left = proc_to_run.run(time_to_run);
// 			if (time_left <= 0){
// 				proc_to_run.kill(current_time+time_to_run);
// 				proc_q.pop();
// 			}else{
// 				cout << "ERROR: Shouldn't have happened" << endl;
// 			}
// 		}

// 		current_time += time_to_run;
// 	}

	// void add_process(Process proc_list[]){
		// if (sizeof(proc_list)==0){
		// 	printf("No processes\n");
		// 	return;
		// }
		// double n = sizeof(proc_list)/sizeof(proc_list[0]);
		// sort(proc_list,proc_list+n, cmp);

		// for (double i = 0; i < n; i++){
		// 	proc_q.push(proc_list[i]);
		// }
	// }

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