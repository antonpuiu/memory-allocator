build: allocator.c
	gcc allocator.c -o allocator -lm

clean:
	rm allocator
