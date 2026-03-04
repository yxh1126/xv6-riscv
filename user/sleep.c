#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // 1. Check if the user provided the required argument
  if(argc != 2){
    fprintf(2, "Usage: sleep <ticks>\n");
    exit(1);
  }

  // 2. Convert the command-line argument (string) to an integer
  int ticks = atoi(argv[1]);

  // 3. Call the sleep system call
  if(pause(ticks) < 0){
    fprintf(2, "sleep: system call failed\n");
    exit(1);
  }

  // 4. Exit successfully
  exit(0);
}
