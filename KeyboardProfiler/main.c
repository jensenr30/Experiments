
#include <stdio.h>
#include "keyboard_profiler.h"



int main(int argc, char * argv[]){
	
	// this is for testing the blacklist function.
	//printf("blacklist result = %d\n",keyprof_find_string_in_blacklist("keyprof_blacklist.txt", "hand") );
	
	// let the keyboard profiler do everything
	return keyboard_profiler(argc, argv);
	
}
