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

void run_proc(void* data) {
	pid_t pid = fork();
	if (pid == 0) {
		exec_in_mem(data);
	}
	yield();
}

int main() {
	char buf[1024];
	pid_t pid = getpid();
	cprintf("Hello World pid = %d\n", pid);

	while(true) {
		cprintf("Input Your Command:");
		line(buf, sizeof(buf));

		if (strcmp(buf, "ls") == 0) {
			cprintf("hello calc\n");
		} else if (strcmp(buf, "hello") == 0) {
			extern char* _uprogs_hello_start[];
			run_proc(_uprogs_hello_start);
		} else if (strcmp(buf, "calc") == 0) {
			extern char* _uprogs_calc_start[];
			run_proc(_uprogs_calc_start);
		} else {
			cprintf("unknow command:[%s]\n", buf);
		}

		cprintf("\n");
	}

	pid = fork();
	cprintf("fork pid = %d\n", pid);
	if (pid == 0) {
		exit();
	}

	yield();
	cprintf("after yield getpid() = %d\n", getpid());

	cprintf("Info: init process exit.\n");
    while(1);
}
