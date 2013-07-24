#include <stdio.h>
#include "SDL.h"
#include "SDL_net.h"
#include <string.h>

//  these are the glbal variables for the ip to connect to and the tcp.
IPaddress ip;
TCPsocket tcpsock;
SDLNet_SocketSet myset;


int main(int argc, char** argv){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	
	//get an IP.
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, 1234);
	
	TCPsocket server = SDLNet_TCP_Open(&ip);
	TCPsocket client;
	
	const char *text = "Hello There! Welcome!";
	
	while(1){
		client = SDLNet_TCP_Accept(server);
		if(client){
			//here you can communicate with the client.
			//use the client socket to communicate to the client.
			SDLNet_TCP_Send(client, text, strlen(text)+1);
			SDLNet_TCP_Close(client);
			break;
		}
	}
	SDLNet_TCP_Close(server);
	
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
