
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define bool char
#define true  1
#define false 0

#define debug 1

// I don't think most words are going to be longer than 512 characters :P
#define MAX_WORD_LENGTH 512

#include "word_functs.h"
int main(void){
	int i;
	printf("Choose a file to analyze...\n");
	//load the document to analyze
	FILE *document = choose_file();
	//if the file was unsucessfully loaded, quit the program.
	if(document == NULL){
		printf("Failed to load file\n");
		return 0;
	}
	system("rmdir \"words\" /q /s"); // quietly removes the words directory
	//create word files directory
	CreateDirectory(WORD_FILES_PATH, NULL);
	
	//open debug file
	#if debug
	FILE *debugFile = fopen("debug.txt", "w");
	if(debugFile == NULL) printf("Couldn't open debug.txt file.\n");
	#endif
	
	//these are two arrays to hold the current word and the previous word that the program analyzed.
	//words[0][] = current word
	//words[1][] = previous word
	char words[2][MAX_WORD_LENGTH] = {"",""};
	
	//this keeps track of the frequency of each chracter
	unsigned long int freq[256];
	for(i=0; i<256; i++) freq[i] = 0; // reset freq elements.
	unsigned long int charactersAnalyzed=0; // keeps track of how many characters have been analyzed
	
	int wordsAnalyzed=0; // this tells us how many words we have analyzed.
	
	time_t startTime = time(NULL);
	i=0;
	while(1){
		//get character from the document.
		words[0][i] = fgetc(document);
		freq[(int)words[0][i]]++; // increment this character's frequency.
		charactersAnalyzed++; // increment the number of characters analyzed
		
		//if the character input was a valid word-character
		if(    (words[0][i]>='A'&&words[0][i]<='Z') // uppercase letters
			|| (words[0][i]>='a'&&words[0][i]<='z') // lowercase letters
			|| (words[0][i]>='0'&&words[0][i]<='9') // numbers
			|| words[0][i] == '-'
			|| words[0][i] == '_'){
					
			//if the character is uppercase
			if(words[0][i]>='A'&&words[0][i]<='Z')
				// make it lowercase (by adding 32)
				words[0][i]+= 0x20;
			
			//increment index
			i++;
		}
		else{
			//end the word
			words[0][i] = '\0';
			//if this word is at least a character long and it has at least one alphabetic letter (a-z)
			if(i>0 && has_some_lowercase_letter(words[0])){
				//if the previous word is valid
				if(words[1][0] != '\0')
					//add relationship
					add_word_relationship(words[0], words[1]);
				//increment words analyzed
				wordsAnalyzed++;
				#if debug
				fprintf(debugFile, "%6.6d %s\n", wordsAnalyzed, words[0]);
				#endif // debug
				//copy the current word into the last word.
				strcpy(words[1], words[0]);
				//reset index.
				i=0;
			}
			//if you reached the end of the document stop reading in the document
			if(feof(document)) break;
		}
	}
	
	//calculate time it took.
	time_t executionTime = difftime(time(NULL), startTime);
	if(executionTime<1)executionTime = 1; // this solves the divide by zero errors
	
	///old loop
	/*
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
	*/
	
	printf("\nFinished analyzing document.\nAnalysis took %d seconds.\nAnalyzed %d words.\nAnalyzed %lu characters.\n\n", (int)executionTime, wordsAnalyzed, charactersAnalyzed);
	float averageWordLength = ((float)charactersAnalyzed)/((float)wordsAnalyzed);
	int wordsPerSecond = wordsAnalyzed/executionTime;
	int charactersPerSecond = charactersAnalyzed/executionTime;
	printf("On average, the words were %.2f characters long.\nAnalysis ran at %d words per second.\nAnalysis ran at %d characters per second.\n", averageWordLength, wordsPerSecond, charactersPerSecond);
	
	//print character frequency results to a file
	FILE *charFreqFile = fopen("Character Frequency.txt", "w");
	if(charFreqFile != NULL){
		fprintf(charFreqFile,"#character number - character - number of times the character appears\n");
		for(i=0; i<256; i++){
			fprintf(charFreqFile, "#%d - %c - %lu\n",i, (char)i, freq[i]);
		}
		fclose(charFreqFile);
	}
	
	#if debug
	fclose(debugFile);
	#endif // debug
	//close the document file
	if(document != NULL) fclose(document);
	return 0;
}

