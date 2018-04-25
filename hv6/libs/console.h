#ifndef __KERN_DRIVER_CONSOLE_H__
#define __KERN_DRIVER_CONSOLE_H__

void libs_cons_init(void);
void libs_cons_putc(int c);
int libs_cons_getc(void);
void libs_serial_intr(void);
void libs_kbd_intr(void);

#endif /* !__KERN_DRIVER_CONSOLE_H__ */

