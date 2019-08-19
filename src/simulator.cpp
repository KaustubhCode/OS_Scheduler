#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "process.cpp"
#include "scheduler.cpp"


using namespace std;

void print_table(vector<Process> p)
{
    int i;
    int n = p.size();

    puts("+-----+------------+--------------+------------------+--------------+----------------+");
    puts("| PID | Burst Time | Waiting Time | Turn-Around Time | Arrival Time | Completion Time |");
    puts("+-----+------------+--------------+------------------+--------------+----------------+");

    for(i=0; i<n; i++) {
    	Process proc = p.at(i);
        printf("| %2d  |     %0.2f     |      %0.2f      |        %0.2f       |      %0.2f      |       %0.2f       |\n"
               , proc.pid, proc.proc_length, proc.wait_time, proc.turn_around_time, proc.arrival_time, proc.end_time);
        puts("+-----+------------+--------------+-----------------+");
    }

}


// void print_gantt_chart(vector<Process> p, vector<time_obj> time)
// {
//     int i, j;
//     int n = p.size();
//     // print top bar
//     printf(" ");
//     for(i=0; i<n; i++) {
//         for(j=0; j<p[i].burst_time; j++) printf("--");
//         printf(" ");
//     }
//     printf("\n|");

//     // printing process id in the middle
//     for(i=0; i<n; i++) {
//         for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
//         printf("P%d", p[i].pid);
//         for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
//         printf("|");
//     }
//     printf("\n ");
//     // printing bottom bar
//     for(i=0; i<n; i++) {
//         for(j=0; j<p[i].burst_time; j++) printf("--");
//         printf(" ");
//     }
//     printf("\n");

//     // printing the time line
//     printf("0");
//     for(i=0; i<n; i++) {
//         for(j=0; j<p[i].burst_time; j++) printf("  ");
//         if(p[i].turnaround_time > 9) printf("\b"); // backspace : remove 1 space
//         printf("%d", p[i].turnaround_time);

//     }
//     printf("\n");
// }


int main(){
	cout << "TEST" << endl;
	srand(time(NULL));
	FIFO_scheduler fifo;
	RR_scheduler rr;
	SJF_scheduler sjf;
	// SRTF_scheduler sjf;
	// MLFQ_scheduler sjf;

	int n; double lambda;
	cout << "Number of Processes: ";
	cin >> n;
	cout << "Mean Time (Inter-arrival time): ";
	cin >> lambda;
	lambda = 1.0/ (double) lambda;

	int cap = 0.1;
	vector<double> proc_times;
	for (int i = 0; i < n-1; i++){
		double r = (((double) rand() / (RAND_MAX)) * (1-cap)) + cap;
		double inter_time = - (log(r))/lambda;
		proc_times.push_back(inter_time);
		printf("%0.2f ", inter_time); 
	}

	cout << "Mean Time (Burst time): ";
	cin >> lambda;
	lambda = 1.0/ (double) lambda;
	list<Process> proc_list;

	double r = (((double) rand() / (RAND_MAX)) * (1-cap)) + cap;
	double burst_time = - (log(r))/lambda;
	Process new_proc(1,0,burst_time);
	proc_list.push_back(new_proc);
	for (int i = 0; i < n-1; i++){
		double r = (((double) rand() / (RAND_MAX)) * (1-cap)) + cap;
		double burst_time = - (log(r))/lambda;
		Process new_proc(i+2,proc_times.at(i),burst_time);
		proc_list.push_back(new_proc);
	}

	fifo.spawn_process(proc_list);
	// rr.spawn_process(proc_list);
	// sjf.spawn_process(proc_list);

	vector<time_obj> fifo_t = fifo.run();
	print_table(fifo.ret_list);
	// print_gantt_chart(fifo.ret_list, fifo_t);


	// vector<time_obj> rr_t = rr.run();
	// vector<time_obj> sjf_t = sjf.run();
}

