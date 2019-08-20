#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "process.h"
#include "scheduler.h"


using namespace std;

void print_table(vector<Process> p)
{
    int i;
    int n = p.size();

    puts("+-----+------------+---------------+------------------+--------------+-----------------+");
    puts("| PID | Burst Time | Response Time | Turn-Around Time | Arrival Time | Completion Time |");
    puts("+-----+------------+---------------+------------------+--------------+-----------------+");

    for(i=0; i<n; i++) {
    	Process proc = p.at(i);
        printf("|  %d  |    %05.2f   |     %05.2f     |       %05.2f      |     %05.2f    |      %05.2f      |\n"
               , proc.pid, proc.proc_length, proc.response_time, proc.turn_around_time, proc.arrival_time, proc.end_time);
        puts("+-----+------------+---------------+------------------+--------------+-----------------+");
    }

    printf("\n");

}


void print_gantt_chart(vector<Process> p, vector<time_obj> time)
{
    int i, j;
    int n = time.size();
    // print top bar
    printf("+");
    for(i=0; i<n; i++) {
    	printf("-");
        for(j=0; j<time.at(i).e_t-time.at(i).s_t; j++) printf("--");
        printf("-+");
    }
    printf("\n|");

    // printing process id in the middle
    for(i=0; i<n; i++) {
        for(j=0; j< time.at(i).e_t-time.at(i).s_t - 1; j++) printf(" ");
        printf(" P%d ", time.at(i).pid);
        for(j=0; j< time.at(i).e_t-time.at(i).s_t - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n+");
    // printing bottom bar
    for(i=0; i<n; i++) {
    	printf("-");
        for(j=0; j< time.at(i).e_t-time.at(i).s_t; j++) printf("--");
        printf("-+");
    }
    printf("\n");

    // printing the time line
    printf("0 ");
    for(i=0; i<n; i++) {
        for(j=0; j<time.at(i).e_t-time.at(i).s_t; j++) printf("  ");

        // if(time.at(i).turn_around_time > 9) printf("\b"); // backspace : remove 1 space
        if (time.at(i).e_t-time.at(i).s_t > 1) printf("\b\b%5.2f",time.at(i).e_t);
    	else{
    		printf("\b%4.1f",time.at(i).e_t);
    	}
        // printf("\b%0.2f", time.at(i).e_t);

    }
    printf("\n");
}


int main(){
	srand(time(NULL));
	FIFO_scheduler fifo;
	RR_scheduler rr;
	SJF_scheduler sjf;
	SRTF_scheduler srtf;
	MLFQ_scheduler mlfq;

	int n; double lambda;
	cout << "Number of Processes: ";
	cin >> n;
	cout << "Mean Time (Inter-arrival time): ";
	cin >> lambda;
	lambda = 1.0/ (double) lambda;

	int cap = 0.1;
	vector<double> proc_times;
	double sum = 0;
	for (int i = 0; i < n-1; i++){
		double r = (((double) rand() / (RAND_MAX)) * (1-cap)) + cap;
		double inter_time = - (log(r))/lambda;
		sum = sum + inter_time;
		proc_times.push_back(sum);
		printf("%0.2f ", inter_time);
	}
	printf("\n");

	cout << "Mean Time (Burst time): ";
	cin >> lambda;
	lambda = 1.0/ (double) lambda;
	list<Process> proc_list;

	double r = (((double) rand() / (RAND_MAX)) * (1-cap)) + cap;
	double burst_time = - (log(r))/lambda;
	Process new_proc(1,0,burst_time);
	proc_list.push_back(new_proc);
	printf("%0.2f ", burst_time);
	for (int i = 0; i < n-1; i++){
		double r = (((double) rand() / (RAND_MAX)) * (1-cap)) + cap;
		double burst_time = - (log(r))/lambda;
		printf("%0.2f ", burst_time);
		Process new_proc(i+2,proc_times.at(i),burst_time);
		proc_list.push_back(new_proc);
	}

	printf("\n");

	fifo.spawn_process(proc_list);
	rr.spawn_process(proc_list);
	sjf.spawn_process(proc_list);
	srtf.spawn_process(proc_list);
	mlfq.spawn_process(proc_list);

	printf("\n\n");
	printf("*******************************************FIFO*******************************************\n\n");
	vector<time_obj> fifo_t = fifo.run();
	print_table(fifo.ret_list);
	print_gantt_chart(fifo.ret_list, fifo_t);
	// cout << fifo.spawn_list.size() << " " << fifo.proc_q.size() << endl;
	printf("******************************************************************************************\n");

	printf("\n\n");

	printf("********************************************RR********************************************\n\n");
	vector<time_obj> rr_t = rr.run();
	print_table(rr.ret_list);
	print_gantt_chart(rr.ret_list, rr_t);
	printf("******************************************************************************************\n");

	printf("\n\n");

	printf("*******************************************SJF********************************************\n\n");
	vector<time_obj> sjf_t = sjf.run();
	print_table(sjf.ret_list);
	print_gantt_chart(sjf.ret_list, sjf_t);
	printf("******************************************************************************************\n");

	printf("\n\n");

	printf("*******************************************SRTF*******************************************\n\n");
	vector<time_obj> srtf_t = srtf.run();
	print_table(srtf.ret_list);
	print_gantt_chart(srtf.ret_list, srtf_t);
	printf("******************************************************************************************\n");

	printf("\n\n");

	printf("*******************************************MLFQ*******************************************\n\n");
	vector<int> slice_list{1,2,3};
	mlfq.set_queue_count(3,slice_list);
	vector<time_obj> mlfq_t = mlfq.run();
	print_table(mlfq.ret_list);
	print_gantt_chart(mlfq.ret_list, mlfq_t);
	printf("******************************************************************************************\n");

}

