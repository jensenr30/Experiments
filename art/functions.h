
void set_window_size(int w, int h){
	screen = SDL_SetVideoMode( w, h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE );
	
	//If there was an error setting up the screen
	if(screen == NULL )
	{
		exit(111);
	}
}




SDL_Surface *load_image( char *filename )
{
    //Temporary storage for the image that is loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image with either SDL_image or LoadBMP. comment-out the one you are not using
    loadedImage = IMG_Load( filename );
    //loadedImage = SDL_LoadBMP( filename );
    
    //If the image was loaded correctly
    if( loadedImage != NULL )
    {
        // Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    else{
		char message[256];
		strcpy(message, filename);
		strcat(message, " is missing");
		//MessageBox(NULL, message, "Error", MB_OK);
		return NULL;
	}
    
    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y,  SDL_Surface* source, SDL_Surface* destination )
{
    //make a temporary rectangle to hold offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
	//Initialize all subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		exit(109);
	}
	
	/*
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		exit(110);
	}
	
	*/
	
	//Set up the screen
	set_window_size(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//Set the window caption
	SDL_WM_SetCaption( "Art", NULL );
	
	//If everything initialized fine
	return true;
}

bool load_files()
{
	
	
	//If everthing loaded fine
	return true;
}


void clean_up()
{
	//free the image
	SDL_FreeSurface( screen );
	//Quit SDL
	SDL_Quit();
}



int load_settings(){
	FILE *settings;
	
	settings = fopen("settings.txt", "r");
	if(settings == NULL) return false;
	
	//skip initial comments
	char lett;
	while(1){
		lett = fgetc(settings);
		if(lett == '§'){
			lett = fgetc(settings); // remove newline character
			break;
		}
		else if(lett == '\0') return false;
	}
	//now we are ready to read the data.
	
	//reading in data
	fscanf(settings, "maxSize = %d\n", &maxSize);
	fscanf(settings, "rectanglesPerCycle = %d\n", &rectanglesPerCycle);
	fscanf(settings, "colorVariance = %d\n", &colorVar);
	fscanf(settings, "slowness = %d\n", &slowness);
	
	//closing the file
	fclose(settings);
	return true;
}





