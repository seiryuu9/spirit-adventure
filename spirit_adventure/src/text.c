#include "../include/text.h"
#include <stdio.h>
#include <stdarg.h> // for va_list, va_start, va_end
#include <unistd.h> // for usleep

int textDelay = 20;

void tprintf(const char *format, ...) { // different number of args, sometimes more ints to insert etc
    char buffer[1024];
    va_list args; // constains various number of arguments
    va_start(args, format); // makes sure only args after format are considered
    vsnprintf(buffer, sizeof(buffer), format, args); // printf for va_list
    va_end(args); // frees memory allocated to args

    for (int i = 0; buffer[i] != '\0'; i++) {
        putchar(buffer[i]);
        fflush(stdout); // character is printed immediately, because buffer usually waits
        usleep(textDelay * 1000);
    }
}
