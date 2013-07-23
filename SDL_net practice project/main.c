#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Windows.h"
#include <process.h>

#include "SDL.h"
#include "SDL_net.h"
#define MAXLEN 1024



//  these are the glbal variables for the ip to connect to and the tcp.
IPaddress ip;
TCPsocket tcpsock;
SDLNet_SocketSet myset;


void *checkTCP(void *threadid)
{
	//continually check
	int i;
	char msg[MAXLEN];
	int result;
	printf("Listening on %d.%d.%d.%d:%d\n", ip.host%0x100, ip.host%0x10000 - ip.host%0x100, ip.host/0x10000 - (ip.host/0x1000000)*0x100, ip.host/0x1000000, ip.port);
	while(1){
	result=SDLNet_CheckSockets(myset, 1000);
		if(result==-1) {
			printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
			//most of the time this is a system error, where perror might help you.
			perror("SDLNet_CheckSockets");
			break; // leave loop
		}
		else if(result > 0){
			//blank msg. this is necessary for some shitty reason...
			for(i=0; i<MAXLEN; i++) msg[i] = '\0';
			// receive some text from tcpsock
			result=SDLNet_TCP_Recv(tcpsock,msg,MAXLEN);
			printf(">>> %s",msg);
		}
	}
	return NULL;
}


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
	
	printf("\n\nEnter a host to connect to\t\t(i.e. google.com, 192.168.1.1, localhost, etc...)\n\n");
	
	//get address
	int i;
	char address[MAXLEN];
	
	for(i=0; i<MAXLEN; i++){
		address[i] = getchar();
		if(address[i] == '\n') {
			address[i] = '\0';
			break;
		}
	}
	
	if(SDLNet_ResolveHost(&ip,address,21)==-1) {
		printf("Couldn't resolve hostname");
		exit(3);
	}
	
	
	
	//this turns the ip.host (0x6789asdf) into this:
	//ip3 = 0x67; ip2 = 0x89; ip1 = 0xas; ip = 0xdf;
	unsigned short ip3,ip2,ip1,ip0;
	ip0 = ip.host/0x1000000;
	ip1 = ip.host/0x10000 - ip0*0x100;
	ip2 = ip.host/0x100 - ip1*0x100 - ip0*0x10000;
	ip3 = ip.host%0x100;
	//ip.port = 80;
	
	//choose local ip address
	/*
	unsigned short ip3,ip2,ip1,ip0;
	ip3 = 127;
	ip2 = 0;
	ip1 = 0;
	ip0 = 1;
	
	//put data into ip
	ip.host = 0;
	ip.host += ip3*0x1000000 + ip2*0x10000 + ip1*0x100 + ip0;
	ip.port = 80;
	*/
	
	printf("IPaddress = %d.%d.%d.%d:%d\n",ip3,ip2,ip1,ip0,ip.port);
	
	
	//opens that TCP
	printf("Opening TCP socket\n");
	tcpsock=SDLNet_TCP_Open(&ip);
	if(!tcpsock) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(4);
	}
	
	// Create a socket set to handle up to 16 sockets
	myset=SDLNet_AllocSocketSet(1);
	if(!myset) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(1); //most of the time this is a major error, but do what you want.
	}
	
	
	
	
	// send a hello over sock
	//TCPsocket sock;
	int len,result;
	char msg[MAXLEN];
	int k;
	//add tcp socket to the socket myset
	result=SDLNet_TCP_AddSocket(myset,tcpsock);
	if(result==-1) {
		printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
		// perhaps you need to restart the myset and make it bigger...
	}
	
	//start listening to TCP connection.
	pthread_t threads;
	int rc;
	rc = pthread_create(&threads, NULL, checkTCP, (void *)1);
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	
	while(1){
		for(k=0; k<MAXLEN -1; k++){
			msg[k] = getchar();
			if(msg[k] == '\n'){
					msg[k+1] = '\0';
			break;
			}
			
		}
		if(strcmp(msg, "/exit\n") == 0){
			pthread_cancel(threads);
			break;
		}
		len=strlen(msg)+1; // add one for the terminating NULL
		result=SDLNet_TCP_Send(tcpsock,msg,len);
		if(result<len) {
			printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			// It may be good to disconnect sock because it is likely invalid now.
			break;
		}
	}
	
	
	printf("closing TCP socket\n");
	SDLNet_TCP_Close(tcpsock);
	
	
	
	
	
	
	
	printf("Closing SDL_net\n");
	SDLNet_Quit();
	printf("closing SDL\n");
	SDL_Quit();
	// you could SDL_Quit(); here...or not.
	
	pthread_exit(NULL);
	exit(0);
}
