sleep: boot.s sleep.c
	gcc -nostartfiles -static -Os -nodefaultlibs -nostdlib -no-canonical-prefixes -s -o $@ $^ -flto -Xlinker -n -Wall -Wextra -Wpedantic -Wshadow -Qn -std=c18
