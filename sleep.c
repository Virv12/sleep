#include <stdint.h>
#include <string.h>
#include <time.h>

int sys_write(unsigned int fd, char const *buf, size_t cnt);
int sys_nanosleep(struct timespec *rqtp, struct timespec *rmtp);

#define PRINT(msg) sys_write(2, msg, strlen(msg))

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		PRINT("Usage: sleep SECONDS\n");
		return 1;
	}

	char const *s = argv[1];
	struct timespec a;
	a.tv_sec = 0;
	a.tv_nsec = 0;

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
}
