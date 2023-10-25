CC = clang
CFLAGS = -Weverything -Wpedantic -Wno-declaration-after-statement -Wno-vla

all: zad10.out zad9.out zad32.out

zad%.out: zad%.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm *.out

