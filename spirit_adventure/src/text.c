#include "../include/text.h"

int textDelay = 0; //change to 20 laterrrr

void tprintf(const char *format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    for (int i = 0; buffer[i] != '\0'; i++) {
        putchar(buffer[i]);
        fflush(stdout);
        usleep(textDelay * 1000);
    }
}
