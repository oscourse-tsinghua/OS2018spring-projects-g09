
#include <stdio.h>

static int x = 4;

int init()
{
    while(1) cprintf("Hello World x=%d\n", x);
    return 0;
}
