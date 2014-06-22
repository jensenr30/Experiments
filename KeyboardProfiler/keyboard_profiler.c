/**
keyboard Profiler
Written by Ryan Jensen
2014-06-15
The purpose of this program is to generate statistics about written documents regarding key strokes.
The intended uses for this program are for:
	- generating a profile for the English language so that a program can be written to randomly create words that look "English-like"
	- writing a program that analyzes keyboard layouts and, through a series of genetic algorithms, optimizes a keyboard layout for speed and comfort.
However, I'm sure that anyone with a little bit of creativity could think of a good use for this program.
*/

/*
This program can be used via command line using the following formats:

// keyprof will compute statistics on the follow document, "myBook.txt"
// the statistics will be written to the default file location (which is in the same directory as keyprof.exe).
// if the default file already has data in it, keyprof will merge (add) the data gathered to any existing

	> keyprof.exe C:\Documents\myBook.txt

// keyprof will compute statistics on both documents (the text file and the source code) are save findings in the default file path.
	
	> keyprof.exe C:\Documents\myBook.txt C:\Programming\my_source_code.c

// by default, keyprof.exe will merge the data calculated in its current execution to any data that was calculated in a previous execution.
// if you want to make keyprof.exe erase any old data before writing the current data to file, use the option, "--overwrite"
	
	> keyprof.exe --overwrite C:\Documents\myBook.txt
	
// if you want to specify an output file, then simply use the option, "--output-file"
// note that the argument after "--output-file" is the output path.
// all other arguments will be interpreted as input files for calculating keyboard statistics.
	
	> keyprof.exe --output-file C:\Data\Custom_Output_File.txt C:\Documents\myBook.txt
	

**/



#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "keyboard_profiler.h"



// logs string to file
void keyprof_log(char *string){
	FILE *log = fopen(KEYPROF_LOG_FILE_NAME, "a");
	if(log != NULL) fprintf(log, "%s\n", string);
	fclose(log);
}
// logs string and integer to file
void keyprof_log_d(char *string, int data){
	FILE *log = fopen(KEYPROF_LOG_FILE_NAME, "a");
	if(log != NULL) fprintf(log, "%s\t%d\n", string, data);
	fclose(log);
}
// logs string and another string to file
void keyprof_log_s(char *string, char *data){
	FILE *log = fopen(KEYPROF_LOG_FILE_NAME, "a");
	if(log != NULL) fprintf(log, "%s\t%s\n", string, data);
	fclose(log);
}


void keyprof_init(){
	// initialize that keyDataString
	keyDataString = "abcdefghijklmnopqrstuvwxyz`-=[];',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~_+{}:\"<>?";
}

/// this will save keyData to file
short keyprof_save_stats(unsigned long long int *keyData, unsigned long long int *keyFrequency, unsigned long long int *keyStartingFrequency, unsigned long long int *wordLength, char *filePath){
	
	FILE *saveFile = fopen(filePath, "w");
	// make sure the file was opened correctly
	if(saveFile == NULL) return KEYPROF_FILE_NOT_FOUND;
	
	fprintf(saveFile, "\t");
	int f, s; // these record the character index f=first, s=second.
	for(f=0; f<KEYPROF_KEYS; f++) fprintf(saveFile, "%c\t", keyDataString[f]);
	fprintf(saveFile, "Next Character");
	// f is the cause and s is the effect.
	for(f=0; f<KEYPROF_KEYS; f++){
		fprintf(saveFile, "\n%c\t", keyDataString[f]);
		for(s=0; s<KEYPROF_KEYS; s++){
			// print the data for the number of times that the user presses [f] and then [s]
			/// TODO: figure out how to print unsigned long long
			fprintf(saveFile, "%lu\t", keyData[f*KEYPROF_KEYS+s]);
		}
	}
	
	// descrbe the y axis
	fprintf(saveFile, "\nGiven Character\n");
	
	
	// describe the following table
	fprintf(saveFile, "\n\nWord Length\tFrequency\n");
	// write the word length frequency data to file
	int l;
	for(l=1; l<KEYPROF_WORD_LENGTH_MAX; l++){
		fprintf(saveFile, "%d\t%lu\n", l, wordLength[l]);
	}
	
	
	// describe the character frequency table
	fprintf(saveFile, "\n\nCharacter\tFrequency\n");
	// write the character frequency to file
	int c;
	for(c=0; c<KEYPROF_KEYS; c++){
		fprintf(saveFile, "%c%c\t%lu\n", keyDataString[c], keyDataString[c+KEYPROF_KEYS], keyFrequency[c]);
	}
	
	fprintf(saveFile, "\n\nWord Starting Character\tFrequency\n");
	for(c=0; c<KEYPROF_KEYS; c++){
		fprintf(saveFile, "%c%c\t%lu\n", keyDataString[c], keyDataString[c+KEYPROF_KEYS], keyStartingFrequency[c]);
	}
	
	// close up shop when you leave
	fclose(saveFile);
	// success
	return 0;
}



/// this will add the statistics from the saved file to the keyData.
// this will NOT overwrite keyData. It will only add to it what was found in the file.
// returns 0 on success
// returns 1 on failure to load file
short keyprof_load_stats(char *filePath, unsigned long long int *keyData){
	
	FILE *loadFile = fopen(filePath, "w");
	// make sure the file was opened correctly
	if(loadFile == NULL) return KEYPROF_FILE_NOT_FOUND;
	
	
	// these are used to process the data from the loadFile
	//unsigned char charCurrent;
	//unsigned char charLast;
	//unsigned char charInput;
	
	
	while(1){
		//charInput = fgetc(loadFile);
		
		/// TODO: PROCESS INPUT DATA
		
		// break because there is nothing written in here yet
		break;
	}
	
	// close up shop when you leave
	fclose(loadFile);
	// success
	return 0;
}

/// this file will search an input file and determine if the text contains a certain word.
// returns 0 if the targetWord WASN'T found in the blackListFile.
// returns 1 if the targetWord WAS    found in the blackListFile.
// returns -1 if the blackListPath is NULL.
// returns -2 if the targetWord is NULL.
// return -3 if the function cannot open the blackListFile file.
short keyprof_find_string_in_blacklist(char *blackListPath, char *targetWord){
	
	if(blackListPath == NULL){
		keyprof_log("keyprof_find_string_in_file() was sent NULL blackListFile path string");
		return -1;
	}
	if(targetWord == NULL){
		keyprof_log("keyprof_find_string_in_file() was sent NULL targetWord.");
		return -2;
	}
	
	//attempt to open the blacklist file
	FILE *blackListFile = fopen(blackListPath, "r");
	if(blackListFile == NULL){
		keyprof_log("keyprof_find_string_in_file() could not open the blackListFile."); 
		return -3;
	}
	
	// calculate the length of targetWord.
	int targetWordLength = strlen(targetWord);
	
	// create a string that has the right length to be checked against the targetWord.
	char *inputWord = malloc(targetWordLength+1+2);
	
	
	// fill up the string initially with the first <targetWordLength> characters from the blacklist into the inputWord to prepare the data for the main while(1) loop.
	int i;
	// set the first character to a space
	inputWord[0] = ' ';
	// set the middle characters to the first <targetWordLength> characters from the blacklist file.
	for(i=1; i<targetWordLength+1; i++){
		//
		inputWord[i] = fgetc(blackListFile);
		// if you encounter to end of the file before you finishing inputting the first <targetWordLength> characters,
		if(inputWord[i] == EOF){
			// close the file
			fclose(blackListFile);
			// and report that it no match was found.
			return 0;
		}
	}
	// set the last  character to a space
	inputWord[targetWordLength+1] = ' ';
	// terminate the inputWord string will a null character.
	inputWord[targetWordLength+2] = '\0';
	
	
	// this variable will be used to tell if the inputWord matches the targetWord.
	uint_fast8_t match;
	while(1){
		
		// set the "match" variable to 1.
		//if the following code finds a discrepancy between the targetWord and the inputWord, it will set it to 0.
		match = 1;
		
		
		// if the letters on either side are alphabetic,
		if((inputWord[0] >= 'a' && inputWord[0] <= 'z') || (inputWord[0] >= 'A' && inputWord[0] <= 'Z')){
			// there is no match
			match = 0;
		}
		
		// only continue checking the inputWord against the targetWord if a discrepancy hasn't already been found
		if(match == 1){
			// check to see any of the word characters are different between the targetWord and the inputWord
			for(i=0; i<targetWordLength; i++){
				// if there is any discrepancy between the characters,
				if(inputWord[i+1] != targetWord[i]){
					// then the words don't match.
					match = 0;
					// stop checking this point in the blacklist file
					break;
				}
			}
		}
		
		// if you have found a match, 
		if(match == 1){
			// close the file
			fclose(blackListFile);
			// and report the match
			return 1;
		}
		
		// otherwise, shift the entire input word over
		for(i=0; i<targetWordLength+2-1; i++){
			inputWord[i+1] = inputWord[i];
		}
		// input a new character at the beginning of targetWordLength
		inputWord[0] = fgetc(blackListFile);
		
		if(inputWord[0] == EOF){
			// if you have reached the end of the file, break.
			//the code after this while(1) loop will close the blacklist file and return 0 because a match has not been found yet if the loop is still running
			// (when a match is found, the loop will exit, closing the file, and returning 1).
			break;
		}
		
		//otherwise, just start the loop over again and try to find a match on the next position of the blacklist
	}
	
	
	// close the blackListFile.
	fclose(blackListFile); 
	// successfully searched and DID NOT FIND the targetWord in the blacklist
	return 0;
}

/// this function will create a filtered version of a text file. whatever words appear in the blacklist file will be omitted from the return file.
// this function will create a new file based on the input file that lacks the words on the black list.
// this function returns...
	// 0 on success
	// 1 on null filePathInput
	// 2 on null filePathBlackList
	// 3 on null filePathReturn
	// 4 when the program cannot open filePathInput
	// 5 when the program cannot open filePathBlackList
	// 6 when the program cannot open fileReturn
short keyprof_create_filtered_file(char *filePathInput, char *filePathBlackList, char  *filePathReturn){
	
	//--------------------------------------------
	// make sure all pointers are functioning.
	//--------------------------------------------
	
	// check to make sure that the filePathInput pointer is valid.
	if(filePathInput == NULL){
		keyprof_log("keyprof_create_filtered_file() received null input variable. filePathInput = NULL");
		return 1;
	}
	// check to make sure that the filePathBlackList pointer is valid.
	if(filePathBlackList == NULL){
		keyprof_log("keyprof_create_filtered_file() received null input variable. filePathBlackList = NULL");
		return 2;
	}
	// check to make sure that the fileReturnPath pointer is valid.
	if(filePathReturn == NULL){
		keyprof_log("keyprof_create_filtered_file() received null input variable. filePathReturn = NULL");
		return 3;
	}
	
	// attempt to open the input file
	FILE *fileInput = fopen(filePathInput, "r");
	if(fileInput == NULL){
		keyprof_log("keyprof_create_filtered_file() could not open the fileInput");
		return 4;
	}
	//attempt to open the return file
	FILE *fileReturn = fopen(filePathReturn, "r");
	if(fileReturn == NULL){
		keyprof_log("keyprof_create_filtered_file() could not open the fileReturn."); 
		return 6;
	}
	
	
	/// TODO: write function that filters the input text document.
	/// somehow you will need to use the keyprof_find_string_in_blacklist() function.
	
	
	
	return 0; // successfully applied a black list to the file.
}


/// this will perform the statistical number crunching on the input files.
// this will take a text file and reduce it to numbers in an array that describe how it works.
// keyData is a pointer to an array of ULL integers that is KEYPROF_KEYS x KEYPROF_KEYS in size. this records what keys will lead to what keys.
// keyFrequency is a pointer to an array of size KEYPROF_KEYS that record the frequency of each key.
// wordLength is a pointer to an array of length KEYPROF_WORD_LENGTH_MAX that records how many times a word has beeen found that has x number of characters in it (where x is used to index into the array)
// keyData, keyFrequency, and wordLength all must be valid for the function to work. If any are NULL, the program will return 1.
// filePath is the path of the file that will be loaded and crunched (for example: "C:\Users\MyUserName\Documents\MyDoc.txt")
// include symbols will dictate whether or not we use symbols `~-_=+[{]};:'",<.>/?
// keystrokeMode will count the end of words and the beginning of the next word as being related. word mode will restrict letter associations to the words they are found in.
short keyprof_crunch_file(unsigned long long int *keyData, unsigned long long int *keyFrequency, unsigned long long int *keyStartingFrequency, unsigned long long int *wordLength, char *filePath, char includeSymbols, char keystrokeMode){
	
	// make sure the pointers are all valid.
	if(keyData == NULL || keyFrequency == NULL || wordLength == NULL) return 1;
	
	// attempt to open the file path
	FILE *inputFile = fopen(filePath, "r");
	// if the file cannot be opened, then report a FILE_NOT_FOUND error.
	if(inputFile == NULL) return KEYPROF_FILE_NOT_FOUND;
	
	
	
	// otherwise, the file should be open and ready for business.
	
	// these are used to process the data from the loadFile
	unsigned char indexCurrent;
	unsigned char indexLast = -1; // this is initialized to -1 because there is no lastIndex when you start up the program.
	unsigned char charInput;
	int currentWordLength=0;
	
	
	// input all characters
	while(1){
		
		// input a character
		charInput = fgetc(inputFile);
		
		
		// if the character input is an uppercase letter,
		if(charInput >= 'A' && charInput <= 'Z'){
			// record it on a scale of 0 to 25 (a through z)
			indexCurrent = charInput-'A';
		}
		// if the character is a lowercase letter,
		else if(charInput >= 'a' && charInput <= 'z'){
			// record it on a scale of 0 to 25 (a through z)
			indexCurrent = charInput-'a';
		}
		// check for symbols
		else if( includeSymbols && (charInput == '`' || charInput == '~') ) indexCurrent = 26;
		else if( includeSymbols && (charInput == '-' || charInput == '_') ) indexCurrent = 27;
		else if( includeSymbols && (charInput == '=' || charInput == '+') ) indexCurrent = 28;
		else if( includeSymbols && (charInput == '[' || charInput == '{') ) indexCurrent = 29;
		else if( includeSymbols && (charInput == ']' || charInput == '}') ) indexCurrent = 30;
		else if( includeSymbols && (charInput == ';' || charInput == ':') ) indexCurrent = 31;
		else if( includeSymbols && (charInput == '\''|| charInput == '"') ) indexCurrent = 32;
		else if( includeSymbols && (charInput == ',' || charInput == '<') ) indexCurrent = 33;
		else if( includeSymbols && (charInput == '.' || charInput == '>') ) indexCurrent = 34;
		else if( includeSymbols && (charInput == '/' || charInput == '?') ) indexCurrent = 35;
		else if(charInput == EOF){
			wordLength[currentWordLength]++;
			break;	// if this is the end of the file, then stop inputting data.
		}
		else{
			// if no valid character was input, that means that there is currently no word being processed.
			// if this iteration marks the end of a word,
			if(currentWordLength != 0){
				// cutoff the word length at KEYPROF_WORD_LENGTH_MAX
				if(currentWordLength > KEYPROF_WORD_LENGTH_MAX) currentWordLength = KEYPROF_WORD_LENGTH_MAX;
				// then record the word length
				wordLength[currentWordLength]++;
				// record that this is the end of the word and don't associate the next letter with the current letter.
				if(!keystrokeMode)indexLast = -2;
			}
			// set word length to 0 because we are no longer processing a word.
			currentWordLength = 0;
			continue;
		}
		
		// add character to character frequency list
		keyFrequency[indexCurrent]++;
		
		// if this is the beginning of a word, record that in the keyStartingFrequency array.
		if(currentWordLength == 0) keyStartingFrequency[indexCurrent]++;
		
		// make sure that this isn't the beginning of the document
		if(indexLast != -1){
			// make sure that you are either in keystroke mode, or the last index was a valid character.
			if(keystrokeMode || indexLast != -2)
			keyData[indexLast*KEYPROF_KEYS+indexCurrent]++;
		}
		// increase the word length
		currentWordLength++;
		// record the current index as the last.
		indexLast = indexCurrent;
	}
	
	// close up the place on your way out.
	fclose(inputFile);
	return 0;
}





/// this is the workhorse function. Pass it argc and argv from "int main()" and it will take care of everything.
// this interpret the command line arguments sent to the program.
int keyboard_profiler(int argc, char *argv[]){
	
	// initialize keyboard profiler stuff
	keyprof_init();
	
	// record what the input arguments were
	keyprof_log_d("Number of Input Arguments =", argc);
	keyprof_log("");
	int arg;
	for(arg = 0; arg<argc; arg++) keyprof_log(argv[arg]);
	keyprof_log("\nEnd of Input Arguments.\n");
	
	// if the number of arguments was 1 or less, that means that there couldn't possibly have been an input document
	if(argc <= 1) return KEYPROF_NO_INPUT_FILES_PASSED;
	
	//--------------------------------------------
	// set up input data
	//--------------------------------------------
	
	// this is the array that will hold all of the key data
	// the first index, keydata[FirstIndex][] is an index into what the previous key was
	// the second index, keyData[][SecondIndex] is an index into what key came after the last key
	// so if you were to record the sentence, "hello", the program would do essentially the following:
	// keyData[h][e]++;
	// keyData[e][l]++;
	// keyData[l][l]++;
	// keyData[l][o]++;
	unsigned long long int keyData[KEYPROF_KEYS][KEYPROF_KEYS];
	// this keeps track of how often each key is found.
	unsigned long long int keyFrequency[KEYPROF_KEYS];
	// this keeps track of how many times words with certain lengths are found.
	// index this array with the length of the word you found, and increment whenever you find a word.
	unsigned long long int wordLength[KEYPROF_WORD_LENGTH_MAX];
	// this keeps track of which letters start words most often
	unsigned long long int keyStartingFrequency[KEYPROF_KEYS];
	
	// set all keyData elements to 0 initially.
	// set all keyFrequency elements to 0 initially as well
	int f, s;
	for(f=0; f<KEYPROF_KEYS; f++){
		for(s=0; s<KEYPROF_KEYS; s++){
			keyData[f][s] = 0;
		}
		keyFrequency[f] = 0;
		keyStartingFrequency[f] = 0;
	}
	
	// set all wordLength elements to 0 initially
	int length;
	for(length=0; length<KEYPROF_WORD_LENGTH_MAX; length++){
		wordLength[length] = 0;
	}
	
	//--------------------------------------------
	// process input arguments
	//--------------------------------------------
	// this is the default output name
	char *outputPath = KEYPROF_OUTPUT_NAME_DEFAULT;
	// normally, the output of this program is added to the output of any previous executions of this program.
	// normally, previously collected data gets merged into the data that is collected by this execution of the program.
	// if this is set to 1, then when this execution of the program is writing statistics to file, it will discard any previous data that was in the output file.
	char outputOverwrite = 0;
	// by default, the program will not include symbols (it will just evaluate alphabetic characters a-z (lowercase and uppercase)).
	// the option KEYPROF_OPT_INCLUDE_SYMBOLS must be used to activate this.
	char includeSymbols = 0;
	// this tells the program to work in keystroke mode if it is 1. 
	// if it is 0, it works in word mode.
	char keystrokeMode = 0;
	
	
	//--------------------------------------------
	// process input arguments
	//--------------------------------------------
	// arg starts at 1 because the first argument is the file path of keyprof.exe and we don't really care about that here.
	for(arg=1; arg<argc; arg++){
		
		// record the current argument
		keyprof_log_s("Argument =",argv[arg]);
		
		// check to see if the argument matches the custom output path option
		if(strcmp(argv[arg], KEYPROF_OPT_OUTPUT_PATH) == 0 || strcmp(argv[arg], KEYPROF_OPT_OUTPUT_PATH_SHORT) == 0){
			
			// use the next argument as the output file name.
			outputPath = argv[arg+1];
			// skip the next argument (because it was just used to get the output file name)
			arg++;
			// record the next argument as well (because otherwise it would be skipped)
			keyprof_log_s("Argument =",argv[arg]);
			
			// continue to the next argument
			continue;
		}
		
		// check to see if the argument matches the overwrite option
		if(strcmp(argv[arg], KEYPROF_OPT_OVERWRITE) == 0 || strcmp(argv[arg], KEYPROF_OPT_OVERWRITE_SHORT) == 0){
			// record that you want to overwrite the output file when the time comes.
			outputOverwrite = 1;
			// continue to the next argument
			continue;
		}
		
		// check to see if the argument matches the overwrite option
		if(strcmp(argv[arg], KEYPROF_OPT_INCLUDE_SYMBOLS) == 0 || strcmp(argv[arg], KEYPROF_OPT_INCLUDE_SYMBOLS_SHORT) == 0){
			// record that you want to overwrite the output file when the time comes.
			includeSymbols = 1;
			// continue to the next argument
			continue;
		}
		if(strcmp(argv[arg], KEYPROF_OPT_KEYSTROK_MODE) == 0 || strcmp(argv[arg], KEYPROF_OPT_KEYSTROK_MODE_SHORT) == 0){
			// record that the user wants to work in keystroke mode instead of word mode
			keystrokeMode = 1;
			// continue to the next argument
			continue;
		}
		
		// if this argument is not an option, then it must be an input file path.
		keyprof_crunch_file(&keyData[0][0], &keyFrequency[0], &keyStartingFrequency[0], &wordLength[0], argv[arg], includeSymbols, keystrokeMode);
		
	}
	
	// if the we aren't supposed to overwrite the file, we need to read it and record it before we go overwriting it.
	if(!outputOverwrite) keyprof_load_stats(outputPath, &keyData[0][0]);
	// save stats to file
	keyprof_save_stats(&keyData[0][0], &keyFrequency[0], &keyStartingFrequency[0], &wordLength[0], outputPath);
	
	// successfully computed statistics
	return 0;
}





