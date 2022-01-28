#include <stdint.h>
#include <string.h>
#include <time.h>

static long sys_write(int fd, void const *buf, size_t cnt) {
	long output;
	__asm__ volatile(
			"syscall"
			: "=a"(output)
			: "a"(1), "D"(fd), "S"(buf), "d"(cnt)
			: "rcx", "r11", "memory");
	return output;
}

static int sys_nanosleep(struct timespec *rqtp, struct timespec *rmtp) {
	int output;
	__asm__ volatile(
			"syscall"
			: "=a"(output)
			: "a"(35), "D"(rqtp), "S"(rmtp)
			: "rcx", "r11", "memory");
	return output;
}

static void sys_exit(int status) {
	__asm__ volatile(
			"syscall"
			:
			: "a"(60), "D"(status)
			: "rcx", "r11");
	__builtin_unreachable();
}

// (ab)using compiler, strlen is not defined but compiler will optimize it away
#define PRINT(msg) sys_write(2, msg, strlen(msg))

static char *HELP = "Usage: sleep NUMBER\n"
					"Pause for NUMBER seconds, NUMBER need not be an integer.\n"
					"Git repo: <https://github.com/Virv12/sleep>\n";

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		PRINT(HELP);
		return 1;
	}

	char const *	s = argv[1];
	struct timespec a;
	a.tv_sec  = 0;
	a.tv_nsec = 0;

	if (s[0] == '-' && s[1] == 'h' && s[2] == 0) {
		PRINT(HELP);
		return 0;
	}

	for (; '0' <= *s && *s <= '9'; ++s) a.tv_sec = a.tv_sec * 10 + *s - '0';

	if (*s == '.') {
		uint32_t p = 1e8;
		while (++s, '0' <= *s && *s <= '9') {
			a.tv_nsec += (*s - '0') * p;
			p = (p >> 1) * (uint32_t)3435973837; // 3435973837 = 1/5 modulo 2 ** 32
		}
	}

	if (*s != 0) {
		PRINT("Invalid number\n");
		return 1;
	}

	sys_nanosleep(&a, 0);
	return 0;
}

void start_main(int argc, char const *argv[]) {
	sys_exit(main(argc, argv));
}
