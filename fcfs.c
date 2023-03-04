#include <stdio.h>

#define MAX_THREADS 100

struct threadInfo {
    int p_id;
    int arr_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
};

int main() {

/* Opening the input file */
FILE *input_file = fopen("sample_in_schedule.txt", "r");
if (input_file == NULL) {
    printf("Failed to open input file.\n");
    return 1;
}

/*Reading the arrival time and burst times of each thread from the input file */ 
/* storing the info */
struct threadInfo threads[MAX_THREADS];
int number_threads = 0;
while (fscanf(input_file, "%d,%d,%d", &threads[number_threads].p_id, &threads[number_threads].arr_time, &threads[number_threads].burst_time) == 3) {
    threads[number_threads].waiting_time = 0;
    threads[number_threads].turn_around_time = 0;
    number_threads++;
}

/* Closed the input file */
fclose(input_file);

/* Scheduled the threads using the FCFS algorithm */
int curr_time = 0;
for (int i = 0; i < number_threads; i++) {
    /* update the current time if the current time is less than the arrival time */
    if (threads[i].arr_time > curr_time) {
        curr_time = threads[i].arr_time;
    }
    /* Calculating the waiting time and turn-around time */
    threads[i].waiting_time = curr_time - threads[i].arr_time;
    threads[i].turn_around_time = threads[i].waiting_time + threads[i].burst_time;
    /* Update the current time to reflect the completion of the thread's burst time */
    curr_time += threads[i].burst_time;
}

/* find sum of the average waiting time and turn-around time */
float average_waiting_time = 0.0;
float average_turn_around_time = 0.0;
for (int i = 0; i < number_threads; i++) {
    average_waiting_time += threads[i].waiting_time;
    average_turn_around_time += threads[i].turn_around_time;
}
average_waiting_time /= number_threads;
average_turn_around_time /= number_threads;

/* print final answer */
printf("The average waiting time : %.2f\n", average_waiting_time);
printf("The average turn-around time : %.2f\n", average_turn_around_time);

return 0;

}
