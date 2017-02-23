#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int numWrites = 0;
int numReads = 0;

struct PageTableEntry{
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
		printf("fr %d: ", fr);
	struct PageTableEntry Frames[fr];
	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		printf("Temp: %s\n", temp.pN);
		printf("Created empty struct\n");
	}
	int count = 0;

	if (file) {
	    //while ((c = getc(file)) != EOF){
					struct PageTableEntry p;
					fscanf (file, "%s %c", a, &b);

					if(strcmp(type, "debug") == 0){
							printf("%s", a);
							printf(" %c\n", b);
							strncpy(p.pN, a, 5);
							p.input_output = b;
							printf("Page Number: %s\n", p.pN);
							printf("Input: %c\n", p.input_output);
						}

					for(int i = 0; i < fr; i++){
						if(strcmp(Frames[i].pN, "EMPTY") == 0){
							Frames[i] = p;
							if(strcmp(type, "debug") == 0){
								printf("Free space available\n");
								printf("Frame added: %s\n", Frames[i].pN);
								printf("Breaking\n");
							}
							break;
					}else if(strcmp(p.pN, Frames[i].pN) == 0){
							printf("Already exists\n");
							if(strcmp(Frames[i].input_output, "R") == 0)
								Frames[i].input_output = 'W';
							else
								Frames[i].input_output = 'R';
						}else{

						}
					}
	}
fclose(file);
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
	printf("%d\n", argc);
    for (int i = 0; i < argc; ++i)
				printf("Added %d: %s\n", i, argv[i]);

		printf("frame: %s \n", argv[2]);
		int c = atoi(argv[2]);
		readTrace(argv[1], c, argv[3], argv[4]);

		return 0;
}
