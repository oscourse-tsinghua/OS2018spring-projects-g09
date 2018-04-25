#include "sbi.h"
#include "console.h"

/* kbd_intr - try to feed input characters from keyboard */
void libs_kbd_intr(void) {}

/* serial_intr - try to feed input characters from serial port */
void libs_serial_intr(void) {}

/* cons_init - initializes the console devices */
void libs_cons_init(void) {}

/* cons_putc - print a single character @c to console devices */
void libs_cons_putc(int c) { sbi_console_putchar((unsigned char)c); }

/* *
 * cons_getc - return the next input character from console,
 * or 0 if none waiting.
 * */
int libs_cons_getc(void) {
    int c = 0;
    c = sbi_console_getchar();
    return c;
}
