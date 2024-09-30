collatz: collatz.c cache.c
	gcc -o collatz collatz.c cache.c

clean:
	rm -f collatz