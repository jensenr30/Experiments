
/* Ryan Jensen * <date> * <title>
 * <purpose>
 */

#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <string.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"


#include <Windows.h>

typedef char bool;
#define false 0
#define true  1

//do i really want to debug?
const bool debug = false;

//The attributes of the screen 
int SCREEN_WIDTH = 948;
int SCREEN_HEIGHT = 488;
int SCREEN_BPP = 32;

//The surfaces that will be used
SDL_Surface* screen = NULL;

//The event structure that will be used
SDL_Event event;

//the max size of the rects.
int maxSize = 5;

//how many rectangles are written to the screen each itteration?
int rectanglesPerCycle = 10;

//how much random variance from the original color is the rectangle?
int colorVar = 24;

//this is how slow the game goes
int slowness = 2;

//color[0] is the last color, color[1] is the current color, color[2] is the next color
int color[3] = {0xffffff, 0xffffff, 0xffffff};
//this holds the value that will be printed in the rectangles
int printColor;

//the difference between each rgb part of color[0] and color[2].
//diff[0] = red diff
//diff[1] = green diff
//diff[2] = blue diff
int diff[3];
//used to keep track of which of the three colors have the biggest diff.
//0=red, 1=green, 2=blue
int bigDiff = 0;
int diffDone = 0;
int afterCorrection[3];


#include "functions.h"
SDL_Rect myrect;

int main(int argc, char *argv[])
{
	int cycle = 0;
	int mult[3] = {0x10000, 0x100, 0x1};
	unsigned long randomtimes;
	
	srand(time(NULL));
	
	if( load_settings() == false) return 404; //error. settings not found.
	
    //Initialize
    if( init() == false )
    {
    	return 100;
    }
    
    //Load the files
    load_files();
    
    
	//make sure the program waits for a quit
	bool quit = false;
    
    //While the user hasn't quit
    while( quit == false )
    {
    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) )
    	{
    		while(rand()%randomtimes); // randomize
    		srand( time(NULL) ^ rand() ); // get new seed
    		while(rand()%randomtimes); // randomize further
    		randomtimes = rand()%41 + 1;
    		if(randomtimes<0) randomtimes*=-1;
    		//printf("%d\n", randomtimes);
    		
    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
			else if(event.type == SDL_VIDEORESIZE){
				SCREEN_WIDTH = event.resize.w;
				SCREEN_HEIGHT = event.resize.h;
				set_window_size(event.resize.w, event.resize.h);
			}
			//If a key was released
			if( event.type == SDL_KEYUP )
			{
				//nothing
			}
			//If space a key was pressed
			else if( event.type == SDL_KEYDOWN )
			{
				//nothing
			}
			//If a mouse button was pressed
			else if( event.type == SDL_MOUSEBUTTONDOWN )
			{
				//nothing
			}
			else if( event.type == SDL_MOUSEBUTTONUP )
			{
				//nothing
			}
			else if( event.type == SDL_MOUSEMOTION)
			{
				myrect.x = event.motion.x;
				myrect.y = event.motion.y;
			}
    	} // end while(poll event)
    	
    	//if you have reached the target color
    	if(color[0] == color[2] && cycle==0){
			color[1] = color[0] =  rand()%0x100;
			color[1]+= color[0]+= (rand()%0x100)*0x100;
			color[1]+= color[0]+= (rand()%0x100)*0x10000; 
			
			color[2] =  rand()%0x100;
			color[2]+= (rand()%0x100)*0x100;
			color[2]+= (rand()%0x100)*0x10000;
			
			//calculate the diffs
			diff[0] = color[2]/0x10000 - color[0]/0x10000;
			diff[1] = ((color[2]/0x100)-(color[2]/0x10000)*0x100) - ((color[0]/0x100)-(color[0]/0x10000)*0x100);
			diff[2] = color[2]%0x100 - color[0]%0x100;
			if(diff[0]<0){ diff[0] *= -1; afterCorrection[0] = -1; } else afterCorrection[0] = 1;
			if(diff[1]<0){ diff[1] *= -1; afterCorrection[1] = -1; } else afterCorrection[1] = 1;
			if(diff[2]<0){ diff[2] *= -1; afterCorrection[2] = -1; } else afterCorrection[2] = 1;
			
			//find the biggest difference in color components.
			//red greater than green
			if(diff[0] > diff[1]){
				//red greater than blue
				if(diff[0] > diff[2])
					bigDiff = 0; // red is biggest diff
				else
					bigDiff = 2; // blue is biggest diff
			}
			else{
				// green greater than red
				if(diff[1] > diff[2])
					bigDiff = 1; // green is biggest diff
				else
					bigDiff = 2; // blue is biggest diff
			}
			
			//revert the diffs.
			diff[0] *= afterCorrection[0];
			diff[1] *= afterCorrection[1];
			diff[2] *= afterCorrection[2];
			
			//reset the done diffs cycles
			diffDone = 0;
			#if debug
			printf("\n\n\ncolor[0] = %6x\ncolor[2] = %6x\n\ndiff[0] = %2d\ndiff[1] = %2d\ndiff[2] = %2d\n\n", color[0], color[2], diff[0], diff[1], diff[2]);
			#endif
    	}
    	else{
			if(diffDone == afterCorrection[bigDiff]*diff[bigDiff] && cycle==0){
				color[0] = color[2]; // if you have reached the end, then you are done. find a new color to persue and go forward from there.
			}
			else{
				int r,g,b;
				
				printColor = color[1] + afterCorrection[bigDiff]*mult[bigDiff]*(diffDone++);
				
				if(bigDiff != 0){ // red
					r = (diff[0]*diffDone)/diff[bigDiff];
					printColor += r*0x10000;
				}
				else if(bigDiff != 1){ // green
					g = (diff[1]*diffDone)/diff[bigDiff];
					printColor += g*0x100;
				}
				else if(bigDiff != 2){ // blue
					b = (diff[2]*diffDone)/diff[bigDiff];
					printColor += b;
				}
				#if debug
				printf("color[1] = %6x\n", color[1]);
				#endif
			}
    	}
    	
    	
    	
    	int i;
    	for(i=0; i<rectanglesPerCycle; i++){
			/* old color generation
			color =  rand()%0x100;
			color+= (rand()%0x100)*0x100;
			color+= (rand()%0x100)*0x10000;
			*/
			myrect.x = rand()%SCREEN_WIDTH;
			myrect.y = rand()%SCREEN_HEIGHT;
			
			myrect.h = rand()%maxSize;
			myrect.w = rand()%maxSize; 
			
			SDL_FillRect(screen, &myrect, printColor);
			
		}
    	
    	
    	SDL_Flip(screen);
    	cycle++;
    	if(cycle>slowness) cycle = 0;
    	Sleep(1);
    }
    
    
    //Free the surface and quit SDL
    clean_up();
    return 0;
}

