
#include <sbi.h>

void cons_putc(int c) { sbi_console_putchar((unsigned char)c); }

int init()
{
    while(1) cons_putc('x');
    return 0;
}
