#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//Reads trace file
void readTrace(const char *fileName, int frames, const char *alg, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	unsigned addr;
	char rw;
	int i = 0;

	if (file) {
	    while ((c = getc(file)) != EOF){
					//fscanf(file, "%x %c", arr[0], arr[1]);
					if(strcmp(type, "debug") == 0)
							putchar(c);
					i++;
			}
	    fclose(file);
	}
}

//Reads command parameters from console
int main(int argc, char **argv){
		//const char *a[2];
    for (int i = 0; i < argc; ++i){
				//a[i] = argv[i];
				printf("Added %s\n", argv[i]);
    }
		readTrace(argv[1], argv[2], argv[3], argv[4]);

		return 0;
}
