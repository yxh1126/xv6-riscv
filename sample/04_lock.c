#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 9
#define INCREMENTS_PER_THREAD 10000000

// A plain integer with no protection
int global_counter = 0;

void* increment_thread(void* arg) {
  for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
    // This looks simple, but it's a "read-modify-write"
    // operation that is NOT thread-safe.
    global_counter++;
  }
  return NULL;
}

// Declare a mutex to protect the shared variable
pthread_mutex_t counter_lock;

void* increment_thread_atomic(void* arg) {
  for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
    // Lock the mutex before touching the global variable
    pthread_mutex_lock(&counter_lock);
    global_counter++;
    // Unlock so other threads can have a turn
    pthread_mutex_unlock(&counter_lock);
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  pthread_t threads[NUM_THREADS];
  pthread_mutex_init(&counter_lock, NULL);

  // Determine which function to use based on arguments
  void* (*thread_func)(void*) = increment_thread;
  char* mode = "WRONG (No Lock)";

  if (argc > 1 && atoi(argv[1]) == 1) {
    thread_func = increment_thread_atomic;
    mode = "RIGHT (With Mutex)";
  }

  printf("Running in mode: %s\n", mode);
  printf("Starting %d threads, each incrementing %d times...\n",
         NUM_THREADS, INCREMENTS_PER_THREAD);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, thread_func, NULL);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Clean up the mutex
  pthread_mutex_destroy(&counter_lock);

  int expected = NUM_THREADS * INCREMENTS_PER_THREAD;
  printf("--- Results ---\n");
  printf("Expected Value: %d\n", expected);
  printf("Actual Value:   %d\n", global_counter);
  printf("Difference:     %d (Lost Increments)\n", expected - global_counter);

  return 0;
}
