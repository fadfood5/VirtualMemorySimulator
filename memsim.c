#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int numWrites = 0;
int numReads = 0;

struct PageTableEntry{
	int pageNumber;
	char pN[7];
	char input_output;
	int dirtyBit;
	int counter;
	int clk;
};

void vms(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	unsigned a;
	char b;

	if (file) {
	    while ((c = getc(file)) != EOF){
					fscanf(file, "%x %c", &a, &b);
					if(strcmp(type, "debug") == 0)
							printf("%u", a);
							printf(" %c\n", b);
					}
					fclose(file);
	}
}

void lru(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	char a[7];
	char b;
	char temp;

	struct PageTableEntry Frames[fr];
	int count = 0;

	if (file) {
	    while ((c = getc(file)) != EOF){
					struct PageTableEntry p;
					//Frames[count] = p;
					//count++;
					fscanf (file, "%s %c", a, &b);

					if(strcmp(type, "debug") == 0){
							printf("%s", a);
							printf(" %c\n", b);
							strncpy(p.pN, a, 5);
							printf("Decimal: %s \n", p.pN);
						}
				}
			fclose(file);
	}
}

void clk(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	unsigned a;
	char b;

	if (file) {
	    while ((c = getc(file)) != EOF){
					fscanf(file, "%x %c", &a, &b);
					if(strcmp(type, "debug") == 0)
							printf("%u", a);
							printf(" %c\n", b);
					}
					fclose(file);
	}
}

void opt(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	unsigned a;
	char b;

	if (file) {
	    while ((c = getc(file)) != EOF){
					fscanf(file, "%x %c", &a, &b);
					if(strcmp(type, "debug") == 0)
							printf("%u", a);
							printf(" %c\n", b);
					}
					fclose(file);
	}
}

//Reads trace file
void readTrace(const char *fileName, int frames, const char *alg, const char *type){
	if(strcmp(alg, "vms") == 0)
		vms(fileName, frames, type);
	else if(strcmp(alg, "lru") == 0)
		lru(fileName, frames, type);
	else if(strcmp(alg, "clk") == 0)
		clk(fileName, frames, type);
	else if(strcmp(alg, "opt") == 0)
		opt(fileName, frames, type);
	else
		printf("Incorrect algorithm input\n");
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
