#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>

#include "function/account_creation.h"
#include "function/function.h"

#define WELCOME "\n\n\t\t###################################\t\t\n\t\t\n\t\t||***MYBANK MANAGEMENT SYSTEM***||\n\n\t\t###################################\t\t\n\n"
#define CREATE_MODE "1. Create an account.\n2.Having an account? Login.\n3. Exit\n\nEnter your choice:"
#define CHOICE "\n\nENTER YOUR CHOICE: \n\n1. Normal user Login.\n2. Joint account user.\n3. Administrator. \n4. Exit\n\n"

int main(){
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char result;

	//connection establishment
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	//server.sin_addr.s_addr=inet_addr("120.16.85.51"); //other machine
	server.sin_addr.s_addr=INADDR_ANY; //same machine
	server.sin_port=htons(8000);
	int connection_status = connect(sd,(struct sockaddr *)&server,sizeof(server));
	if(connection_status == -1)
	{
		printf("Error while connecting!\n");
		return 0;
	}
	while(1){
	printf("%s", WELCOME);
	printf("%s", CREATE_MODE);
	int choice;
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
			create_mode();
			break;
		case 2:
			chooseOption(sd);
			showMenu(sd);
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("Please enter valid choice.\n");
			break;
	}
}
	close(sd);
	return 0;
}
