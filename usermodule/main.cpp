#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "driver.hpp"

int main(int argc, char const *argv[]) {

    int result = 0;
    pid_t pid = getpid();

    //Initialize driver with Process IDentifier
    driver->initialize(pid);

    int value = 555;

    result = driver->Read<int>((uintptr_t) &value);

    printf("Result = %d", result);

    return 0;
}
