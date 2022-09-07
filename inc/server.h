
#ifndef HEADERFILE
#define HEADERFILE
//including header files
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include<arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
 //defining macros
#define SYN "SYN"
#define SYNACK "SYNACK"
#define ACK "ACK"
#define BUFFERSIZE 1024
#define SERVERIDSIZE 15
#define SERVERPASSWORDSIZE 10
#define SERVERID "server"
#define SERVERPASSWORD "Server123"
#define MIN 49152
#define MAX 65535
#define GOODBYE "goodbye"

//declaring functions
void error(char *);
void serverLogin();

#endif	//end_of_HEADERFILE
