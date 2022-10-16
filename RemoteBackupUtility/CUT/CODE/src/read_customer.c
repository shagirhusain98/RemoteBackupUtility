#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include "../include/header.h"
#define SIZE 100
extern pthread_mutex_t lock_invalid_cust;
struct customer_details{
    char *cust_id;
    char* cust_name;
    char date[10];
    int no_of_seats;
    struct customer_details *next;
};
typedef struct customer_details customer; 
struct customer_LL{
    customer * head;
    customer *tail;
}; 
typedef struct customer_LL cl;
extern struct flight_LL *fd;

void *read_customer_data(void *file)
{
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("---Not able to open %s file.---\n", fp);
        exit(1);
    }
    char *str;
    str = (char*)calloc(100,sizeof(char));
    char *cust_info;
    cust_info = (char*)calloc(100,sizeof(char));
    char words[SIZE][SIZE];
    int j=0;
    while (1)
    {
        if(fgets(str, 100, fp) == NULL)
            break;
        else 
        {
            //tokeinsing all the strings and storing them in an array
            int counter=0;
            int date_valid = 0;
            strcpy(cust_info,str); 
            int k = strlen(str);
            str[k-1]= '\0'; //last letter of the string has to be made as '\0'
        // str[k-2]='\0';
            char* token = strtok(str, "|");
            while(token != NULL)
            {
                counter++;
                if(counter==3){
                    if(strlen(token)==10){
                        date_valid =1;
                    }
                }
                    strcpy(words[j],token);
                    token = strtok(NULL,"|");
                    j++;
            }
            if(counter==4 && date_valid){
                allocate_tickets(cust_info);
            }
            else 
            {
                //invalid customer save it in a invalid customer linked list
                FILE *fpw;
                fpw =fopen("..//data//Invalid_Passengers.txt","a");
                if(fpw==NULL){
                    printf("cannot open file for writing invalid details\n");
                }
                pthread_mutex_lock((&lock_invalid_cust));
                fprintf(fpw,"%s\n",cust_info);
                fclose(fpw);
                pthread_mutex_unlock((&lock_invalid_cust));
            }
        }
    }
    fclose(fp);      
}


