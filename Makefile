sleep: boot.s sleep.c
	gcc -nostartfiles -static -Os -nodefaultlibs -nostdlib -s -o $@ $^ -flto -Xlinker -n -Wall -Wextra -Wpedantic -Wshadow -Qn -std=c18 -Xlinker -gc-sections -fno-stack-protector -fno-asynchronous-unwind-tables -Xlinker --build-id=none
