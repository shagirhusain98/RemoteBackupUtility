//C file for incremental() and incremental_dir() functions for incremenal backup of files and directories 

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


//incremental() function to backup only the files that have been changed/modified today
void incremental(char* filename,int argc,char **argv,int sockfd,char* lb){
  
    char message[10] ;
		for(int i = 3; i < argc; i++){

			char file[50];
			char go[50];
			strcpy(file,filename);
			strcat(file,argv[i]);
			strcpy(go,argv[i]);

			struct stat filestat;
			printf("%s\n",file);
			stat(file,&filestat);
			char bin[6];
			//bin[0] = '\0';
			char time_modified[30];
			//time_modified[0] = '\0';
			strcpy(time_modified, ctime(&filestat.st_ctime));
			strncat(bin,time_modified+4,sizeof(bin));
			strcpy(time_modified,bin);
			printf("last_backup : %s\n",lb);
			printf("File changed at : %s\n", time_modified);
			if(strncmp(lb,time_modified,6) == 0){
				printf("Backup Needed \n");
				strcpy(message,"go");
				int r = send(sockfd, message, sizeof(message), 0);
				int s = send(sockfd, go, sizeof(go), 0);
				printf("%d %d\n",r,s);
				send_file(file,sockfd);
			}
			printf("\n");
			bin[0] = '\0';
		}
		strcpy(message,"stop");
		send(sockfd, message, sizeof(message), 0);
  
}


//incremental_dir() function to backup only the files in directories that have been changed/modified today
void incremental_dir(char* filename,int argc,char **argv,int sockfd,char* lb){
  
  char dirn[50];
		for(int j = 2;j < argc;j++){

			strcpy(dirn, argv[j]);
			send(sockfd, dirn, sizeof(dirn), 0 );
			printf("%s\n", argv[j]);

		}
		printf("\n");

		char message[10];
		struct dirent *de;
		for(int i = 2; i < argc; i++){
			strcpy(filename,argv[i]);
			char tm[30];
			char dbin[6];
			char nm[150];

			struct stat fs;
			stat(filename,&fs);
			printf("%s\n",filename);
			strcpy(tm,ctime(&fs.st_ctime));
			strncat(dbin,tm+4,sizeof(dbin));
			printf("last backup : %s\n",lb);
			printf("Directory changed : %s\n",dbin);

			if(strncmp(lb,dbin,6) == 0){
				printf("backup needed\n");

				DIR *dr = opendir(filename);
				if(dr == NULL){
					printf("Couldn't open the directory");
				}

				while((de = readdir(dr)) != NULL){
					if(strlen(de->d_name) > 2){
						strcpy(nm,filename);
						strcat(nm,"/");
						strcat(nm,de->d_name);
						strcpy(message,"go");
						send(sockfd, message, sizeof(message), 0);
						send(sockfd, nm, sizeof(nm), 0);
						send_file(nm,sockfd);
						printf("%s\n",nm);
					}
				}
				printf("\n");
   			}
			dbin[0] = '\0';
		}
		strcpy(message,"stop");
		send(sockfd, message, sizeof(message), 0);
  
}
