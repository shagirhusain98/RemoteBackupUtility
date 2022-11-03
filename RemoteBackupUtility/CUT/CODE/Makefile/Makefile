#compiler
GCC = gcc
#output file
LFLAGS = -o
#source file directory
SRC = ../src
#object file directory
OBJ = ../obj

main: $(OBJ)/full.o $(OBJ)/incremental.o $(OBJ)/versioned.o $(OBJ)/scheduled.o $(OBJ)/client.o
	$(GCC) -g $(LFLAGS) $(OBJ)/backup.exe $(OBJ)/full.o $(OBJ)/incremental.o $(OBJ)/versioned.o $(OBJ)/scheduled.o $(OBJ)/client.o
$(OBJ)/full.o: $(SRC)/full.c
	$(GCC) -g -Wall $(LFLAGS) $(OBJ)/full.o $(SRC)/full.c -c
$(OBJ)/incremental.o: $(SRC)/incremental.c
	$(GCC) -g -Wall $(LFLAGS) $(OBJ)/incremental.o $(SRC)/incremental.c -c
$(OBJ)/versioned.o: $(SRC)/versioned.c
	$(GCC) -g -Wall $(LFLAGS) $(OBJ)/versioned.o $(SRC)/versioned.c -c
$(OBJ)/scheduled.o: $(SRC)/scheduled.c
	$(GCC) -g -Wall $(LFLAGS) $(OBJ)/scheduled.o $(SRC)/scheduled.c -c
$(OBJ)/client.o: $(SRC)/client.c
	$(GCC) -g -Wall $(LFLAGS) $(OBJ)/client.o $(SRC)/client.c -c
$(OBJ)/server: $(SRC)/server.c
	$(GCC) $(SRC)/server.c -o $(OBJ)/server	
clean:
	rm $(OBJ)/*.exe $(OBJ)/*.o
	
