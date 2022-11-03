//The client function which communicates with the server and other function

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "../include/header.h"
#define SIZE 1024


void send_file(char* filename, int sockfd){
  char data[SIZE] = {0};
  printf("%s\n",filename);
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(0);
  }

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(0);
    }
    bzero(data, SIZE);
  }
  strcpy(data,"0x007Xh");
  send(sockfd, data, sizeof(data), 0);
  bzero(data,SIZE);
}

int main(int argc, char* argv[]){
  char *ip = "10.0.2.15";
  //char *ip = "192.168.1.6";
  int port = 8080;
  int e;
  char* las_backup;
  time_t mytime = time(NULL);
  las_backup = ctime(&mytime);
  las_backup[strlen(las_backup)-1] = '\0';
  char lb[6];
  strncpy(lb,las_backup+4,6);
  lb[6] = '\0';
  printf("Last backup at : %s\n",lb);

  int sockfd;
  struct sockaddr_in server_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(0);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(0);
  }
 printf("[+]Connected to Server.\n");

 printf("\n");
 int k = argc;
 send(sockfd, &k, sizeof(int), 0);
 char option[3];
 strcpy(option,argv[1]);
 send(sockfd, option, sizeof(option), 0);
 char dir[30];
 strcpy(dir,argv[2]);
 send(sockfd, dir, sizeof(dir), 0);
 char filename[50];
 strcat(filename,"/");
 strcat(filename,dir);
 strcat(filename,"/");

	//Full backup for ***files***
	//./client1.c -ff dir file1 file2 file3......
	if(strcmp(option,"-ff") == 0){
        	if(argc<4)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -ff dir file1 file2 file3......");
        		exit(0);
        	}
		else
			full(filename,argc,argv,sockfd);
	}
	//Full backup for ***directories***
	//./client -fd dir1 dir2 dir3 .......
	else if(strcmp(option,"-fd") == 0){
        	if(argc<3)
		{
       			 printf(" Invalid Usage : No folder name entered!!!\n");
        		 printf(" Usage: ./client -fd dir1 dir2 dir3 .......");
        		 exit(0);
        	}
		else
			full_dir(filename,argc,argv,sockfd);
	}
	//incremental backup for ***files***
	//./client -if dir file1 file2 file3 ..............
	else if(strcmp(option,"-if") == 0){
		if(argc<4)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -if dir file1 file2 file3......");
        		exit(0);
        	}
		else
			incremental(filename,argc,argv,sockfd,lb);
	}
	//incremental backup for ***directories**
	//./client -id dir1 dir2 dir3 ...............
	else if(strcmp(option,"-id") == 0){
        	if(argc<3)
		{
        		printf(" Invalid Usage : No folder name entered!!!\n");
        		printf(" Usage: ./client -id dir1 dir2 dir3 .......");
        		exit(0);
        	}
		else
			incremental_dir(filename,argc,argv,sockfd,lb);
	}
	//versioned backup files
	//./client -vf dir file1 file2 file3 .........
	else if(strcmp(option,"-vf") == 0){
		if(argc<4)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -vf dir file1 file2 file3......");
        		exit(0);
        	}
		else
			versioned(filename,argc,argv,sockfd);
	}
	//versioned backup directoreis
	else if(strcmp(option,"-vd") == 0){
        	if(argc<3)
		{
        		printf(" Invalid Usage : No folder name entered!!!\n");
        		printf(" Usage: ./client -vd dir1 dir2 dir3 .......");
        		exit(0);
        	}
		else
			versioned_dir(filename,argc,argv,sockfd);
	}
	//scheduled backup for files
	//./client -sf dir "mm hh dom mon dow" file1 file2 file3 .........
	else if(strcmp(option,"-sf") == 0){
		if(argc<5)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -sf dir 'mm hh dom mon dow' file1 file2 file3 .........");
        		exit(0);
        	}
		else
			scheduled(filename,argc,argv,sockfd,dir);
	}
	//scheduled backup for files
	//./client -sd "mm hh dom mon dow" dir1 dir2 dir3 ...............
	else if(strcmp(option,"-sd") == 0){
		if(argc<4)
		{
        		printf(" Invalid Usage : No folder name entered!!!\n");
        		printf(" Usage: /client -sd 'mm hh dom mon dow' dir1 dir2 dir3 ............");
        		exit(0);
        	}
		else
			scheduled_dir(filename,argc,argv,sockfd);
	}
	else {
		printf("Invalid Option please choose from any of the options mentioned below\n");
		printf("-ff for full backup for files\n");	
		printf("-fd for full backup for Directories\n");	
		printf("-if for incremental backup for files\n");	
		printf("-id for incremental backup for Directories\n");	
		printf("-vf for Versioned backup for files\n");	
		printf("-vd for Versioned backup for Directories\n");	
		printf("-sf for Scheduled backup for files\n");	
		printf("-sd for Scheduled backup for Directories\n");	
	}

  printf("[+]Closing the connection.\n");
  close(sockfd);
  return 0;
}
