#define EXIT_SUCCESS 1
#define EXIT_FAILURE 0
#define MAXFLIGHTS 6
#define MAXLENGTH 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int allocate_tickets(char arr[], int seats)
{
    int available_seats = 120;
	char flight_arr[MAXFLIGHTS][MAXLENGTH] = {"Indigo Airlines", "Spicejet Airlines","American Airlines","Vistara Airlines", "Jet Airlines","Akasa Airlines"};
	if(seats<0){
		return 0;
	}

	int flag=0;
	for(int i=0;i<MAXFLIGHTS;i++){
        if(strcmp(arr, flight_arr[i])==0){
			flag=0;
			if(available_seats>=seats){
				return 1;
			}
			else{
				return 0;
			}
		}
		flag=1;
	}
	//flight unavailable
	if(flag ==1 ){
		return 0;
	}
}
