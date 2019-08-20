#ifndef SCHEDULER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SCHEDULER_H

#include <iostream>
#include <bits/stdc++.h>
#include "process.h"

using namespace std;

struct time_obj
{
	int pid;
	double s_t;
	double e_t;
	time_obj(int id, double s, double e);
};

class sjf_comp { 
public: 
    int operator() (const Process& p1, const Process& p2);
};

bool cmp(Process p1, Process p2);

class FIFO_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	queue<Process> proc_q;				// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	// Functions
	void run_block();
	vector<time_obj> run();
	void add_process(Process new_proc);
	void spawn_process(list<Process> proc_list);
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
	void run_block();
	vector<time_obj> run();
	void add_process(Process new_proc);
	void spawn_process(list<Process> proc_list);
};

class SJF_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	priority_queue<Process, vector<Process>, sjf_comp> proc_q;	// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;

	// Functions
	void run_block();
	vector<time_obj> run();
	void add_process(Process new_proc);
	void spawn_process(list<Process> proc_list);
};

class SRTF_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	priority_queue<Process, vector<Process>, sjf_comp> proc_q;				// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	
	// Functions
	void run_block();
	vector<time_obj> run();
	void add_process(Process new_proc);
	void spawn_process(list<Process> proc_list);
};

class MLFQ_scheduler{
	// Variables
public:
	vector<int> time_slice_list;
	int queue_count = 3;
	double last_reset = 0;
	double reset_time = 10;
	double current_time;					// Global time of scheduler
	int time_mode = 0;
	vector<queue<Process> > proc_q;				// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	
	// Functions
	void set_queue_count( int n, vector<int> slice_list);
	void run_block();
	vector<time_obj> run();
	void add_process(Process new_proc);
	void spawn_process(list<Process> proc_list);
};


#endif
