sleep: boot.s sleep.c
	gcc -nostartfiles -static -Os -nodefaultlibs -nostdlib -s -o $@ $^ -flto -Wall -Wextra -Wpedantic -Wshadow -Qn -std=c18 -fno-stack-protector -fno-asynchronous-unwind-tables -Wl,-n,-gc-sections,-build-id=none -T x86_64.ld
