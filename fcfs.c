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

/* Open the input file *=
FILE *input_file = fopen("sample_in_schedule.txt", "r");
if (input_file == NULL) {
    printf("Failed to open input file.\n");
    return 1;
}

/*Read the arrival time and burst times of each thread from the input file */ 
/* and store the information in an array of threadInfo structs */
struct threadInfo threads[MAX_THREADS];
int number_threads = 0;
while (fscanf(input_file, "%d,%d,%d", &threads[number_threads].p_id, &threads[number_threads].arr_time, &threads[number_threads].burst_time) == 3) {
    threads[number_threads].waiting_time = 0;
    threads[number_threads].turn_around_time = 0;
    number_threads++;
}

/* Close the input file */
fclose(input_file);

/* Schedule the threads using the FCFS algorithm */
int curr_time = 0;
for (int i = 0; i < number_threads; i++) {
    /* If the current time is less than the arrival time of the thread, update the current time */
    if (threads[i].arr_time > curr_time) {
        curr_time = threads[i].arr_time;
    }
    /* Calculate the waiting time and turn-around time for the thread */
    threads[i].waiting_time = curr_time - threads[i].arr_time;
    threads[i].turn_around_time = threads[i].waiting_time + threads[i].burst_time;
    /* Update the current time to reflect the completion of the thread's burst time */
    curr_time += threads[i].burst_time;
}

/* Calculate the average waiting time and turn-around time for all threads */
float avg_waiting_time = 0.0;
float avg_turn_around_time = 0.0;
for (int i = 0; i < number_threads; i++) {
    avg_waiting_time += threads[i].waiting_time;
    avg_turn_around_time += threads[i].turn_around_time;
}
avg_waiting_time /= number_threads;
avg_turn_around_time /= number_threads;

/* Print the results */
printf("The average waiting time : %.2f\n", avg_waiting_time);
printf("The average turn-around time : %.2f\n", avg_turn_around_time);

return 0;

}
