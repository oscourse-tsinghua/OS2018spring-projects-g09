#ifndef __LIBS_STDIO_H__
#define __LIBS_STDIO_H__

#include "defs.h"
#include "stdarg.h"

/* kern/libs/stdio.c */
int libs_cprintf(const char *fmt, ...);
int libs_vcprintf(const char *fmt, va_list ap);
void libs_cputchar(int c);
int libs_cputs(const char *str);
int libs_getchar(void);

/* kern/libs/readline.c */
char *libs_readline(const char *prompt);

/* libs/printfmt.c */
void libs_printfmt(void (*putch)(int, void *), void *putdat, const char *fmt, ...);
void libs_vprintfmt(void (*putch)(int, void *), void *putdat, const char *fmt, va_list ap);
int libs_snprintf(char *str, size_t size, const char *fmt, ...);
int libs_vsnprintf(char *str, size_t size, const char *fmt, va_list ap);

#endif /* !__LIBS_STDIO_H__ */

