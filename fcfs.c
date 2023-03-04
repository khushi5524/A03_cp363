#include <stdio.h>
#define SIZE 5 // constant size

// Struct for the process
typedef struct {
	int p_id;
	int arr_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
	int completiontime;
} threadInfo;

// Create a map to help Sort the input based on arrival time
typedef struct {
	int arrivalTime;
	int pid;
} Map;

// Methods
void turnAroundTime(threadInfo process[], int threadId, int completionTime); // Calculate the turn around Time
void waitingTime(threadInfo process[], int threadId); // Calculate the Waiting Time
void sortProcessArrivalTime(Map sortedarray[], int s); // sort the process based on the arrival time

int main(int argc, char *argv[]) {

	// Check if enough parameter is entered
	if (argc != 2) {
		printf("Error: Insufficient parameters passed.\n"); // print statement
		return 0; // return and stop the programming
	}

	// Open the file and read it
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("Error opening file");
		return (-1);
	}

	// Declare to the Thread Info and Map(for sorting)
	threadInfo process[SIZE + 1];
	Map sortedarray[SIZE + 1];

	// loop to initalize all value to -1 so that check to exist the loop
	for (int x = 0; x <= SIZE; x++) {
		process[x].p_id = -1;
		process[x].arr_time = -1;
		process[x].burst_time = -1;
		process[x].waiting_time = -1;
		process[x].turn_around_time = -1;
		process[x].completiontime = -1;
		sortedarray[x].pid = -1;
		sortedarray[x].arrivalTime = -1;
	}

	// read the input file and save to process and sorted array
	for (int row = 0; row < SIZE; row++) {
		fscanf(fp, "%d%*c %d%*c %d", &process[row].p_id, &process[row].arr_time,
				&process[row].burst_time);
		sortedarray[row].arrivalTime = process[row].arr_time;
		sortedarray[row].pid = process[row].p_id;
	}
	fclose(fp); // close the file pinter
	// call the sort function to sort the process based on arrival time
	sortProcessArrivalTime(sortedarray, SIZE);

// Just to test the sort
//	for (int row = 0; row <= SIZE; row++) {
//		printf("Arrival Time: %d\n", sortedarray[row].arrivalTime);
//		printf("PID: %d\n", sortedarray[row].pid);
//	}

	// Declare variables
	int completiontime = 0;
	int processNumber;
	//int completedprocess[SIZE];
	float avgWaitingTime = 0;
	float turnaroundTime = 0;
	int x = 0;

	// Header print statement
	printf(
			"Thread ID\tArrival Time\tBurst Time\tCompletion Time\tTurn-Around Time\tWaiting Time\n");

	// Loop while the pid isnt -1 which is the last pid meaning all process are complete
	do {

		// Look if current time is greater than or equal to arrival time
		if (completiontime >= sortedarray[x].arrivalTime) {
			// get the processnumber index from pid
			processNumber = sortedarray[x].pid - 1;

			completiontime += process[processNumber].burst_time;// calculate completion time
			turnAroundTime(process, processNumber, completiontime); // calculate turn around time
			waitingTime(process, processNumber); // calculate the waiting time
			process[processNumber].completiontime = completiontime; // add the completion time to the process struct
			avgWaitingTime += process[processNumber].waiting_time; // add the waiting time to be used later to find avg
			turnaroundTime += process[processNumber].turn_around_time; // add the turn around time to be use later to find avg
			x++; // increase counter

		} else {
			//if idle increase the current time
			completiontime++;
		}
	} while (sortedarray[x].pid >= 0);

	// Loop through the process and print  out the thread info
	for (int row = 0; row < SIZE; row++) {
		printf("%d\t\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[row].p_id,
				process[row].arr_time, process[row].burst_time,
				process[row].completiontime, process[row].turn_around_time,
				process[row].waiting_time);
	}

	// print the avg waiting time and avg turn around time
	printf("The average waiting time: %.2f\n", avgWaitingTime / SIZE);
	printf("The average turn-around time: %.2f\n", turnaroundTime / SIZE);

}

// Calculate Turn Around Time
void turnAroundTime(threadInfo process[], int threadId, int completionTime) {
	process[threadId].turn_around_time = completionTime
			- process[threadId].arr_time; // completionTime - arrival time

}

// Calculate the waiting time
void waitingTime(threadInfo process[], int threadId) {
	process[threadId].waiting_time = process[threadId].turn_around_time
			- process[threadId].burst_time; // Turn around time - burst time
}

// Sort the process based on arrival time in the Map struct
void sortProcessArrivalTime(Map sortedarray[], int s) {
	int i, j;
	Map temp;

	for (i = 0; i < s - 1; i++) {
		for (j = 0; j < (s - 1 - i); j++) {
			if (sortedarray[j].arrivalTime > sortedarray[j + 1].arrivalTime) {
				temp = sortedarray[j];
				sortedarray[j] = sortedarray[j + 1];
				sortedarray[j + 1] = temp;
			}
		}
	}
}
