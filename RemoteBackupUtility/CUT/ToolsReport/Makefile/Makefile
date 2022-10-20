#compiler
GCC = gcc
#output file
LFLAGS = -o
#binary file directory
BIN = ../bin
#source file directory
SRC = ../src
#object file directory
OBJ = ../obj








#compile all source file
all: buildServer buildClient

buildServer: $(OBJ)/server.o $(OBJ)/translate.o $(OBJ)/modify.o $(OBJ)/delete.o $(OBJ)/writetofile.o
	$(GCC) $(LFLAGS) $(BIN)/server $(OBJ)/server.o $(OBJ)/translate.o $(OBJ)/modify.o $(OBJ)/delete.o $(OBJ)/writetofile.o    

buildClient: $(OBJ)/client.o
	$(GCC) $(LFLAGS) $(BIN)/client $(OBJ)/client.o 

$(OBJ)/server.o: $(SRC)/server.c
	$(GCC) -c  $(LFLAGS) $(OBJ)/server.o $(SRC)/server.c 
	
$(OBJ)/client.o: $(SRC)/client.c
	$(GCC) -c $(LFLAGS) $(OBJ)/client.o $(SRC)/client.c 

$(OBJ)/translate.o: $(SRC)/translate.c
	$(GCC) -c $(LFLAGS) $(OBJ)/translate.o $(SRC)/translate.c
 
$(OBJ)/modify.o: $(SRC)/modify.c
	$(GCC) -c $(LFLAGS) $(OBJ)/modify.o $(SRC)/modify.c 

$(OBJ)/delete.o: $(SRC)/delete.c
	$(GCC) -c $(LFLAGS) $(OBJ)/delete.o $(SRC)/delete.c 

$(OBJ)/writetofile.o: $(SRC)/writetofile.c
	$(GCC) -c $(LFLAGS) $(OBJ)/writetofileo $(SRC)/writetofile.c 



#run server
server:
	 ./$(BIN)/server

#run client
client:
	 ./$(BIN)/client

clean:
	rm $(BIN)/server 
	rm $(BIN)/client 
	rm $(OBJ)/server.o 
	rm $(OBJ)/client.o 
	rm $(OBJ)/translate.o
	rm $(OBJ)/modify.o
	rm $(OBJ)/delete.o
	rm $(OBJ)/writetofile.o
	
