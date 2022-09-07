
#ifndef HEADER
#define HEADER

//including header files
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <pthread.h>

//defining macros
#define SYN "SYN"
#define SYNACK "SYNACK"
#define ACK "ACK"
#define BUFFERSIZE 1024
#define NAMESIZE 20
#define PASSWORDSIZE 10
#define ONE 1
#define TWO 2
#define THREE 3
#define MIN 49152
#define MAX 65535
#define GOODBYE "goodbye"

//Defining struct name user which has 3 elements, two are character array or string and 1 is interger 

typedef struct user
{
	
	char name[NAMESIZE];
	char password[PASSWORDSIZE];
	int id;
	
}user;



//Defining struct name userNode alias unode which has 2 elements, 1 is  user structure type variable and 1 is of its own type pointer
typedef struct userNode
{
	user data;
	struct userNode *next;
}unode;




//declaring functions
unode* addNode(unode * ,user);	//declaring function addNode() with return of unode structure pointer with parameters structure pointer of type unode and structure variable of type user
unode * readfile(FILE *, unode *);	//declaring function readfile() with return of unode structure pointer with parameters file pointer and structure pointer of type unode
int isUserPresent(int );	//declaring function isUserPresent() with return of integer with parameter of integer type

void writefile( FILE * );	//declaring function writefile() with return of void with parameter of file pointer type
void registration();	//declaring function registration() with return of void 
int count();	//declaring function count() with return of integer
int clientLogin();	//declaring function login() with return of integer 
void getMenu();	//declaring function getMenu to get menu 

//declaration of error function
extern void error(char *);	//declaring function error() with return of void with parameter of character pointer
	
#endif	//end_of_HEADER

	
