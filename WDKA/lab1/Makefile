CC = clang
CFLAGS = -Weverything -Wpedantic

all: zad10.out zad9.out zad32.out

zad%.out: zad%.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm *.out

