//C file for versioned backup of files and directories
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "../include/header.h"



//the versioned() function to send the files from client to server  
void versioned(char* filename,int argc,char **argv,int sockfd){
  
      for(int i = 3;i < argc;i++){

			      char temp[30];
			      strcpy(temp,argv[i]);
            		      send(sockfd,temp,sizeof(temp),0);
            		      printf("%s\n",temp);
            		      strcpy(temp,filename);
            		      strcat(temp,argv[i]);
            		      printf("%s\n",temp);
	 		      send_file(temp,sockfd);

		}
}

//the versioned_dir() function to send all files present in directories to server
void versioned_dir(char* filename,int argc,char **argv,int sockfd){
    filename[strlen(filename) - 1] = '\0';
		printf("%s\n",filename);
		char dirn[50];
		for(int j = 2;j < argc;j++){

			strcpy(dirn, argv[j]);
			send(sockfd, dirn, sizeof(dirn), 0 );
			printf("%s\n", argv[j]);
		}



		char msg[10];
		struct dirent *de;
		for(int i = 2;i < argc;i++){
			DIR *dr = opendir(argv[i]);
			char name[150];
			char name2[150];
			strcpy(name,argv[i]);
			strcat(name,"/");
			strcpy(name2,name);

			if(dr == NULL){
				printf("Couldn't open the directory");
			}

			while((de = readdir(dr)) != NULL){
				if(strlen(de->d_name) > 2){
					strcat(name2,de->d_name);
					strcpy(msg,"go");
					send(sockfd, msg, sizeof(msg), 0);
					send(sockfd, name2, sizeof(name2), 0);
					send_file(name2,sockfd);
					printf("%s\n",name2);
					strcpy(name2,name);
				}
			}
		}

		strcpy(msg,"stop");
		send(sockfd, msg, sizeof(msg), 0);
}
