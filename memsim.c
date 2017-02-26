#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int numWrites = 0;
int numReads = 0;

struct PageTableEntry{
	char pN[5];
	char input_output;
	int dirtyBit;
	int counter;
	int clk;
};

void lru(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	char a[5];
	char b;
	char temp;

	struct PageTableEntry Frames[fr];

	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		if(strcmp(type, "debug") == 0)
			printf("Created empty struct\n");
	}

	if (file) {
			//Run through file by line
	    while ((c = getc(file)) != EOF){
					//Create a temporary struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", a, &b);
					//Cut down string to page number
					strncpy(p.pN, a, 5);
					//Set read/write to empty
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
					if(b == 'W')
						p.dirtyBit = 1;
					else
						p.dirtyBit = 0;

					p.counter = 0;
					p.clk = 0;

					//Debug
					if(strcmp(type, "debug") == 0){
							printf("%s", a);
							printf(" %c\n", b);
							printf("Page Number: %s\n", p.pN);
							printf("Input: %c\n", p.input_output);
					}

					//Go through array of structs
					for(int i = 0; i < fr; i++){
						//If array not full and has space
						if(strcmp(Frames[i].pN, "EMPTY") == 0){
							//Take that space
							Frames[i] = p;
							numReads++;
							//Debug
							if(strcmp(type, "debug") == 0){
								printf("Disk Read Performed\n");
								printf("Free space available\n");
								printf("Frame added: %s\n", Frames[i].pN);
								printf("Breaking\n");
							}
							break;
					}

						else if(strcmp(p.pN, Frames[i].pN) == 0){
							//If page number is already in array
							//Debug
							if(strcmp(type, "debug") == 0)
								printf("Already exists\n");
							//Switch input_output
							if(Frames[i].input_output == 'R' && p.input_output == 'W'){
								Frames[i].input_output = 'W';
								Frames[i].dirtyBit = 1;
							}
							else if(Frames[i].input_output == 'W' && p.input_output == 'R')
								Frames[i].input_output = 'R';
							//Set counter to 0
							Frames[i].counter = 0;
						}

						else if(i+1 == fr){
								//If array full and page number not found
								//Get highest counter
								int max = Frames[0].counter;
								int tempJ = 0;
								for(int j = 0; j < fr; j++){
									if(Frames[j].counter > max){
										max = Frames[j].counter;
										tempJ = j;
									}
								}
								//If highest counter's input_output is write, switch out page number
								if(Frames[tempJ].input_output == 'W'){
									numWrites++;
									if(strcmp(type, "debug") == 0)
										printf("Disk Write Performed\n");
								}

								Frames[tempJ] = p;
								numReads++;
						}
					}

				if(strcmp(type, "debug") == 0)
					printf("Disk read performed\n");
				for(int i = 0; i < fr; i++){
					Frames[i].counter += 1;
				}
			}

	//Close file
	fclose(file);
	//Print final array elements
	printf("Final form is: \n");
	for(int i =0; i < fr; i++){
		printf("%s\n", Frames[i].pN);
		printf("%d\n", Frames[i].counter);
	}
	printf("Num of traces: \n");
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);

}
}


void clk(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	char a[5];
	char b;
	char temp;

	struct PageTableEntry Frames[fr];

	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		if(strcmp(type, "debug") == 0)
			printf("Created empty struct\n");
	}

	if (file) {
			//Run through file by line
	    while ((c = getc(file)) != EOF){
					//Create a temporary struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", a, &b);
					//Cut down string to page number
					strncpy(p.pN, a, 5);
					//Set read/write to empty
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
					p.input_output = 0;
					if(b == 'W')
						p.dirtyBit = 1;
					else
						p.dirtyBit = 0;

					p.counter = 0;
					p.clk = 0;

					if(strcmp(type, "debug") == 0){
							printf("%s", a);
							printf(" %c\n", b);
							printf("Page Number: %s\n", p.pN);
							printf("Input: %c\n", p.input_output);
						}

					//Go through array of structs
					for(int i = 0; i < fr; i++){
						//If array not full and has space
						if(strcmp(Frames[i].pN, "EMPTY") == 0){
							//Change counter and take space
							if(p.input_output == 'R'){
								p.counter = 0;
							else
								p.counter = 1;

							Frames[i] = p;
							numReads++;
							//Debug
							if(strcmp(type, "debug") == 0){
								printf("Disk Read Performed\n");
								printf("Free space available\n");
								printf("Frame added: %s\n", Frames[i].pN);
								printf("Breaking\n");
							}
							break;
					}else if(strcmp(p.pN, Frames[i].pN) == 0){
							//If page number is already in array
							//Debug
							if(strcmp(type, "debug") == 0)
								printf("Already exists\n");
							if(Frames[i].input_output == 'R' && p.input_output == 'W'){
								Frames[i].input_output = 'W';
								Frames[i].dirtyBit = 1;
							}
							else if(Frames[i].input_output == 'W' && p.input_output == 'R'){
								Frames[i].input_output = 'R';
								dirtyBit = 0;
							}
							//Set counter to 0
							Frames[i].counter = 0;
							Frames[i].clk = 1;
						}else
							if(i+1 == fr){
								for(int j = 0; j < fr; j++){
									if(Frames[j].clk == 1)
										Frames[j].clk = 0;
									else{
									numWrites++;
									numReads++;
									if(strcmp(type, "debug") == 0){
										printf("Disk Write Performed\n");
										printf("Disk Read Performed\n");
									}
										if(p.input_output == 'W')
											Frames[j] = p;
										else
											Frames[0] = p;
									}
								}
					}
			}
		if(strcmp(type, "debug") == 0)
			printf("Disk read performed\n");
		for(int j = 0; j < fr; j++){
			Frames[j].counter += 1;
	}
}
fclose(file);
printf("Final form is: \n");
for(int i =0; i < fr; i++){
	Frames[i].counter++;
	printf("%s\n", Frames[i].pN);
	printf("%d\n", Frames[i].counter);
}
	printf("Num of traces: \n");
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
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
	/*if(strcmp(alg, "vms") == 0)
		vms(fileName, frames, type);*/
	if(strcmp(alg, "lru") == 0)
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
