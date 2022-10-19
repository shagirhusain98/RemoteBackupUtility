main: full.o incremental.o versioned.o scheduled.o client.o
	gcc -g -o ./obj/backup.exe ./obj/full.o ./obj/incremental.o ./obj/versioned.o ./obj/scheldued.o ./client.o
full.o: ./src/full.c
	gcc -g -Wall -o ./obj/full.o ./src/full.c -c
incremental.o: ./src/incremental.c
	gcc -g -Wall -o ./obj/incremental.o ./src/incremental.c -c
versioned.o: ./src/versioned.c
	gcc -g -Wall -o ./obj/versioned.o ./src/versioned.c -c
scheduled.o: ./src/scheduled.c
	gcc -g -Wall -o ./obj/scheduled.o ./src/scheduled.c -c
client.o: ./src/client.c
	gcc -g -Wall -o ./obj/client.o ./src/client.c -c
clean:
	rm ./obj/*.exe ./obj/*.o
