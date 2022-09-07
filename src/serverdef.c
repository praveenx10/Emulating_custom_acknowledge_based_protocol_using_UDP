#include </home/praveen/Downloads/updatedone/srcupdated/inc/server.h>


/*
return type = void
parameter passed = character pointer
This function will print error
*/	
void error(char *error_Message)
{
	perror(error_Message);
	exit(EXIT_FAILURE);
}//end_of_error()_function



/*
return type = void
parameter passed = NULL
This function will get server id and server password as user input and established handshake to receive data from client and display it
*/		
void serverLogin()
{

	int socketfd, serverLength,clientLength, sendValue,receiveValue, portNumber;
	char serverId[SERVERIDSIZE], serverPassword[SERVERPASSWORDSIZE], buffer_One[BUFFERSIZE], buffer_Two[BUFFERSIZE];
	
	//pre-defined structures of type struct sockaddr_in which holds socket address
	struct sockaddr_in server,client;
	
	//taking serverId 
	printf("Enter Server ID: ");
	scanf("%s",serverId);
	//checking entered serverId id registered or not
	if(strcmp(serverId,SERVERID)==0)
	{
		printf("Enter Server Password: ");	//taking server password from user
		scanf("%s",serverPassword);
		//checking entered serverId id registered or not
		if(strcmp(serverPassword,SERVERPASSWORD)==0)
		{
			printf("Enter Port Number: ");		//taking port number from user whose range will be in between 49152 to 65535
			scanf("%d",&portNumber);
			if(portNumber < MIN || portNumber > MAX)
			{
				error("Port number invalid");
				
			}
			//Creating server socket 
			socketfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	/* AF_INET = ipv4 internet protocol
										 	 **SOCK_DGRAM = Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
										 	 ***IPPROTO_UDP = 0 and IPPROTO_UDP for UDP sockets	
											*/
			
			//checking the socketFileDescriptor value if socket is created successfull it returns greater than 0 otherwise give message error in opening socket
			if (socketfd < 0)
			{
				error("Error in Opening socket");
			}//end_of_if
			else
			{
				printf("socket is successfully opened!!!\n");
			}//end_of_else
			
			//getting size of server varible of type sockaddr_in structure
			serverLength = sizeof(server);
			
			//bzero will make all the structure members to NULL
			bzero(&server,serverLength);
			
			//providing ipv4 internet protocol
			server.sin_family=AF_INET;
			
			//providing 0.0.0.0 as IP adderss so any client can join
			server.sin_addr.s_addr=INADDR_ANY;
			
			//providing port number
			server.sin_port=htons(portNumber);	/*atoi() = converts a character string to an integer value
								 **htons() = converting host byte order to network byte order
								*/ 
			
			
			int bind_Value=bind(socketfd,(struct sockaddr *)&server,serverLength);   /*binding socket with address and port and storing returned value in bind variable
													      **socketFileDescriptor = file descriptor contains return value of .*/
													      
			//checks if value of bind is greater than 0 or not if bind is positive binding is successful otherwise error in binding 		
										   
			if (bind_Value<0)
			{
				error("Error in binding");
			}//end_of_if
			else
			{
				printf("binding successful!!!\n\n");
			}//end_of_else
			
			
			//getting size of client varible of type sockaddr_in structure
			clientLength = sizeof(struct sockaddr_in);
			
			//calculating size of SYNACK and storing it into
			int synackLength=sizeof(SYNACK);
			
			//receiving Synchronization message from client for connection and storing the return type in receive
			receiveValue = recvfrom(socketfd,buffer_One,BUFFERSIZE,MSG_WAITALL,(struct sockaddr *)&client,&clientLength);
			
			//checks if value of receiveValue is greater than 0 or not if receiveValue is positive message is received successfully otherwise error in receiving and handshake error
			if(receiveValue<0)
			{
				error("SYN not received!\nHANDSHAKE error!\n");
			}//end_of_if
			else
			{
				
				printf("Handshake initiated!\n");
				sleep(2);
				printf("SYN received!\n");
				bzero(buffer_One,sizeof(buffer_One)); //making the buffer empty or null
				
				//sending syn+ack as SYNACK to client and storing the return type in send
				sendValue=sendto(socketfd,SYNACK,synackLength,MSG_WAITALL,(struct sockaddr *)&client,clientLength);
					
				//checks if value of send is greater than 0 or not if sendValue is positive message is sent successfully otherwise error in sending and handshake error
				if(sendValue>0)
				{	sleep(1);
					printf("SYNACK sent successfully!\n");
				}//end_of_if
				else
				{
					error("SYNACK not sent!\nHANDSHAKE error!\n");	
				}//end_of_else

			}//end_of_else	
			
			//receiving acknowledgement message from client and storing the return type in receiveValue
			receiveValue=recvfrom(socketfd,buffer_One,BUFFERSIZE,MSG_WAITALL,(struct sockaddr *)&client,&clientLength);
			
			//checks if value of receiveValue is greater than 0 or not if receive is positive message is received successfully otherwise error in receiving and handshake error
			if(receiveValue<0)
			{
				error("ACK not received!\nHANDSHAKE error!\n");
			}//end_of_if
			else
			{
				//comparing received string with ACK using strcmp, if it returns 0, handshake completes
				if(strcmp(buffer_One,"ACK")==0)
				{
					sleep(2);
					printf("ACK has received!\n");
					printf("Handshake Completed!\n");
				}//end_of_if
			}//end_of_else
			
			while(1)
			{
				/*from line 148 to line 185, we are performing data received  from server side*/
				
				// receiving message from client 
				receiveValue = recvfrom(socketfd,buffer_One,BUFFERSIZE,MSG_WAITALL,(struct sockaddr *)&client,&clientLength); 
				
				//copying value of buffer_One into buffer_Two
				strcpy(buffer_Two,buffer_One);
				
				if(receiveValue<0)
				{
					error("Message has not received!\n");
				}//end_of_if
				else
				{
					//sending the received message back to server to get aknowledgement
					sendValue=sendto(socketfd,buffer_One,strlen(buffer_One),MSG_WAITALL,(struct sockaddr *)&client,clientLength);
					if(sendValue<0)
					{
						error("Send failed\n");
					}//end_of_if
					
				}//end_of_else
					
				receiveValue=recvfrom(socketfd,buffer_One,BUFFERSIZE,MSG_WAITALL,(struct sockaddr *)&client,&clientLength);
				//checks acknowledgement received from client or not
				if(receiveValue<0)
				{
					error("Acknowledgement has not received!\n");
				}//end_of_if
				else
				{
				
					if(strcmp(buffer_One,ACK)==0)		
					{
						if(strcmp(buffer_Two,GOODBYE)==0)
						{
							printf("\n\nClient: %s\n",buffer_Two);
							sleep(1);
							exit(EXIT_SUCCESS);
						}

						printf("\n\nClient: %s\n",buffer_Two);		//printing message received from client
					}//end_of_if
					else
					{
						printf("\n\n\nData not received");	
					}//end_of_else	
				}//end_of_else
			}
		}//end_of_if
		else
		{
				error("Wrong Password!\n");
		}//end_of_else
	}//end_of_if
	else
	{
		printf("Wrong Server ID!\n");
	}//end_of_else
}//end_of_serverLogin()_function

