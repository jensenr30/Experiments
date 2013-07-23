#include <stdio.h>
//#include "Windows.h"

#include "SDL.h"
#include "SDL_net.h"

int main(int argc, char* argv[]){
	
	
	if(SDL_Init(0)==-1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	//enable console
	freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
	if(SDLNet_Init()==-1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
	
	SDL_version compile_version;
	
	const SDL_version *link_version=SDLNet_Linked_Version();
	
	SDL_NET_VERSION(&compile_version);
	
	printf("compiled with SDL_net version: %d.%d.%d\n",
        compile_version.major,
        compile_version.minor,
        compile_version.patch);
	printf("running with SDL_net version: %d.%d.%d\n", 
        link_version->major,
        link_version->minor,
        link_version->patch);
	
	
	// connect to localhost at port 9999 using TCP (client)
	IPaddress ip;
	TCPsocket tcpsock;
	
	
	//get address
	int i;
	#define maxadd 80
	char address[maxadd];
	
	for(i=0; i<80; i++){
		address[i] = getchar();
		if(address[i] == '\n') {
			address[i] = '\0';
			break;
		}
	}
	
	if(SDLNet_ResolveHost(&ip,address,80)==-1) {
		printf("Couldn't resolve hostname");
		exit(3);
	}
	
	
	
	//this turns the ip.host (0x6789asdf) into this:
	//ip3 = 0x67; ip2 = 0x89; ip1 = 0xas; ip = 0xdf;
	unsigned short ip3,ip2,ip1,ip0;
	ip3 = ip.host/0x1000000;
	ip2 = ip.host/0x10000 - ip3*0x100;
	ip1 = ip.host/0x100 - ip2*0x100 - ip3*0x10000;
	ip0 = ip.host%0x100;
	/*
	//choose local ip address
	ip3 = 127;
	ip2 = 0;
	ip1 = 0;
	ip0 = 1;
	ip.port = 80;
	*/
	printf("IPaddress = %d.%d.%d.%d:%d\n",ip0,ip1,ip2,ip3,ip.port);
	
	
	//opens that TCP
	printf("Opening TCP socket\n");
	tcpsock=SDLNet_UDP_Open(&ip);
	if(!tcpsock) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(4);
	}
	char data[1024];
	Uint32 number = 0xDEADBEEF;
	SDLNet_Write32(number, data)
	
	
	
	
	printf("closing TCP socket\n");
	SDLNet_TCP_Close(tcpsock);
	
	
	
	
	
	
	
	printf("Closing SDL_net\n");
	SDLNet_Quit();
	printf("closing SDL\n");
	SDL_Quit();
	// you could SDL_Quit(); here...or not.
	
	return 0;
}
