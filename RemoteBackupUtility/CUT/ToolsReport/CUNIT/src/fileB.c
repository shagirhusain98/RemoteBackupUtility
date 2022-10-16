#define EXIT_SUCCESS 1
#define EXIT_FAILURE 0
#include <string.h>
int flight_data(char arr[])
{
	int counter=0,j=0,valid=0;
        //strcpy(cust_info,str); 
        //int k = strlen(arr);
        //arr[k-1]= '\0'; //last letter of the string has to be made as '\0'
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
	{
		return EXIT_SUCCESS;
        }
	else
		return EXIT_FAILURE;
}
