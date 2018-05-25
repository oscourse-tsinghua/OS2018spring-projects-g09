#include "user.h"

void line(char *buf, size_t n) {
	char ch;
	size_t off = 0;

	while(off < n) {
		ch = sys_debug_getchar();
		if (ch == '\r') continue;
		if (ch == '\n') break;
		buf[off++] = ch;
	}
	buf[off] = '\0';
	return;
}

int main() {
	char buf[1024];
	pid_t pid = getpid();
	cprintf("Hello World\n");

	line(buf, sizeof(buf));
	cprintf("Line:%s\n", buf);

    while(1);
}
