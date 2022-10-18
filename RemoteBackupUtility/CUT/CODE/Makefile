main: read_flight.o read_customer.o ticket_alloc.o project.o
	gcc -g -o ./obj/reservation.exe ./obj/read_flight.o ./obj/read_customer.o ./obj/ticket_alloc.o ./obj/project.o -lpthread
read_flight.o: ./src/read_flight.c
	gcc -g -o ./obj/read_flight.o ./src/read_flight.c -c
read_customer.o: ./src/read_customer.c
	gcc -g -o ./obj/read_customer.o ./src/read_customer.c -c
ticket_alloc.o: ./src/ticket_alloc.c
	gcc -g -o ./obj/ticket_alloc.o ./src/ticket_alloc.c -c
project.o: ./src/project.c
	gcc -g -o ./obj/project.o ./src/project.c -c
clean:
	rm ./obj/*.exe ./obj/*.o
