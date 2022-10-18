#define size 100
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
extern pthread_mutex_t lock_unavailable_cust;
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
void insert_at_end(cl *cust,customer * cr){
    if(cust->head==NULL){
        cust->head=cr;
    }
    if(cust->tail==NULL){
        cust->tail=cr;
    }
    else{
        cust->tail->next =cr;
        cust->tail=cr;
    }
}
void allocate_tickets(char * cust_info){
    char *temp_cust_info;
    temp_cust_info =(char *)calloc(100,sizeof(char));
    strcpy(temp_cust_info,cust_info);
    char words[4][100];
    char *token1 =strtok(temp_cust_info,"|");
    int g=0;
    while(token1!=NULL){
        strcpy(words[g],token1);
        token1 =strtok(NULL,"|"); 
        g++;
    }
    int j=0;
    customer *newNode;
    newNode =(customer *)calloc(1,sizeof(customer));
    newNode->next=NULL;
    newNode->cust_id =(char *)calloc(strlen(words[0]),sizeof(char));
    strcpy(newNode->cust_id,words[0]);
    newNode->cust_name =(char *)calloc(strlen(words[1]),sizeof(char));
    strcpy(newNode->cust_name,words[1]);
    newNode->cust_date =(char *)calloc(strlen(words[2]),sizeof(char));
    strcpy(newNode->cust_date,words[2]);
    newNode->no_of_seats =atoi(words[3]);
    flight *temp =NULL;
    temp= fd->head;
    int flag=0;
    while(temp){
        if(strcmp(newNode->cust_date,temp->date)==0){
            pthread_mutex_lock((&temp->lock));
            if(temp->available_seats>=newNode->no_of_seats){
                temp->available_seats-=newNode->no_of_seats;
                insert_at_end(temp->ptr,newNode);
                flag=1;
                break;
            }
        }
        temp=temp->next;
    }
    pthread_mutex_unlock((&temp->lock));
    if(flag==0){
        FILE *fpw;
        fpw =fopen("..//data//Unavailable_Flights.txt","a");
        if(fpw==NULL){
            printf(" Cannot open file for writing invalid details\n");
            //return 0;
        }
        pthread_mutex_lock((&lock_unavailable_cust));
        fprintf(fpw,"%s",cust_info);
        fclose(fpw);
        pthread_mutex_unlock((&lock_unavailable_cust));
    }
}