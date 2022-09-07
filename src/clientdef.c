//including user defined header file
#include </home/praveen/Downloads/updatedone/srcupdated/inc/client.h>


/*login function first ask user input for validating regitered user with user id generated during registration after that it will ask port number from user
 then it requests the server for connection  if handshake done successfully, means connection is estabilished successfully and then data transfer can be done.
 login method 
 return type = integer
 parameters = null
*/

int clientLogin()
{
	//variable declaration
	int userId=0,iterator=0, portNumber=0,socketfd=0, serverLength=0, sendValue=0, receiveValue=0;
	
	char message[BUFFERSIZE],buffer_One[BUFFERSIZE],buffer_Two[BUFFERSIZE];
	
	struct sockaddr_in server;
	system("clear");
	printf("-------------------------------------------\n");
	printf("-------------------------------------------\n");
	printf("\t     LOGIN WINDOW\n");
	printf("-------------------------------------------\n");
	printf("-------------------------------------------\n");
	
	//taking user id as user input
	printf("=> Enter user id: ");
	scanf("%d",&userId);
	
	//checking if user is registerd or not using registed user id
	if(isUserPresent(userId)!=0)
	{
		error("Id not registered!!\n");
	}//end_of_if
				
	printf("=> Enter port number: ");	//taking port number from user with range 49152 to 65535
	scanf("%d",&portNumber);
	if(portNumber < MIN || portNumber > MAX)
	{
		error("Invalid port number\n");
	}//end_of_if
	
	//Creating socket for client
	socketfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	/* AF_INET = ipv4 internet protocol
								 **SOCK_DGRAM = Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
								 ***IPPROTO_UDP = 0 and IPPROTO_UDP for UDP sockets	
								*/
											 		
	//checking the socketfd value if socket is created successfull it returns greater than 0 otherwise give message no such host
	if(socketfd < 0)
	{
		error("ERROR!!! no such host\n");
		
	}//end_of_if
	
	else
	{
		printf("socket is successfully opened\n\n");
	}//end_of_else
				
	//providing ipv4 internet protocol
	server.sin_family = AF_INET;
				
	//providing port number 
	server.sin_port = htons(portNumber);	//htons() = converting host byte order to network byte order
				
	//INADDR_ANY = IP 0.0.0.0
	server.sin_addr.s_addr=INADDR_ANY;

	//getting size of the sockaddr_in structure
	serverLength=sizeof(server);
				
	//bzero will make all the all the members of buffer to 0
	bzero(buffer_One,BUFFERSIZE);
				
	//calculating size of SYN and storing it into	synLength		
	int synLength=sizeof(SYN);
	
	//calculating size of ACK and storing it into ackLength
	int ackLength=sizeof(ACK);
			
	sendValue=sendto(socketfd,SYN,synLength,MSG_WAITALL,(struct sockaddr *)&server,serverLength);
	if(sendValue>0)
	{
		printf("Handshake initiated!\n");
		sleep(1);
		printf("Syn sent successfully!\n");
	}//end_of_if
	
	else
	{
		error("syn not sent successfully!\n Handshake error\n");
	}//end_of_else
	
	//receiving acknowledgement message from server and storing the return type in receiveValue				
	receiveValue=recvfrom(socketfd,buffer_One,BUFFERSIZE,MSG_WAITALL,(struct sockaddr *)&server, &serverLength);
		
	//checks if value of receiveValue is greater than 0 or not if receive is positive message is received successfully otherwise error in receiving and handshake error
	if(receiveValue>0)
	{	
		sleep(2);
		printf("Synack received successfully!\n");
		//setting the string to null					
		bzero(buffer_One,sizeof(buffer_One));
		//sending acknowledgement to server				
		sendValue=sendto(socketfd,ACK,ackLength,MSG_WAITALL,(struct sockaddr *)&server,serverLength);
		
		if(sendValue>0)
		{	
			sleep(1);
			printf("ack sent successfully!\n");
			sleep(1);
			printf("3-way Handshake Completed!\n\n\n");
		}//end_of_if
		
		else
		{
			error("ack not sent successfully!\n Handshake error\n");
		}//end_of_else
		
	}//end_of_if
	else
	{
		error("synack not received successfully! Handshake error\n\n");
	}//end_of_else
	
	
	//starts message transfer from client to server
	printf("\n\n\n-----------------------------------------------");
	printf("\n-----------------------------------------------");
	printf("\n\t    Data Transfer Starts\n");
	printf("\n-----------------------------------------------");
	printf("\n-----------------------------------------------\n");
	
	while(1)
	{	
	printf("Enter your message: " );
	scanf("%s",message);
	printf("\n");
	
	//setting buffer_Two string to null
	bzero(buffer_Two,BUFFERSIZE);
	
	//sending message to server				
	sendValue=sendto(socketfd,message,strlen(message),MSG_WAITALL,(struct sockaddr *)&server,serverLength);
	if(sendValue<0)
	{
		error("Unable to send message successfully!\n");			
	}//end_of_if
	
	receiveValue=recvfrom(socketfd,buffer_Two,BUFFERSIZE,MSG_WAITALL,(struct sockaddr *)&server, &serverLength);
	if(receiveValue>0)
	{	
		for(iterator = 0; buffer_Two[iterator] != '\0' && message[iterator] != '\0'; iterator++)
		{				
			if(buffer_Two[iterator]!=message[iterator])	//checking send message to server and received message  from server
			{
				break;
			}//end_of_if

			bzero(buffer_Two,sizeof(buffer_Two));
			//sending aknowledgement to server that server has received correct message
			sendValue=sendto(socketfd,ACK,ackLength,MSG_WAITALL,(struct sockaddr *)&server,serverLength);
			if(sendValue<0)
			{
				error("Acknowledgement has not sent successfully!\n");
			}
			else
			{
					if(strcmp(message,GOODBYE)==0)
					{
						sleep(1);
						exit(EXIT_SUCCESS);
					}
			}//end_of_if			
		}//end_of_for
	}//end_of_if
	else
	{
		error("Not received successfully!\n");	
	}
	}						
}//end_of_clientLogin()


/*
return type = void
parameter passed = character pointer
This function will print error
*/

void error(char *error_Message)
{
	perror(error_Message);
	exit(EXIT_FAILURE);
}//end_of_error()

/*
return type = void
parameter passed = null
This function will print menu and take user input for choosing menu
*/

void getMenu()
{
	int num;
	pthread_t thread1,thread2;		// declaring thread variables
	printf("\n\n1.Registration");
	printf("\n2.Login \n");
	printf("\n3.Exit \n");
	printf("\nENTER YOUR CHOICE: ");	//accepting choice from user
	scanf("%d", &num);
	
		switch(num)
		{
			case ONE:
				pthread_create(&thread1,NULL,(void*) &registration,NULL);
				pthread_join(thread1,NULL);	
				break;
				
			case TWO:
				pthread_create(&thread2,NULL,(void*) &clientLogin,NULL);
				pthread_join(thread2,NULL);	
				break;	
				
			case THREE:	
				exit(EXIT_SUCCESS);
				
			default:
				printf("\nWrong choice!!!  choose again....\n\n\n");
		}//end_of_switch
}//end_of_getMenu()_function

