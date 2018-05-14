#ifndef __LIBS_STRING_H__
#define __LIBS_STRING_H__

#include "defs.h"

size_t libs_strlen(const char *s);
size_t libs_strnlen(const char *s, size_t len);

char *libs_strcpy(char *dst, const char *src);
char *libs_strncpy(char *dst, const char *src, size_t len);

int libs_strcmp(const char *s1, const char *s2);
int libs_strncmp(const char *s1, const char *s2, size_t n);

char *libs_strchr(const char *s, char c);
char *libs_strfind(const char *s, char c);
long libs_strtol(const char *s, char **endptr, int base);

void *libs_memset(void *s, char c, size_t n);
void *libs_memmove(void *dst, const void *src, size_t n);
void *libs_memcpy(void *dst, const void *src, size_t n);
int libs_memcmp(const void *v1, const void *v2, size_t n);

#endif /* !__LIBS_STRING_H__ */

