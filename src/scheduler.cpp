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

// class mlfq_comp { 
// public: 
// 	int operator() (const Process& p1, const Process& p2){
// 		if (p1.qu > p2.qu){
// 			return 1;
// 		}else if (p1.qu == p2.qu &)
// 		return p1.time_left > p2.time_left; 
// 	} 
// };

class sjf_comp { 
public: 
    int operator() (const Process& p1, const Process& p2) 
    { 
        return p1.time_left > p2.time_left; 
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
			while(!spawn_list.empty() && current_time+time_to_run > spawn_list.front().arrival_time){
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
				cout << "ERROR: Queued" << endl;
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
			while(!spawn_list.empty() && current_time+time_to_run > spawn_list.front().arrival_time){
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
public:
	double current_time;					// Global time of scheduler
	priority_queue<Process, vector<Process>, sjf_comp> proc_q;	// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	// Functions

	void run_block(){
		double time_to_run;		// time to add to global time

		if (!proc_q.empty()){
			Process proc_to_run = proc_q.top();
			time_to_run = proc_to_run.time_left;
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			proc_q.pop();

			while(!spawn_list.empty() && current_time+time_to_run > spawn_list.front().arrival_time){
				Process proc_to_spawn = spawn_list.front();		// Process to be spawned
				add_process(proc_to_spawn);
				spawn_list.pop_front();
			}

			proc_to_run.kill(current_time+time_to_run);
			ret_list.push_back(proc_to_run);
		}
		else{
			if (!spawn_list.empty()){
				Process proc_to_spawn = spawn_list.front();
				time_to_run = proc_to_spawn.arrival_time - current_time;
				add_process(proc_to_spawn);
				spawn_list.pop_front();
			}
		}

		// if ( !proc_q.empty() && spawn_list.empty() ){
		// 	Process proc_to_run = proc_q.top();					// Process to be run
		// 	time_to_run = proc_to_run.time_left;
		// 	// Running Process
			// double time_left = proc_to_run.run(current_time, time_to_run);
			// timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
		// 	// Killing Process if needed
		// 	if (time_left <= 0){
		// 		proc_to_run.kill(current_time+time_to_run);
		// 		ret_list.push_back(proc_to_run);
		// 		proc_q.pop();
		// 	}else{
		// 		// shouldnt come
		// 		cout << "ERROR: SJF" << endl;
		// 	}
		// }else if ( proc_q.empty() && !spawn_list.empty() ){
		// 	Process proc_to_spawn = spawn_list.front();		// Process to be spawned
		// 	add_process(proc_to_spawn);
		// 	spawn_list.pop_front();
		// 	time_to_run = proc_to_spawn.arrival_time - current_time;
		// }else if ( !proc_q.empty() && !spawn_list.empty() ){
		// 	Process proc_to_run = proc_q.pop();					// Process to be run
		// 	time_to_run = proc_to_run.time_left;
		// 	// If process is to be spawned first
		// 	while(!spawn_list.empty() && current_time+time_to_run > spawn_list.front().arrival_time){
		// 		Process proc_to_spawn = spawn_list.front();		// Process to be spawned
		// 		add_process(proc_to_spawn);
		// 		spawn_list.pop_front();
		// 	}
		// 	// Running Process
		// 	double time_left = proc_to_run.run(current_time, time_to_run);
		// 	timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
		// 	// Killing Process if needed
		// 	if (time_left <= 0){
		// 		proc_to_run.kill(current_time+time_to_run);
		// 		ret_list.push_back(proc_to_run);
		// 		proc_q.pop();
		// 	}else{
		// 		// shouldnt come
		// 		cout << "ERROR: SJF" << endl;
		// 	}
		// }else{
		// 	// Scheduler should exit
		// }

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

class SRTF_scheduler{
	// Variables
public:
	double current_time;					// Global time of scheduler
	priority_queue<Process, vector<Process>, sjf_comp> proc_q;				// List of processes spawned and queued in Scheduler
	list<Process> spawn_list;		// List of processes to be queued
	vector<Process> ret_list;			// List of completed processes
	vector<time_obj> timeline;
	// Functions

	void run_block(){
		double time_to_run;		// time to add to global time
		if ( !proc_q.empty() && spawn_list.empty() ){
			Process proc_to_run = proc_q.top();					// Process to be run
			time_to_run = proc_to_run.time_left;
			// Running Process
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// Killing Process
			proc_to_run.kill(current_time+time_to_run);
			ret_list.push_back(proc_to_run);
			proc_q.pop();

		}else if ( proc_q.empty() && !spawn_list.empty() ){
			Process proc_to_spawn = spawn_list.front();		// Process to be spawned
			add_process(proc_to_spawn);
			spawn_list.pop_front();
			time_to_run = proc_to_spawn.arrival_time - current_time;
		}else if ( !proc_q.empty() && !spawn_list.empty() ){
			Process proc_to_run = proc_q.top();					// Process to be run
			time_to_run = proc_to_run.time_left;
			proc_q.pop();

			// If process is to be spawned first
			if (current_time+time_to_run > spawn_list.front().arrival_time){
				Process proc_to_spawn = spawn_list.front();		// Process to be spawned
				add_process(proc_to_spawn);
				time_to_run = proc_to_spawn.arrival_time - current_time;
				spawn_list.pop_front();
			}
			// Running Process
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// Killing Process if needed
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
			}else{
				// Again queue back process (acc to time_left)
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
	void run_process(Process proc_to_run){

	}

	void run_block(){
		double time_to_run;
		int select_q = 0;
		vector<double> time_modes{INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX};
		//{time_slice, time_left, time_allotment_left, time_till_reset, time_till_spawn}

		while (select_q < queue_count && proc_q[select_q].empty() ){	
			select_q++;
		}

		time_modes[3] = last_reset + reset_time - current_time;
		// Process proc_to_spawn;
		// Process proc_to_run;

		if (!spawn_list.empty()){
			Process proc_to_spawn = spawn_list.front();
			time_modes[4] = proc_to_spawn.arrival_time - current_time;
		}
		if ( select_q < queue_count){
			Process proc_to_run = proc_q[select_q].front();
			time_modes[0] = time_slice_list[select_q];
			time_modes[1] = proc_to_run.time_left;
			time_modes[2] = proc_to_run.time_allotment_left;
			// printf("Alloting time at start: %0.2f with pid: %d\n",proc_to_run.time_allotment_left,proc_to_run.pid);
		}
		auto itr = min_element(time_modes.begin(), time_modes.end());
		time_to_run = *itr;
		time_mode = distance(time_modes.begin(), itr);

		if (time_mode==0 || time_mode==1 || time_mode==2){
			Process proc_to_run = proc_q[select_q].front();
			double time_left = proc_to_run.run(current_time, time_to_run);
			timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			
			proc_to_run.time_allotment_left = INT_MAX;
			// Killing Process if needed
			if (time_left <= 0){
				proc_to_run.kill(current_time+time_to_run);
				ret_list.push_back(proc_to_run);
				proc_q[select_q].pop();
			}else{
				// Push Back
				proc_q[select_q].pop();
				if (select_q != queue_count-1){
					select_q++;
				}
				proc_q[select_q].push(proc_to_run);
			}
		}
		else if (time_mode==3){
			if (select_q < queue_count){
				Process* proc_to_run = &proc_q[select_q].front();
				double time_left = proc_to_run->run(current_time, time_to_run);
				timeline.push_back(time_obj(proc_to_run->pid, current_time, current_time+time_to_run));
				if (time_left <= 0){
					proc_to_run->kill(current_time+time_to_run);
					ret_list.push_back(*proc_to_run);
					proc_q[select_q].pop();
				}
			}
			for (int i=1; i<queue_count; i++){
				while (!proc_q[i].empty()){
					proc_q[i].front().time_allotment_left = INT_MAX;
					proc_q[0].push(proc_q[i].front());
					proc_q[i].pop();
				}
			}
			last_reset = current_time + time_to_run;
		}
		else if (time_mode==4){
			Process proc_to_spawn = spawn_list.front();
			if (select_q < queue_count){
				Process* proc_to_run = &proc_q[select_q].front();
				double time_left = proc_to_run->run(current_time, time_to_run);
				timeline.push_back(time_obj(proc_to_run->pid, current_time, current_time+time_to_run));
				if (time_left <= 0){
					proc_to_run->kill(current_time+time_to_run);
					ret_list.push_back(*proc_to_run);
					proc_q[select_q].pop();
				}
				else{
					if (proc_to_run->time_allotment_left == INT_MAX){
						proc_to_run->time_allotment_left = time_slice_list[select_q] - time_to_run;
					}
					else{
						proc_to_run->time_allotment_left = proc_to_run->time_allotment_left - time_to_run;
					}
				}
			}
			add_process(proc_to_spawn);
			spawn_list.pop_front();
		}

		// if ( select_q < queue_count && spawn_list.empty() ){
			// Process proc_to_run = proc_q[select_q].front();					// Process to be run
			// if (time_to_run > proc_to_run.time_left){
			// 	time_to_run = proc_to_run.time_left;
			// }
			// if (time_to_run > proc_to_run.time_allotment_left && proc_to_run.time_allotment_left != 0){
			// 	time_to_run = proc_to_run.time_allotment_left;
			// }

			// // Reset if needed
			// bool reset = false;
			// if (last_reset + reset_time < current_time + time_to_run){
			// 	time_to_run = last_reset + reset_time - current_time;
			// 	reset = true;
			// }

			// // Running Process
			// double time_left = proc_to_run.run(current_time, time_to_run);
			// timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
			// // Killing Process if needed
			// if (time_left <= 0){
			// 	proc_to_run.kill(current_time+time_to_run);
			// 	ret_list.push_back(proc_to_run);
			// 	proc_q[select_q].pop();
			// }else{
			// 	// Push Back
			// 	if (!reset){
			// 		proc_q[select_q].pop();
			// 		if (select_q != queue_count-1){
			// 			select_q++;
			// 		}
			// 		proc_q[select_q].push(proc_to_run);
			// 	}
			// }

		// }else if ( select_q >= queue_count && !spawn_list.empty() ){
		// 	Process proc_to_spawn = spawn_list.front();		// Process to be spawned
		// 	time_to_run = proc_to_spawn.arrival_time - current_time;
			
		// 	// Reset if needed
		// 	if (last_reset + reset_time < current_time + time_to_run){
		// 		last_reset = current_time + reset_time;
		// 	}
			// add_process(proc_to_spawn);
			// spawn_list.pop_front();

		// }else if ( select_q < queue_count && !spawn_list.empty() ){
		// 	Process proc_to_run = proc_q[select_q].front();					// Process to be run
		// 	if (time_to_run > proc_to_run.time_left){
		// 		time_to_run = proc_to_run.time_left;
		// 	}
		// 	// If process is to be spawned first
		// 	if (current_time+time_to_run > spawn_list.front().arrival_time){
		// 		Process proc_to_spawn = spawn_list.front();		// Process to be spawned
		// 		time_to_run = proc_to_spawn.arrival_time - current_time;
		// 		// Reset if needed
		// 		if (last_reset + reset_time < current_time + time_to_run){
		// 			last_reset = current_time + reset_time;
		// 		}
		// 		add_process(proc_to_spawn);
		// 		proc_to_run.time_allotment_left = time_slice_list[select_q] - time_to_run;
		// 		spawn_list.pop_front();
		// 	}

		// 	// Reset if needed
		// 	bool reset = false;
		// 	if (last_reset + reset_time < current_time + time_to_run){
		// 		time_to_run = last_reset + reset_time - current_time;
		// 		reset = true;	
		// 	}
		// 	// Running Process
		// 	double time_left = proc_to_run.run(current_time, time_to_run);
		// 	timeline.push_back(time_obj(proc_to_run.pid, current_time, current_time+time_to_run));
		// 	// Killing Process if needed
		// 	if (time_left <= 0){
		// 		proc_to_run.kill(current_time+time_to_run);
		// 		ret_list.push_back(proc_to_run);
		// 		proc_q[select_q].pop();
		// 	}else{

		// 		// if (proc_to_run.time_allotment_left!=0){
		// 		// 	if]

		// 		// }

		// 		// Push Back
		// 		if (!reset){
		// 			proc_q[select_q].pop();
		// 			if (select_q != queue_count-1){
		// 				select_q++;
		// 			}
		// 			proc_q[select_q].push(proc_to_run);
		// 		}
		// 	}
		// }else{
		// 	// Scheduler should exit
		// }

		// if (reset){
		// 	for (int i=1; i<queue_count; i++){
		// 		while (!proc_q[i].empty()){
		// 			proc_q[i].front().time_allotment_left = 0;
		// 			proc_q[0].push(proc_q[i].front());
		// 			proc_q[i].pop();
		// 		}
		// 	}
		// 	last_reset = current_time + reset_time;
		// }

		current_time += time_to_run;
	}

	void set_queue_count( int n, vector<int> slice_list){
		time_slice_list = slice_list;
		queue<Process> q;
		queue_count = n;
		for (int i=0; i<n; i++){
			proc_q.push_back(q);
		}
	}

	vector<time_obj> run(){
		bool val = true;
		while(!spawn_list.empty() || val){
			run_block();
			val = false;
			for (int i = 0; i < queue_count; i++){
				if (!proc_q[i].empty()){
					val = true;
					break;
				}
			}
		}
		return timeline;
	}

	void add_process(Process new_proc){
		proc_q[0].push(new_proc);
	}

	void spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
};