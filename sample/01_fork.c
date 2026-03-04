#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid, wait_pid;
  int status;

  pid = fork();

  if (pid < 0) {
    perror("Fork failed");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child: Starting work (PID: %d)...\n", getpid());
    sleep(2);
    printf("Child: Work complete. Exiting with status 42.\n");
    // Exiting with a specific value to be caught by the parent
    exit(42);
  } else {
    // Parent process
    printf("Parent: Waiting for child %d to finish...\n", pid);

    /* * wait(&status) fills 'status' with exit info
     * and returns the PID of the child that ended.
     */
    wait_pid = wait(&status);

    printf("Parent: wait() returned for PID: %d\n", wait_pid);

    // Check if the child exited normally
    if (WIFEXITED(status)) {
      int exit_code = WEXITSTATUS(status);
      printf("Parent: Child exited normally with code: %d\n", exit_code);
    } else {
      printf("Parent: Child did not exit normally.\n");
    }
  }

  return 0;
}
