#include <iostream>

using namespace std;

class Process{
	// Variables
public:
	int pid;
	int start_time;
	int proc_length;
	int time_left;
	int status;
	
	// Functions
	void kill(){

	}
	//Run for t seconds
	void run(int t){
		time_left = time_left-t;
	}
};