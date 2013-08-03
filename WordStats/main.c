
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define true  1
#define false 0

#define debug 1

// I don't think most words are going to be longer than 512 characters :P
#define MAX_WORD_LENGTH 512

#include "word_functs.h"
int main(void){
	
	printf("Choose a file to analyze...\n");
	
	//create word files directory
	CreateDirectory(WORD_FILES_PATH, NULL);
	
	//load program
	FILE *document = choose_file();
	//if the file was unsucessfully loaded, quit the program.
	if(document == NULL){
		printf("Failed to load file\n");
		return 0;
	}
	
	//open debug file
	#if debug
	FILE *debugFile = fopen("debug.txt", "w");
	if(debugFile == NULL) printf("Couldn't open debug.txt file.\n");
	#endif
	
	//these are two arrays to hold the current word and the previous word that the program analyzed.
	//words[0][] = current word
	//words[1][] = previous word
	char words[2][MAX_WORD_LENGTH] = {"",""};
	char nonWordChars[] = " .,!?*|\\/<>:\n\r\t\"\'()[]{};"; // this holds all of the non-word characters
	int totalNonWordChars = strlen(nonWordChars); // get the length of the nonWordChars string.
	
	int i=0,j=0; // this is the integer to count through the current string
	int wordsAnalyzed=0; // this tells us how many words we have analyzed.
	int startedNewWord=true; // this tells us if we just started a new word
	
	//go through the document and collect word data.
	while(1){
		words[0][i] = fgetc(document); // input a single character
		if(feof(document)) break;
		
		//check to see if there is a non-word character being read
		for(j=0;j<totalNonWordChars; j++){
			if(words[0][i] == nonWordChars[j]){ // if you encounter a non-word character, you have reached the end of the word.
				//if there are no valid characters in the word yet
				if(i==0){
					//don't treat this as the end of a word. just skip over it.
					words[0][0] = '\0';
					startedNewWord = true;
					break;
				}
				// set current character to end of string.
				words[0][i] = '\0';
				// as long as this isn't the first word being analyzed
				if(wordsAnalyzed>0)
					// add the relationship that the previous word is followed by the current one.
					add_word_relationship(words[0], words[1]);
				
				wordsAnalyzed++;
				
				#if debug
				//only if the word is valid, print it to the debug file.
				if(words[0][0] != '\0'){
					fprintf(debugFile, "%7d - %s\n", wordsAnalyzed, words[0]);
				}
				#endif
				
				//move the current word (words[0]) into the previous word (words[1])
				strcpy(words[1], words[0]);
				//blank the current word
				words[0][0] = '\0';
				
				//we have started a new word.
				startedNewWord = true;
				break;
			}
		}
		// reset index if we are starting on a new word
		if(startedNewWord == true){
			i=0;
			startedNewWord = false;
		}
		// increment index if we are going to keep working on our current word
		else i++;
	}
	
	printf("\nFinished analyzing document.\nAnalyzed %d words", wordsAnalyzed);
	#if debug
	fclose(debugFile);
	#endif // debug
	return 0;
}

