#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//Reads trace file
void readTrace(const char *a){
	int c;
	FILE *file;
	file = fopen(a, "r");
	unsigned addr;
	char rw;
	int i = 0;

	if (file) {
	    while ((c = getc(file)) != EOF){
					//fscanf(file, "%x %c", arr[0], arr[1]);
					putchar(c);
					i++;
			}
	    fclose(file);
	}
}

//Reads commanf parameters from console
int main(int argc, char **argv){
		const char *a[2];
    for (int i = 0; i < argc; ++i){
        printf("argv[%d]: %s\n", i, argv[i]);
				a[i] = argv[i];
				printf("Added %s\n", a[i]);
    }
		readTrace(a[1]);
		return 0;
}
