#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "process.cpp"
#include "scheduler.cpp"


using namespace std;

// void print_table(Process p[], int n)
// {
//     int i;

//     puts("+-----+------------+--------------+------------------+--------------+----------------+");
//     puts("| PID | Burst Time | Waiting Time | Turn-Around Time | Arrival Time | Completion Time |");
//     puts("+-----+------------+--------------+------------------+--------------+----------------+");

//     for(i=0; i<n; i++) {
//         printf("| %2d  |     %2d     |      %2d      |        %2d       |      %2d      |       %2d       |\n"
//                , p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].arrivl_time, p[i].completion_time);
//         puts("+-----+------------+--------------+-----------------+");
//     }

// }


// void print_gantt_chart(Process p[], int n)
// {
//     int i, j;
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

	int n; double lambda;
	cout << "Number of Processes: ";
	cin >> n;
	cout << "Mean Time: ";
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



}
