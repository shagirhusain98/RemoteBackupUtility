#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#define SIZE 1024

void send_file(char* filename, int sockfd){
  int n;
  char data[SIZE] = {0};

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
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
  char lbb[15];
  strncpy(lb,las_backup+4,6);
  lb[6] = '\0';
  printf("Last backup at : %s\n",lb);

  int sockfd;
  struct sockaddr_in server_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");

 printf("\n");
 //printf("%d %s %s\n",argc,argv[1],argv[2]);
 int k = argc;
 send(sockfd, &k, sizeof(int), 0);
 char option[3];
 strcpy(option,argv[1]);
 send(sockfd, option, sizeof(option), 0);
 char dir[30];
 strcpy(dir,argv[2]);
 send(sockfd, dir, sizeof(dir), 0);
 char filename[50];
 strcpy(filename, "../");
 strcat(filename,dir);
 strcat(filename,"/");

	//Full backup for ***files***
	//./client1.c -ff dir file1 file2 file3......
	if(strcmp(option,"-ff") == 0){

        	if(argc<4)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -ff dir file1 file2 file3......");
        		exit(1);
        	}

		for(int i = 3;i < argc;i++){

			int k;
			char temp[30];
			strcpy(temp,argv[i]);
			send(sockfd,temp,sizeof(temp),0);
			printf("%s\n",temp);
			strcpy(temp,filename);
 	 		strcat(temp,argv[i]);
			//strcpy(filename,temp);
	 		printf("%s\n",temp);
	 		send_file(temp,sockfd);

		}

	}
	//Full backup for ***directories***
	//./client -fd dir1 dir2 dir3 .......
	else if(strcmp(option,"-fd") == 0){

        	if(argc<3)
		{
       			 printf(" Invalid Usage : No folder name entered!!!\n");
        		 printf(" Usage: ./client -fd dir1 dir2 dir3 .......");
        		 exit(1);
        	}

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
	//incremental backup for ***files***
	//./client -if dir file1 file2 file3 ..............
	else if(strcmp(option,"-if") == 0){
        	
		if(argc<4)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -if dir file1 file2 file3......");
        		exit(1);
        	}

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
			char time_modified[30];
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
	//incremental backup for ***directories**
	//./client -id dir1 dir2 dir3 ...............
	else if(strcmp(option,"-id") == 0){

        	if(argc<3)
		{
        		printf(" Invalid Usage : No folder name entered!!!\n");
        		printf(" Usage: ./client -id dir1 dir2 dir3 .......");
        		exit(1);
        	}

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
	//versioned backup files
	//./client -vf dir file1 file2 file3 .........
	else if(strcmp(option,"-vf") == 0){
        	
		if(argc<4)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -vf dir file1 file2 file3......");
        		exit(1);
        	}

		for(int i = 3;i < argc;i++){

			int k;
			char temp[30];
			strcpy(temp,argv[i]);
			send(sockfd,temp,sizeof(temp),0);
			printf("%s\n",temp);
			strcpy(temp,filename);
 	 		strcat(temp,argv[i]);
			//strcpy(filename,temp);
	 		printf("%s\n",temp);
	 		send_file(temp,sockfd);

		}
	}
	//versioned backup directoreis
	else if(strcmp(option,"-vd") == 0){
        	if(argc<3)
		{
        		printf(" Invalid Usage : No folder name entered!!!\n");
        		printf(" Usage: ./client -vd dir1 dir2 dir3 .......");
        		exit(1);
        	}

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
	//scheduled backup for files
	//./client -sf dir "mm hh dom mon dow" file1 file2 file3 .........
	else if(strcmp(option,"-sf") == 0){
        	
		if(argc<5)
		{
        		printf(" Invalid Usage : No file name entered!!!\n");
        		printf(" Usage: ./client1.c -sf dir 'mm hh dom mon dow' file1 file2 file3 .........");
        		exit(1);
        	}

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
	//scheduled backup for files
	//./client -sd "mm hh dom mon dow" dir1 dir2 dir3 ...............
	else if(strcmp(option,"-sd") == 0){
        	
		if(argc<4)
		{
        		printf(" Invalid Usage : No folder name entered!!!\n");
        		printf(" Usage: /client -sd 'mm hh dom mon dow' dir1 dir2 dir3 ............");
        		exit(1);
        	}

		FILE* con = fopen("config","a");
		if(con == NULL){
			printf("Config file doesn't exist\n");
		}
		char ce[200];
		char sbt[200];
		strcpy(ce, argv[2]);
		strcpy(sbt, ce);
		strcat(ce," cd /home/kali/RBU && ./client -fd ");

		for(int i = 3; i < argc; i++){

			strcat(ce," ");
			strcat(ce, argv[i]);
		}
		send(sockfd, sbt, sizeof(sbt), 0);
		strcat(ce,"\n");
		printf("%s\n",ce);
		fprintf(con, "%s", ce);

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


  //send_file("send.txt", sockfd);
  //printf("[+]File data sent successfully.\n");


  printf("[+]Closing the connection.\n");
  close(sockfd);

  return 0;
}
