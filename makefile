memsim.o: memsim.c
		gcc -c memsim.c -o memsim.o

clean:
		-rm -f memsim.o
