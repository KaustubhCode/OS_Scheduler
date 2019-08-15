#include <iostream>
#include <bits/stdc++.h>
#include "process.h"
using namespace std;

class FIFO_scheduler{
	// Variables
public:
	int current_time;					// Global time of scheduler
	queue<Process> proc_q;

	// Functions
	void run(){
		int time_to_run = 1;		// time to add to global time

		if (!proc_q.empty()){
			Process proc_to_run = proc_q.front();
			time_to_run = proc_to_run.time_left;
			int time_left = proc_to_run.run(time_to_run);
			if (time_left == 0){
				proc_to_run.kill(current_time);
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

class RR_scheduler{
	// Variables
public:
	
	// Functions
	void run(){
		
	}
};

class SJF_scheduler{
	// Variables
public:
	
	// Functions
	void run(){
		
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