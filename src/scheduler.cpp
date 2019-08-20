#include <iostream>
#include <bits/stdc++.h>
#include "process.h"
#include "scheduler.h"
using namespace std;

// ************************************************
// time_obj struct
// ************************************************
	time_obj::time_obj(int id, double s, double e){
		pid = id;
		s_t = s;
		e_t = e;
	}
// ************************************************


// ************************************************
// SJF Comparator
// ************************************************
  int sjf_comp::operator() (const Process& p1, const Process& p2) 
  { 
      return p1.time_left > p2.time_left; 
  }

	bool cmp(Process p1, Process p2){
		return (p1.time_left < p2.time_left);
	}
// ************************************************


// ************************************************
// FIFO Scheduler
// ************************************************
	void FIFO_scheduler::run_block(){
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

	vector<time_obj> FIFO_scheduler::run(){
		while(!spawn_list.empty() || !proc_q.empty()){
			run_block();
		}
		return timeline;
	}

	void FIFO_scheduler::add_process(Process new_proc){
		proc_q.push(new_proc);
	}

	void FIFO_scheduler::spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
// ************************************************


// ************************************************
// RR_scheduler
// ************************************************
	void RR_scheduler::run_block(){
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

	vector<time_obj> RR_scheduler::run(){
		while(!spawn_list.empty() || !proc_q.empty()){
			run_block();
		}
		return timeline;
	}

	void RR_scheduler::add_process(Process new_proc){
		proc_q.push(new_proc);
	}

	void RR_scheduler::spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
// ************************************************


// ************************************************
// SJF_scheduler
// ************************************************
	void SJF_scheduler::run_block(){
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

		current_time += time_to_run;
	}

	vector<time_obj> SJF_scheduler::run(){
		while(!spawn_list.empty() || !proc_q.empty()){
			run_block();
		}
		return timeline;
	}

	void SJF_scheduler::add_process(Process new_proc){
		proc_q.push(new_proc);
	}

	void SJF_scheduler::spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
// ************************************************


// ************************************************
// SRTF_scheduler Functions
// ************************************************
	void SRTF_scheduler::run_block(){
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

	vector<time_obj> SRTF_scheduler::SRTF_scheduler::run(){
		while(!spawn_list.empty() || !proc_q.empty()){
			run_block();
		}
		return timeline;
	}

	void SRTF_scheduler::add_process(Process new_proc){
		proc_q.push(new_proc);
	}

	void SRTF_scheduler::spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
// ************************************************


// ************************************************
// MLFQ Functions
// ************************************************
	void MLFQ_scheduler::run_block(){
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

		current_time += time_to_run;
	}

	void MLFQ_scheduler::set_queue_count( int n, vector<int> slice_list){
		time_slice_list = slice_list;
		queue<Process> q;
		queue_count = n;
		for (int i=0; i<n; i++){
			proc_q.push_back(q);
		}
	}

	vector<time_obj> MLFQ_scheduler::run(){
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

	void MLFQ_scheduler::add_process(Process new_proc){
		proc_q[0].push(new_proc);
	}

	void MLFQ_scheduler::spawn_process(list<Process> proc_list){
		spawn_list = proc_list;
	}
// ************************************************