#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define SUCCESS 1
#define FAILURE 0
int read_customer(char arr[])
{
	int counter=0,j=0,valid=0;
    char* token = strtok(arr, "|");
    while(token != NULL)
    {
		switch(j)
	   {
		   case 2:
			   if(strlen(token)==10)
			   {
				   valid=1;
			   }
	   }
	   j++;	
       counter++;
	   token = strtok(NULL,"|");
	}
    if(counter==4 && valid==1)
		return SUCCESS;
	else
		return FAILURE;
}
