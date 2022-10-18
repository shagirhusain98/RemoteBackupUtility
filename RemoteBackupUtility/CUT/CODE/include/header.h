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
