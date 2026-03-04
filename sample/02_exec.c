#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Path to the executable
  char *binaryPath = "/usr/bin/echo";
  char *message;

  // Check if the user provided an argument in the command line
  if (argc > 1) {
    message = argv[1];
  } else {
    message = "helloworld"; // Default value
  }

  // Arguments: The first must be the executable name, followed by params,
  // and must end with a NULL pointer.
  char *args[] = {binaryPath, message, NULL};

  printf("Executing /usr/bin/echo with message: %s\n", message);

  // execv replaces the current process
  if (execv(binaryPath, args) == -1) {
    // If execv returns, an error occurred
    perror("execv failed");
    return 1;
  }

  // This line will never be reached if execv is successful
  printf("\nThis line will never be reached if execv is successful\n");
  return 0;
}
