#include "headers_and_globals.h"

int main( int argc, char* args[] )
{
    //mouse variables and cell types
    int x, y, d = 0;

    //mouse is held variables
    int mousestatus = 0;

	//make sure the program waits for a quit
	int quit = false;

    //Initialize
    if( init() == false ) return 1;

    //Load the files
    if( load_files() == false ) return 2;

    //Update the screen
    if( SDL_Flip( screen ) == -1 ) return 3;

    //initialize the cell stuff. This gets the cell system up and running.
    init_cell_stuff();

    print_cells();

    //While the user hasn't quit
    while( quit == false ){

    	//While there's an event to handle
    	while( SDL_PollEvent( &event ) ){

    		//If the user has Xed out the window
    		if( event.type == SDL_QUIT ){
				//Quit the program
				quit = true;
			}

            if( event.type == SDL_MOUSEBUTTONDOWN ){
                if( event.button.button == SDL_BUTTON_LEFT ){
                        x = event.button.x;
                        y = event.button.y;
                        setcell(x, y, d);
                    /*
                    mousestatus = 1;
                    while(mousestatus == 1){
                        x = event.button.x;
                        y = event.button.y;
                        setcell(x, y, d);
                        if(event.type == SDL_MOUSEBUTTONUP){
                            mousestatus = 0;
                        }
                    }
                    */
                    if(!event.type == SDL_MOUSEBUTTONUP){
                        x = event.button.x;
                        y = event.button.y;
                        setcell(x, y, d);
                    }
                }
                if( event.button.button == SDL_BUTTON_RIGHT ){
                    x = event.button.x;
                    y = event.button.y;
                    deletecell(x, y, d);
                }
            }

            if( event.type == SDL_KEYDOWN ){
                switch( event.key.keysym.sym ){
                    case SDLK_UP: d++; break;
                    case SDLK_DOWN: d--; break;
                    default: break;
                    }
                }

    	} // end while(event)
		//no more events to handle at the moment.



    }// end while(quit == false)

    //Free the surface and quit SDL
    clean_up();

    return 0;
}
