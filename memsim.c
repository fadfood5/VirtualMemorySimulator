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
	//Declare file buffer and open it
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	char b;

	//Declare array of structures the size of frame number
	struct PageTableEntry Frames[fr];

	//Set structures in array as empty
	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		if(strcmp(type, "debug") == 0)
			printf("Created empty struct\n");
	}

	//If file is not null
	if (file) {
			//Run through file by line
	    while ((c = getc(file)) != EOF){
					traces++;
					//Create a temporary struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", p.pN, &b);
					//Cut down string to page number
					p.pN[5] = '\0';
					//Set read/write to empty
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
					if(b == 'W')
						p.dirtyBit = 1;
					else
						p.dirtyBit = 0;
					//Set other values of struct to zero
					p.counter = 0;
					p.clk = 0;
					p.found = 0;
					p.index = 0;

					//Debug
					if(strcmp(type, "debug") == 0){
							p.pN[5] = '\0';
							printf("Page Number: %s\n", p.pN);
							printf("Input: %c\n", b);
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

								Frames[i].pN[5] = '\0';
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
								printf("Already exists\n\n");
							//Switch input_output
							if(Frames[i].input_output == 'R' && p.input_output == 'W'){
								Frames[i].input_output = 'W';
								Frames[i].dirtyBit = 1;
							}
							else if(Frames[i].input_output == 'W' && p.input_output == 'R')
								Frames[i].input_output = 'R';
							//Set counter to 0
							Frames[i].counter = 0;
							break;
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
								if(Frames[tempJ].dirtyBit == 1){
									numWrites++;
									if(strcmp(type, "debug") == 0)
										printf("Disk Write Performed\n");
								}

								//Replace and increment numReads
								Frames[tempJ] = p;
								numReads++;
								//Debug
								if(strcmp(type, "debug") == 0)
									printf("Disk Read Performed\n\n");
						}
					}

				//Increment counter of each struct of array
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
			Frames[i].pN[5] = '\0';
			printf("%s\n", Frames[i].pN);
		}
	}
	//Print summary
	printf("Num of traces: %d\n", traces);
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
	printf("Num of hits: %d\n", numHits);

}
}


void clk(const char *fileName, int fr, const char *type){
	//Declare file buffer and open it
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	char b;
	//Declare array of structures the size of frame number
	struct PageTableEntry Frames[fr];

	//Set structures in array as empty
	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		//Debug
		if(strcmp(type, "debug") == 0)
			printf("Created empty struct\n");
	}

	if (file) {
			//Run through file by line
	    while ((c = getc(file)) != EOF){
					traces++;
					//Create a page table entry struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", p.pN, &b);
					//Cut down string to page number
					p.pN[5] = '\0';
					//Set read/write to b
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
					if(b == 'W')
						p.dirtyBit = 1;
					else
						p.dirtyBit = 0;
					//Set other values of struct to zero
					p.counter = 0;
					p.clk = 1;
					p.found = 0;
					p.index = 0;
					//Debug
					if(strcmp(type, "debug") == 0){
							p.pN[5] = '\0';
							if(strcmp(type, "debug") == 0){
								printf("Page Number: %s\n", p.pN);
								printf("Input: %c\n", b);
							}
						}

					//Go through array of structs
					for(int i = 0; i < fr; i++){
						//If array not full and has space
						if(strcmp(Frames[i].pN, "EMPTY") == 0){
							//Take free space and increment numReads
							Frames[i] = p;
							numReads++;
							//Substring to get page number
							Frames[i].pN[5] = '\0';
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
								printf("Already exists\n\n");
							//Update input_output and dirtyBit
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
											//Increment numReads and numWrites
											if(Frames[0].dirtyBit == 1)
												numWrites++;
											numReads++;
											Frames[0] = p;
											//Debug
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
										//Increment numReads and numWrites
										if(Frames[j].dirtyBit == 1)
											numWrites++;
										numReads++;
										//Debug
										if(strcmp(type, "debug") == 0){
											printf("Disk Read Performed\n");
											if(p.input_output == 'W')
												printf("Disk Write Performed\n");
										}
										if(strcmp(type, "debug") == 0)
											printf("\n");
										Frames[j] = p;
										break;

									}
								}
							}
						}
					}

		}
	}

	//CLose file buffer
	fclose(file);
	//Debug
	if(strcmp(type, "debug") == 0){
		printf("Final form is: \n");
		for(int i =0; i < fr; i++){
			Frames[i].pN[5] = '\0';
			printf("%s\n", Frames[i].pN);
		}
	}

	//Print Summary
	printf("Num of traces: %d\n", traces);
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
	printf("Num of hits: %d\n", numHits);
}

void opt(const char *fileName, int fra, const char *type){
	//Declare file buffer and open it
	int c;
	FILE *file;
	file = fopen(fileName, "r");
	char b;
	int count = 0;
	const int fr = fra;

	//Declare array of structures the size of frame number
	struct PageTableEntry Frames[fr];

	//Set structures in array as empty
	for(int i = 0; i < fr; i++){
		struct PageTableEntry temp;
		strncpy(temp.pN, "EMPTY", 5);
		Frames[i] = temp;
		if(strcmp(type, "debug") == 0)
			printf("Created  struct\n");
	}

	//Store all lines in an array to be able to see future values during opt
	int counting = 0;
	char all[1000000][8];
	//Open file
	FILE *file2;
	file2 = fopen(fileName, "r");
	int chh;
	//If file not null
	if(file2){
		while ((chh = getc(file2)) != EOF) {
			//Scan
			fscanf (file2, "%s %c", all[counting], &b);
			//Substring to get page number
			all[counting][5] = '\0';
			counting++;
		}
	}
	//Close File Buffer
	fclose(file2);

	//If file is not null
	if (file) {
			//Run through file by line
	    while ((c = getc(file)) != EOF){
					traces++;
					//Create a page table entry struct
					struct PageTableEntry p;
					fscanf (file, "%s %c", p.pN, &b);
					//Cut down string to page number
					p.pN[5] = '\0';
					//Set read/write to b
					strncpy(&p.input_output, &b, 1);
					//Set dirty bit based on read/write being scanned
					if(b == 'W')
						p.dirtyBit = 1;
					else
						p.dirtyBit = 0;
					//Set other values of struct to zero
					p.counter = 0;
					p.clk = 0;

					//Debug
					if(strcmp(type, "debug") == 0){
							printf("Page Number: %s\n", p.pN);
							printf("Input: %c\n", b);
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
							//Switch input_output
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
								//Get current line
								int temp = count;
								//Declare temp array and counter of array
								char allTemp[fr][8];
								int counting2 = 0;
								//Look into the future and place in array
								for(int i = temp; i < temp+fr; i++){
									if(temp+fr < 1000001){
										strcpy(allTemp[counting2], all[i]);
										allTemp[counting2][5] = '\0';
										if(strcmp(type, "debug") == 0)
											printf("%s\n", allTemp[counting2]);
										counting2++;
									}
								}
								//Debug
								if(strcmp(type, "debug") == 0)
									printf("\n");

								//Check if found and update index
								for(int i = 0; i < fr; i++){
									for(int j = 0; j < fr; j++){
										if(strcmp(Frames[i].pN, allTemp[j]) == 0){
											Frames[i].found = 1;
											Frames[i].index = j;
										}
									}
								}

								//Set max to index of first struct of array
								int max = 0;
								if(Frames[0].found == 1)
									max = Frames[0].index;
								//Check if found
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
								//
								if(test == 1){
									//Increment numWrites
									if(Frames[tempL].dirtyBit == 1){
										numWrites++;
										//Debug
										if(strcmp(type, "debug") == 0)
											printf("Disk Write Performed");
									}
									//Replace and increment numReads
									Frames[tempL] = p;
									numReads++;
									//debug
									if(strcmp(type, "debug") == 0)
										printf("Disk Read Performed");
								}else{
									//Loop through array of structs and increment numReads if equal to max
									for(int m = 0; m<fr; m++){
										if(max == Frames[m].index){
											numReads++;
											//Debug
											if(strcmp(type, "debug") == 0)
												printf("Disk Read Performed");
											//Increment numWrites
											if(Frames[m].dirtyBit == 1){
												numWrites++;
												//Debug
												if(strcmp(type, "debug") == 0);
													printf("Disk Write Performed");
											//Replace
											Frames[m] = p;
											break;
											}
										}
									}
								}

								}
							}
						}
						//Keep track of current line
						count++;
		}
	}
	//Close file buffer
	fclose(file);
	//Debug
	if(strcmp(type, "debug") == 0){
		printf("Final form is: \n");
		for(int i = 0; i < fr; i++){
			Frames[i].pN[5] = '\0';
			printf("%s\n", Frames[i].pN);
		}
	}
	//Print Summary
	printf("Num of traces: %d\n", traces);
	printf("Num of frames: %d\n", fr);
	printf("Num of disk reads: %d\n", numReads);
	printf("Num of disk writes: %d\n", numWrites);
	printf("Num of hits: %d\n", numHits);
}

//Call function based on input (router)
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
	//Debug
	if(strcmp(argv[4], "debug") == 0){
    for (int i = 0; i < argc; ++i)
				printf("Added %d: %s\n", i, argv[i]);

		printf("frame: %s \n", argv[2]);
	}
		//Convert num of frames from string to integer
		int c = atoi(argv[2]);
		//Call that routing function
		readTrace(argv[1], c, argv[3], argv[4]);

		return 0;
}
