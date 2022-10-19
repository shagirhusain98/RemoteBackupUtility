//C file for scheduled() and scheduled_dir() functions for scheduled backup

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "../include/header.h"


//scheduled() function to create a cronjob and update it to the contab (conjob to backup files)
void scheduled(char* filename,int argc,char **argv,int sockfd,char* dir){
  FILE* con = fopen("config","a");
		if(con == NULL){
			printf("Config file doesn't exist\n");
		}

		char ce[200];
		char sbt[200];
		strcpy(ce,argv[3]);
		strcpy(sbt,ce);
		strcat(ce," cd /home/kali/RBU && ./client -ff ");
		strcat(ce,dir);

		for(int i = 4;i < argc;i++){
			//printf("%s\n",argv[i]);
			strcat(ce," ");
			strcat(ce,argv[i]);
		}

		send(sockfd, sbt, sizeof(sbt), 0);
		strcat(ce,"\n");
		printf("%s\n",ce);
		fprintf(con, "%s", ce);
}

//scheduled() function to create a cronjob and update it to the contab (cronjob to backup directories)
void scheduled_dir(char* filename,int argc,char **argv,int sockfd){

  FILE* con = fopen("config","a");
		if(con == NULL){
			printf("Config file doesn't exist\n");
		}
  
		char ce[200];
		strcpy(ce, argv[2]);
		strcat(ce," cd ../RBU && ./client -fd ");

		for(int i = 3; i < argc; i++){
			strcat(ce," ");
			strcat(ce, argv[i]);
		}
		strcat(ce,"\n");
		printf("%s\n",ce);
		fprintf(con, "%s", ce);
  
}
