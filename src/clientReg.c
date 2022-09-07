//include user defined headerfile
#include </home/praveen/Downloads/updatedone/srcupdated/inc/client.h>


/* addNode() function is for creating and adding newnode in linked  list" 
	return type = structure pointer of type unode
	parameter =  structure pointer of type unode and structure varible of type user
	no. of parameter = 2 
*/

unode* addNode(unode * head,user value)
{
	//allocating memory for newnode
	unode *newnode = (unode*)malloc(sizeof(unode));
	
	//storing value in node's data part
	newnode->data=value;
	//making its next null	
	newnode->next =NULL;
	
	unode *temp=NULL;
	
	if(head==NULL)
	{
		newnode->next=NULL;
		head=newnode;
	}
	else
	{
		temp=head;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=newnode;
		newnode->next=NULL;	
	}
	
	return head;
	free(newnode);
}//end_of_addNode()



/* readfile() function is for reading data from a file named "user.txt using linked  list" 
	return type = structure pointer of type unode
	parameter = File pointer and structure pointer of type unode
	no. of parameter = 2 
*/
	
unode * readfile(FILE *fptr, unode *head)
{
	user value;
	unode * newnode=NULL;
	
	// reading values from files using file pointer
	while(fscanf(fptr,"%s %s %d",value.name,value.password,&value.id)!=-1)
	{
		//calling addNode() function
		head=addNode(head,value); 
		
	}
	return head;
		
}//end_of_readfile




/* isPresent() function is for searching a data is present using auser id in a file named "user.txt" 
	return type = integer
	parameter = integer
	no. of parameter = 1 
*/
	
int isUserPresent(int id)
{
	unode *head=NULL;
	unode * temp=head;
	
	//opening file in read mode
	FILE *fptr=fopen("../data/user.txt","r");
	
	if(fptr!=NULL)
	{
		//calling readfile()
		head = readfile(fptr,head);	
	}
	else
	{
		error("Unable to Open File\n");		
	}
	temp=head;
	while(temp != NULL)
	{
	
		if(temp->data.id==id)	//checking id entered id matches id in linked list or not
		{
			return 0;
		} else 
		{
		
			temp=temp->next;
		}		
		
	}
	fclose(fptr);
	return 1;	
}//end_of_isPresent()



/* countnode() function is for storing data in linkedlist from a file named "valid.txt"  and counting the nodes
	return type = integer
	parameter = NULL
	no. of parameter = 0
*/

int countNode()
{
	unode * head=NULL;
	unode * temp=head;
	int count=1000;
	
	//opening file in read mode
	FILE *fptr=fopen("../data/user.txt","r");
	//checking if file pointer fptr is null or not
	if(fptr!=NULL)
	{
		//calling readfile() function
		head = readfile(fptr,head);
	}
	else
	{
		error("Unable to Open File\n");		
	}
	
	temp=head;
	
	if(head==NULL)
	{
		return count;
	}
	else
	{
		while(temp!=NULL)
		{
			count++;
			temp=temp->next;
		}
		return count;
	}
}//end_of_countNode()



/* writefile() function is for taking userinput and storing those in a file named "user.txt"
	return type = void
	parameter = file pointer
	no. of parameter = 1 
*/
void writefile(FILE * fptr)
{

	user value;
	system("clear");	
	printf("-------------------------------------------\n");
	printf("-------------------------------------------\n");
	printf("\t    REGISTRATION WINDOW\n");
	printf("-------------------------------------------\n");
	printf("-------------------------------------------\n");
	
	//taking name and password from user for registration	
	printf("\nEnter name: ");
	scanf("%s", value.name);
	printf("\nEnter password: ");
	scanf("%s", value.password);
	
	int id=countNode();	//calling countNode() function
	
	value.id=++id;
	
	fprintf(fptr,"%s\t\t%s\t\t%d\n",value.name,value.password,value.id);
	printf("\n\nYour user id is %d\n",id);
}//end_of_writefile()


	
/* userRegistration() function is for adding data
	return type = void
	parameter = null
	no. of parameter = 0 
*/
void registration()
{
	char choice;
	//opening file in append mode
	FILE *fptr=fopen("../data/user.txt","a+");	
	if(fptr==NULL)
	{
		error("unable to open file..\n");
		
	}//end_of_if
	
	do
	{
		//calling writefile()function
		writefile(fptr);
		printf("\n\n\nCONGRATULATIONS....!  You have successfully registered.\n\n\n");
		
		//asking user to give input for continue regitstration for another user if yes type 'y' otherwise 'n'	
		printf("Do you want to continue(y/n): ");
		scanf(" %c",&choice);
		if(choice=='n' || choice=='N')
		{
			system("clear");
			getMenu();
		}
		
	}while((choice!='n' || choice!='N')&& (choice=='y' || choice=='Y'));	//end_of_dowhile
	
	fclose(fptr);
}//end_of_registration()




