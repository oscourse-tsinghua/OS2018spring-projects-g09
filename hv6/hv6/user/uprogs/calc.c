#include "user.h"

void inputline(char *buf, size_t n) {
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

int isspace(char c) {
    return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

int calc(char *str, int s, int t) {
    while(s < t && isspace(str[s])) s ++;
    while(s < t && isspace(str[t-1])) t --;

    int pos = -1;
    char op;
    for(int i = s; i < t; i ++) {
        if (str[i] == '+' || str[i] == '-') {
            pos = i;
            op = str[i];
        } else if (str[i] == '*' || str[i] == '/') {
            if (pos == -1 || op == '*' || op == '/') {
                pos = i;
                op = str[i];
            }
        }
    }
    int ans = 0;
    if (pos == -1) {
        while(s < t) {
            ans = ans*10 + str[s] - '0';
            s ++;
        }
    } else {
        int a = calc(str, s, pos);
        int b = calc(str, pos+1, t);
        switch(op) {
            case '+': ans = a + b; break;
            case '-': ans = a - b; break;
            case '*': ans = a * b; break;
            case '/': ans = a / b; break;
        }
    }
    
    return ans;
}

int main() {
    char buf[1024];
	cprintf("Input Expression:");
    inputline(buf, sizeof(buf));
    cprintf("Your Input:[%s]\n", buf);
    cprintf("Answer:%d\n", calc(buf, 0, strlen(buf)));

    exit();
}
