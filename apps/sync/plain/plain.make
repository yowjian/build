all:
	clang -o sync sync.c -lpthread

clean:
	rm -f *~ sync
