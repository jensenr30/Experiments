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




/// this will save keyData to file
short keyprof_save_stats(unsigned long long int *keyData, char *filePath){
	
	FILE *saveFile = fopen(filePath, "w");
	// make sure the file was opened correctly
	if(saveFile == NULL) return KEYPROF_FILE_NOT_FOUND;
	
	
	int f, s; // these record the character index f=first, s=second.
	// f is the cause and s is the effect.
	for(f=0; f<KEYPROF_KEYS; f++){
		for(s=0; s<KEYPROF_KEYS; s++){
			// print the data for the number of times that the user presses [f] and then [s]
			/// TODO: figure out how to print unsigned long long
			fprintf(saveFile, "%lu\t", (unsigned long int)keyData[f*KEYPROF_KEYS+s]);
		}
		// print a newline character
		fprintf(saveFile, "\n");
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
	char charCurrent;
	char charLast;
	char charInput;
	
	
	while(1){
		charInput = fgetc(loadFile);
		
		/// TODO: PROCESS INPUT DATA
		
		// break because there is nothing written in here yet
		break;
	}
	
	// close up shop when you leave
	fclose(loadFile);
	// success
	return 0;
}



short keyprof_crunch_file(unsigned long long int *keyData, char *filePath, char includeSymbols){
	
	// attempt to open the file path
	FILE *inputFile = fopen(filePath, "r");
	// if the file cannot be opened, then report a FILE_NOT_FOUND error.
	if(inputFile == NULL) return KEYPROF_FILE_NOT_FOUND;
	
	// otherwise, the file should be open and ready for business.
	
	// these are used to process the data from the loadFile
	char indexCurrent;
	char indexLast = 26; // this is initialized to 35 because it has to be something. It will only skew the data of the Backtick/Tilda key which nobody uses anyway. And it will only add a single keystroke from Backtick\Tilda key to the first character on the list.
	char charInput;
	
	
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
		else if( includeSymbols && (charInput == '.' || charInput == '>') ) indexCurrent = 34;	//
		else if( includeSymbols && (charInput == '/' || charInput == '?') ) indexCurrent = 35;	//
		else if(charInput == EOF) break;	// if this is the end of the file, then stop inputting data.
		else{
			// if no valid character was input, wait for the next valid one.
			continue;
		}
		
		// record that in the input document, there was a transition from one key to another.
		keyData[indexLast*KEYPROF_KEYS+indexCurrent]++;
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
	
	
	// set all keyData elements to 0 initially.
	int f, s;
	for(f=0; f<KEYPROF_KEYS; f++){
		for(s=0; s<KEYPROF_KEYS; s++){
			keyData[f][s] = 0;
		}
	}
	
	// this is the default output name
	char *outputPath = KEYPROF_OUTPUT_NAME_DEFAULT;
	// normally, the output of this program is added to the output of any previous executions of this program.
	// normally, previously collected data gets merged into the data that is collected by this execution of the program.
	// if this is set to 1, then when this execution of the program is writing statistics to file, it will discard any previous data that was in the output file.
	char outputOverwrite = 0;
	// by default, the program will not include symbols (it will just evaluate alphabetic characters a-z (lowercase and uppercase)).
	// the option KEYPROF_OPT_INCLUDE_SYMBOLS must be used to activate this.
	char includeSymbols = 0;
	
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
		
		// if this argument is not an option, then it must be an input file path.
		keyprof_crunch_file(&keyData[0][0], argv[arg], includeSymbols);
		
	}
	
	// if the we aren't supposed to overwrite the file, we need to read it and record it before we go overwriting it.
	if(!outputOverwrite) keyprof_load_stats(outputPath, &keyData[0][0]);
	// save stats to file
	keyprof_save_stats(&keyData[0][0], outputPath);
	
	// successfully computed statistics
	return 0;
}





