//allocate and create for every ptr(linked list)
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#define SIZE 100
struct customer_details{
    char *cust_id;
    char* cust_name;
    char *cust_date;
    int no_of_seats;
    struct customer_details *next;
};
typedef struct customer_details customer;
struct customer_LL{
    customer * head;
    customer *tail;
};
typedef struct customer_LL cl; 
struct flight_details{
    char *flight_id;
    char *flight_name;
    char date[10];
    int total_seats;
    int available_seats;
    pthread_mutex_t lock;
    cl *ptr;
    struct flight_details *next;
    };
typedef struct flight_details flight;
struct flight_LL{
    flight * head;
    flight *tail;
};
typedef struct flight_LL fl;
extern struct flight_LL *fd;
 
void create(cl *cd){
    cd->head=NULL;
    cd->tail=NULL;
}

int insert_flight(char *flight_info){
    int j=0;
    flight *newNode;
    newNode =(flight *)calloc(1,sizeof(flight));
    newNode->next=NULL;
    char * token =strtok(flight_info,"|");
    while(token!=NULL){
        switch(j){
            case 0:newNode->flight_id =(char *)calloc(strlen(token),sizeof(char));
             strcpy(newNode->flight_id,token);
            break;
            case 1:newNode->flight_name =(char *)calloc(strlen(token),sizeof(char));
            strcpy(newNode->flight_name,token);
             break;
            case 2: strcpy(newNode->date,token);
            break;
            case 3: 
                   newNode->total_seats =atoi(token);
                   newNode->available_seats =atoi(token); 
                if (pthread_mutex_init(&(newNode->lock),NULL) != 0)
                {
                    printf("\n mutex init failed\n");
                    return 1;
                }
                newNode->ptr = (cl *)calloc(1,sizeof(cl));
                create(newNode->ptr);
                break;
        }
        token =strtok(NULL,"|");
        j++;
    }
    if(fd->head==NULL){
        fd->head=newNode;
    }
    if(fd->tail==NULL){
        fd->tail =newNode;
    }
    else{
        fd->tail->next=newNode;
        fd->tail=newNode;
    }
    return 0;
}
void read_flight(char * file){
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("---Not able to open %s file.---\n", fp);
        exit(1);
    }
    char *flight_info;
    flight_info=(char *)calloc(100,sizeof(char));
    char *temp_info;
    temp_info=(char *)calloc(100,sizeof(char));

    while (1)
    {
        if(fgets(flight_info, 100, fp) == NULL)
            break;
        else 
        {
            //tokeinsing all the strings and storing them in an array 
            strcpy(temp_info,flight_info);
            int counter =0; int date_valid =0; int seats_valid =0;
            int k = strlen(temp_info);
            temp_info[k-1]= '\0'; //last letter of the string has to be made as '\0'
            char* token = strtok(temp_info, "|");
            while(token != NULL)
            {
                if(counter == 2){
                    if(strlen(token)==10){
                        date_valid =1;
                    }
                }
                if(counter==3){
                    if(atoi(token) > 0){
                        seats_valid =1;
                    }
                }
                counter++;
                token =strtok(NULL,"|");
            }
            if((counter==4)&&(seats_valid)&&(date_valid)){
                insert_flight(flight_info);
            }
       }
    }
}
