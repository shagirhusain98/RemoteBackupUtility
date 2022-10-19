//Header file to include all the functions

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void full(char* filename,int argc,char **argv,int sockfd);
void full_dir(char* filename,int argc,char **argv,int sockfd);
void incremental(char* filename,int argc,char **argv,int sockfd,char* lb);
void incremental_dir(char* filename,int argc, char **argv,int sockfd,char* lb);
void versioned(char* filename,int argc, char **argv,int sockfd);
void versioned_dir(char* filename,int argc, char **argv,int sockfd);
void scheduled(char* filename,int argc,char **argv,int sockfd,char* dir);
void scheduled_dir(char* filename,int argc,char **argv,int sockfd);
void send_file(char* filename,int sockID);
void write_file(char* filename, int sockID);
		 
#endif
