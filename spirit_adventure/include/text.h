#ifndef SPIRIT_ADVENTURE_TEXT_H
#define SPIRIT_ADVENTURE_TEXT_H

#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <stdarg.h> //
#include <unistd.h> // for usleep

extern int textDelay;

void tprintf(const char *format, ...);

#endif

#endif //SPIRIT_ADVENTURE_TEXT_H