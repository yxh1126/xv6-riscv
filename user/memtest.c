#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    printf("Free memory: %d bytes\n", mfree());
    exit(0);
}
