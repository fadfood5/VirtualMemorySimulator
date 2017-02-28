#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int numWrites = 0;
int numReads = 0;
int traces = 0;
int numHits = 0;

struct PageTableEntry{
	char pN[5];
	char input_output;
	int dirtyBit;
	int counter;
	int clk;
	int found;
	int index;
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
					traces++;
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
					p.found = 0;
					p.index = 0;

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
							numHits++;
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
	if(strcmp(type, "debug") == 0){
		printf("Final form is: \n");
		for(int i =0; i < fr; i++){
			printf("%s\n", Frames[i].pN);
			printf("%d\n", Frames[i].counter);
		}
	}
	printf("Num of traces: %d\n", traces);
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
	printf("Num of hits: %d\n", numHits);

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
					traces++;
					//Create a page table entry struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", a, &b);
					//Cut down string to page number
					strncpy(p.pN, a, 5);
					//Set read/write to b
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
					if(b == 'W')
						p.dirtyBit = 1;
					else
						p.dirtyBit = 0;

					p.counter = 0;
					p.clk = 1;
					p.found = 0;
					p.index = 0;

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
							//Take free space
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
							numHits++;
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
							}
							//Set clk to 1
							Frames[i].clk = 1;
							break;
						}


						else{
							//If array full and not found
							if(i+1 == fr){
								//Scan array for clk bit == 0, if 1 set to 0
								for(int j = 0; j < fr; j++){
									if(Frames[j].clk == 1){
										//If they were all 1, Frames[0] gets swapped out
										if(fr == j - 1){
											if(Frames[0].input_output == 'W')
												numWrites++;
											numReads++;
											Frames[0] = p;
											if(strcmp(type, "debug") == 0){
												printf("Disk Read Performed\n");
												if(Frames[0].input_output == 'W')
													printf("Disk Write Performed\n");
											}
										}
										else
											Frames[j].clk = 0;
									}

									else if(Frames[j].clk == 0){
										if(p.input_output == 'W')
											numWrites++;
										numReads++;
										if(strcmp(type, "debug") == 0){
											printf("Disk Read Performed\n");
											if(p.input_output == 'W')
												printf("Disk Write Performed\n");
										}

										Frames[j] = p;
										break;

									}
								}
							}
						}
					}

		}
	}

	fclose(file);
	printf("Final form is: \n");
	for(int i =0; i < fr; i++){
		Frames[i].counter++;
		printf("%s\n", Frames[i].pN);
		printf("%d\n", Frames[i].counter);
	}

	printf("Num of traces: %d\n", traces);
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
	printf("Num of hits: %d\n", numHits);
}

void opt(const char *fileName, int fr, const char *type){
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	int i = 0;
	char a[5];
	char b;
	char e;
	char temp;
	int count = 0;
	int count2 = 0;

	struct PageTableEntry Frames[fr];

	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		if(strcmp(type, "debug") == 0)
			printf("Created empty struct\n");
	}

	int c1=0, c2=0, c3=0;

	if (file) {
			//Run through file by line
	    while ((c = getc(file)) != EOF){
					traces++;
					//Create a page table entry struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", a, &b);
					//Cut down string to page number
					strncpy(p.pN, a, 5);
					//Set read/write to b
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
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
							c1++;
							//Take free space
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
							numHits++;
							c2++;
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
							}
							break;
						}else{
							//If array full and not found
							if(i+1 == fr){
								c3++;
								char *FramesTemp[fr];
								int temp = count;

								FILE *file2;
								file2 = fopen(fileName, "r");

								int ch;
								int newlines = 0;
								if(file2){
									while ((ch = getc(file)) != EOF) {
											char d[8];
							        if (newlines >= temp - 1 && newlines<= temp+fr-1){
													fscanf (file2, "%s %c", d, &e);
												//Cut down string to page number
												// for(int n=0; n<5; n++){
												// 	FramesTemp[count2][n] = d[n];
												// }
												//strncpy(d, d, 5);

													printf("D is: %s\n", d);
													printf("Count: %d\n", count2);
												strncpy(FramesTemp[count2], d, 5);

													printf("kms2\n");
												//FramesTemp[count2] = d.c_str();
												printf("%s\n", FramesTemp[count2]);
												count2++;
											}
							        newlines++;
									}
							}
							fclose(file2);
							for(int i = 0; i < fr; i++){
								for(int j = 0; j < fr; j++){
									if(strcmp(Frames[i].pN, FramesTemp[j]) == 0){
										Frames[i].found = 1;
										Frames[i].index = j;
									}
								}
							}

							int max = 0;
							if(Frames[0].found == 1)
								max = Frames[0].index;

							int test = 0;
							int tempL = 0;
							for(int l = 0; l<fr; l++){
								if(Frames[l].found == 0){
								test = 1;
								tempL = l;
								break;
							}else{
								if(max < Frames[l].index)
									max = Frames[l].index;
							}
						}
							if(test == 1){
								Frames[tempL] = p;
								numReads++;
								numWrites++;
							}else{
								for(int m = 0; m<fr; m++){
									if(max == Frames[m].index){
										numReads++;
										numWrites++;
										break;
									}
								}
							}

							}
						}
					}
					count++;
					//printf("Count: %d\n", count);
		}
	}

	fclose(file);
	printf("Final form is: \n");
	for(int i =0; i < fr; i++){
		Frames[i].counter++;
		printf("%s\n", Frames[i].pN);
		printf("%d\n", Frames[i].counter);
	}
	printf("Count1: %d\n", c1);
	printf("Count2: %d\n", c2);
	printf("Count3: %d\n", c3);
	printf("Num of traces: \n");
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
}

//Reads trace file
void readTrace(const char *fileName, int frames, const char *alg, const char *type){
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
	if(strcmp(argv[4], "debug") == 0){
    for (int i = 0; i < argc; ++i)
				printf("Added %d: %s\n", i, argv[i]);

		printf("frame: %s \n", argv[2]);
	}
		int c = atoi(argv[2]);
		readTrace(argv[1], c, argv[3], argv[4]);

		return 0;
}
