#include <iostream>

using namespace std;

int main(){
	
}

void print_table(Process p[], int n)
{
    int i;

    puts("+-----+------------+--------------+------------------+--------------+----------------+");
    puts("| PID | Burst Time | Waiting Time | Turn-Around Time | Arrival Time | Completion Time |");
    puts("+-----+------------+--------------+------------------+--------------+----------------+");

    for(i=0; i<n; i++) {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |      %2d      |       %2d       |\n"
               , p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].arrivl_time, p[i].completion_time);
        puts("+-----+------------+--------------+-----------------+");
    }

}


void print_gantt_chart(Process p[], int n)
{
    int i, j;
    // print top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // printing process id in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("P%d", p[i].pid);
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // printing the time line
    printf("0");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("  ");
        if(p[i].turnaround_time > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", p[i].turnaround_time);

    }
    printf("\n");

}