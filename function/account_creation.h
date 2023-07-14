#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include "generate_userID.h"
#include "account.h"

#define mode 0744
#define flags O_RDWR | O_CREAT


void create_admin(){
	int fd=open("Admin",flags,mode);
	admin newAdmin;
	int size=lseek(fd,0,SEEK_END);
  //printf("%d",size);
	printf("Please enter the name of the admin: ");
	scanf(" %[^\n]",newAdmin.username);
	//printf("Please enter the password(max 10 characters): ");
	//scanf(" %[^\n]",newAdmin.password);
	char *pass=getpass("Please enter the password(max 10 characters): ");
	memcpy(newAdmin.password,pass,sizeof(pass));
	if(size==0) newAdmin.userID=1000;
	else newAdmin.userID=getNewUserID3();
	printf("Your userID is : %d\n",newAdmin.userID);
	write(fd,&newAdmin,sizeof(admin));
	close(fd);
}

void create_normuser(){
	int fd=open("Normal_user",flags,mode);
	int size=lseek(fd,0,SEEK_END);
	normalUser newNUser;
	printf("Please enter the name of the normal user: ");
	scanf(" %[^\n]",newNUser.name);
	//printf("Please enter the password(max 10 characters): ");
	//scanf(" %[^\n]",newNUser.password);
	char *pass=getpass("Please enter the password(max 10 characters): ");
	memcpy(newNUser.password,pass,sizeof(pass));
	if(!size) newNUser.userID=1000;
	else newNUser.userID=getNewUserID1();
	printf("Please enter the balance amount: Rs. ");
	scanf("%f",&newNUser.balance);
	//newNUser.balance=1000;
	newNUser.account_no=(newNUser.userID-1000)+100000;
	printf("Your userID is : %d\n",newNUser.userID);
	strcpy(newNUser.status,"ACTIVE");
	write(fd,&newNUser,sizeof(normalUser));
	close(fd);
}

void create_jntuser(){
	int fd=open("Joint_user",flags,mode);
	int size=lseek(fd,0,SEEK_END);
	jointUser newJUser;
	printf("Please enter the main name of the joint user: ");
	scanf(" %[^\n]",newJUser.name1);
	printf("Please enter the second name of the joint user: ");
	scanf(" %[^\n]",newJUser.name2);
	//printf("Please enter the password(max 10 characters): ");
	//scanf(" %[^\n]",newJUser.password);
	char *pass=getpass("Please enter the password(max 10 characters): ");
	memcpy(newJUser.password,pass,sizeof(pass));
	if(!size) newJUser.userID=1000;
	else newJUser.userID=getNewUserID2();
	printf("Please enter the balance amount: Rs. ");
	scanf(" %f",&newJUser.balance);
	//newJUser.balance=1000;
	newJUser.account_no=(newJUser.userID-1000)+100000;
	printf("Your userID is : %d\n",newJUser.userID);
	strcpy(newJUser.status,"ACTIVE");
	write(fd,&newJUser,sizeof(jointUser));
	close(fd);
}

void create_mode(){
	printf("\e[1;1H\e[2J");
	printf("\n\n\n\t\t**********************************************************\n");
	printf("\t\t***   WELCOME TO BANKING SYSTEM  Account Creation Section ***\n");
	printf("\t\t**********************************************************\n\n\n");
	int choice,select;
	do {
		printf("Enter your choice:\n1. Admin\n2. Normal user\n3. Joint user\nchoice:");
		scanf("%d",&choice);
		switch (choice) {
			case 1:
					create_admin();
					printf("Do you want to add more account(0/1)? ");
					scanf("%d",&select);
					break;
			case 2:
					create_normuser();
					printf("Do you want to add more account(0/1)? ");
					scanf("%d",&select);
					break;
			case 3:
					create_jntuser();
					printf("Do you want to add more account(0/1)? ");
					scanf("%d",&select);
					break;
		}
	} while(select);
}
