#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#define SIZE 100
#include "../include/header.h"
pthread_mutex_t lock_invalid_cust;
pthread_mutex_t lock_unavailable_cust;
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
void create_flight_LL(fl *fd){
    fd->head=NULL;
    fd->tail=NULL;
}
fl *fd;
int main(int argc, char *argv[])
{
    //validating argvs
    if(argc<2){
        printf(" Invalid Usage : No booking data file name entered!!!\n");
        printf(" Usage: <executable file> <booking_file1>  <booking_file2> ...");
        exit(1);
    }
    //creating linked list to store flight details;
    fd = (fl *)calloc(1,sizeof(fl));
    create_flight_LL(fd);
    read_flight("..//data//flights.dat");

    //creating an array of thread_ids which are pthread_t type 

    pthread_t thread_id[argc-1];
    
    //pthread initialisation
    if (pthread_mutex_init(&lock_invalid_cust, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
        
    int returnValue;
    //creating threads and using join in main for all the threads
    for(int i=1;i<argc;i++)
    {
        if (returnValue = pthread_create( &thread_id[i], NULL,read_customer_data , (void *)argv[i]))
        {
            printf("WARNING: thread creation for  [ file: %s] failed\n", argv[i]);
        }
    }
    //destroying mutex
    flight *temp =fd->head;

    while(temp!=NULL){
        pthread_mutex_destroy(&temp->lock);
        temp=temp->next;
    }
    pthread_mutex_destroy(&lock_invalid_cust);
    for(int i=1;i<argc;i++)
    {
       pthread_join(thread_id[i], NULL); 
    }

    flight * temp_f;
    temp_f=fd->head;
    while(temp_f){
            printf("\n----Printing Reservation Chart ----");
            printf("\nFlight ID\tFlight Name\tDate of Journey\tFlight Capacity\tAvailable Seats");
            printf("\n%5s\t%25s\t%5s\t%10d\t%10d",temp_f->flight_id,temp_f->flight_name,temp_f->date,temp_f->total_seats,temp_f->available_seats);
            customer * temp1;
            temp1=temp_f->ptr->head;
            if(temp1){
                printf("\n----Printing Passenger Details----");
                printf("\nPassenger ID\tPassenger Name\tDate of Journey\tSeats Booked");
                while(temp1){
                    // printf("\n%s\t%s\t%s",temp1->cust_id,temp1->cust_name,temp1->cust_date);
                    printf("\n%15s\t%15s\t%15s",temp1->cust_id,temp1->cust_name,temp1->cust_date);
                    printf("\t%15d",temp1->no_of_seats);
                    temp1=temp1->next;
                }
                printf("\n");
            }
            else
            {
                printf("\n---No Passengers for this flight for the given date of Journey---");
            }
            temp_f=temp_f->next;
            printf("\n");
    }
    return 0;
}
