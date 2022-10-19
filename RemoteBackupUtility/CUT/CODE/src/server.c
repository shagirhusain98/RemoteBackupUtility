//the server side code 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <time.h>
#define SIZE 1024
#define backupdir "/home/kali/backup"
 

// function to write the contents of the file recieved from the client
void write_file(char* filename,int sockfd){
  int n;
  FILE *fp;
  //char *filename;
  char buffer[SIZE];
  
 
  fp = fopen(filename, "w");
  if(fp == NULL){
  	printf("Couldnt not make file\n");
	exit(1);
  }
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0 || strcmp(buffer,"0x007Xh") == 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

//a function to concatnate a string in between a string not to the end (concatinate string b where a has ".")
void spl(char* a,char* b){
	
	if(strstr(a+3,".") != NULL){
		char str2[200] = "\0";
		int n = strlen(a) - strlen(strstr(a+3,"."));
		strncat(str2, a, n);
		strcat(str2,"_");
		strcat(str2,b);
		strcat(str2,strstr(a+3,"."));
		//printf("%s\n",str2);
		strcpy(a,str2);
	}
	else{
		strcat(a,"_");
		strcat(a,b);
	}
	
}

 
int main(){
  //char *ip = "127.0.0.1";
  char* ip = "10.0.2.15";
  int port = 8080;
  int e;
  char* las_backup;
  time_t mytime = time(NULL);
  las_backup = ctime(&mytime);
  las_backup[strlen(las_backup)-1] = '\0';
  char lb[15];
  strncpy(lb,las_backup+4,3);
  lb[3] = '\0';
  strcat(lb,"_");
  strncat(lb,las_backup+8,2);
  lb[6] = '\0';
  strcat(lb,"_");
  strncat(lb,las_backup+11,5);
  lb[12] = '\0';
  printf("%s\n",lb);//current time.........................................
 
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");
 
  if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
 }else{
 perror("[-]Error in listening");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  
  int count;
  recv(new_sock, &count, sizeof(count), 0); //1
  char option[3];
  recv(new_sock, option, sizeof(option), 0); //2
  char dir[30];
  recv(new_sock, dir, sizeof(dir), 0); //3
  char filename[50];
  char filename2[50];
  char temp[30];
  strcpy(filename,backupdir);
   	  
  	   //full backup files 	
	   if(strncmp(option,"-ff",3) == 0){

		  for(int i = 0; i < count-3;i++){
		  	int k = recv(new_sock, temp, sizeof(temp),0);
			printf("%s\n",temp);
                        strcpy(filename2,filename);
			strcat(filename2,"/backup_of_"); 	  
			strcat(filename2,temp);
			printf("%s\n",filename2);
			write_file(filename2,new_sock);
			k = -1;			
		  }

	   }
	   //full backup directories
	   else if(strncmp(option,"-fd",3) == 0){
		  printf("%s\n",filename);
		  char dirn[50];
		  char dirn2[50];
	  	  for(int i = 2;i < count; i++){  
		  	recv(new_sock, dirn, sizeof(dirn), 0);
			strcpy(dirn2,backupdir);
			strcat(dirn2,dirn);
			printf("%s\n",dirn2);
			if(mkdir(dirn2, 0777) == 0){
				printf("Dir created successes\n");
			}
		  }		  


		  char name[150];
		  char msg[10];
		  while(1){
		  	recv(new_sock, msg, sizeof(msg), 0);
			//printf("%s\n",msg);

			if(strncmp(msg,"go",2) == 0){
				recv(new_sock, name, sizeof(name), 0);
				strcat(filename,name);
				printf("%s\n",filename);
				write_file(filename,new_sock);
				strcpy(filename,backupdir);
			}
			else if(strncmp(msg,"stop",4) == 0){
				printf("stopped\n");
				break;
			}
		  }
	   }
	   //incremental backup files
	   else if(strncmp(option,"-if",3) == 0){

		   char file[50];
		   char message[10];
		   while(1){
			recv(new_sock, message, sizeof(message), 0);
		     	if(strncmp(message,"go",2) == 0){
				printf("%s\n",message);	
		   		recv(new_sock, file, sizeof(file), 0);
		   		strcpy(filename2,filename);
		   		strcat(filename2,"/backup_of_");
		   		strcat(filename2,file);
				printf("%s\n",filename2);
				write_file(filename2,new_sock);
			}
			else if(strncmp(message,"stop",4) == 0){
				printf("stopped\n");
				break;
			}
		   }

	   }
	   //inremental backup directories
	   else if(strncmp(option,"-id",3) == 0){
		   	
		  printf("%s\n",filename);
		  char dirn[50];
		  char dirn2[50];
	  	  for(int i = 2;i < count; i++){  
		  	recv(new_sock, dirn, sizeof(dirn), 0);
			strcpy(dirn2,"/home/kali/backup");
			strcat(dirn2,dirn);
			printf("%s\n",dirn2);
			if(mkdir(dirn2, 0777) == 0){
				printf("Dir created successes\n");
			}
		  }

		  char message[10];
		  char nm[150];
		  char nm2[150];
	  	  while(1){
		  	recv(new_sock, message, sizeof(message), 0);
			printf("%s\n",message);
			if(strncmp(message,"go",2) == 0){
				//printf("%s\n",message);
				recv(new_sock, nm, sizeof(nm), 0);
				strcpy(nm2,"/home/kali/backup");
				strcat(nm2,nm);
				printf("%s\n",nm2);
				write_file(nm2,new_sock);
			}
			else if(strncmp(message,"stop",4) == 0){
				printf("stopped\n");
				break;
			} 
		  } 		  



	   }
	   //versioned backup files
	   else if(strncmp(option,"-vf",3) == 0){

		  for(int i = 0; i < count-3;i++){
		  	int k = recv(new_sock, temp, sizeof(temp),0);
			printf("%s\n",temp);
                        strcpy(filename2,filename);
			strcat(filename2,"/backup_at_");
	      		strcat(filename2,lb);
			strcat(filename2,"_of_");		
			strcat(filename2,temp);
			printf("%s\n",filename2);
			write_file(filename2,new_sock);
			k = -1;			
		  }
	   }
	   //versioned backup directories
	   else if(strncmp(option,"-vd",3) == 0){
		  printf("%s\n",filename);
		  char dirn[50];
		  char dirn2[50];
	  	  for(int i = 2;i < count; i++){  
		  	recv(new_sock, dirn, sizeof(dirn), 0);
			strcpy(dirn2,"/home/kali/backup");
			strcat(dirn2,dirn);
			printf("%s\n",dirn2);
			if(mkdir(dirn2, 0777) == 0){
				printf("Dir created successes\n");
			}
		  }		  


		  char name[150];
		  char msg[10];
		  while(1){
		  	recv(new_sock, msg, sizeof(msg), 0);
			//printf("%s\n",msg);

			if(strncmp(msg,"go",2) == 0){
				recv(new_sock, name, sizeof(name), 0);
				strcat(filename,name);
				printf("%s\n",filename);
				spl(filename,lb);			
				printf("%s\n",filename);
				write_file(filename,new_sock);
				strcpy(filename,backupdir);
			}
			else if(strncmp(msg,"stop",4) == 0){
				printf("stopped\n");
				break;
			}
		  }
	   }
	   else if(strncmp(option,"-sf",3) == 0){
		printf("Scheduled Backup\n");
	   }
	   else if(strncmp(option,"-sd",3) == 0){
	   	printf("Scheduled Backup\n");
                   
	   }
	   else{
		  printf("Not a valid option \n");
	   }
					  
  

  //write_file("data.txt",new_sock);
  //printf("[+]Data written in the file successfully.\n");
 
  return 0;
}
