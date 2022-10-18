cunit_tests: cunit_file.o fileA.o fileA_suite.o fileB.o fileB_suite.o fileC.o fileC_suite.o
	gcc -o bin/file.tests bin/cunit_file.o bin/fileA.o bin/fileA_suite.o bin/fileB.o bin/fileB_suite.o bin/fileC.o bin/fileC_suite.o -lcunit

cunit_file.o: src/cunit_file.c
	gcc -o bin/cunit_file.o -c src/cunit_file.c 
fileA.o: src/fileA.c
	gcc -o bin/fileA.o -c src/fileA.c 

fileA_suite.o: src/fileA_suite.c
	gcc -o bin/fileA_suite.o -c src/fileA_suite.c

fileB.o: src/fileB.c
	gcc -o bin/fileB.o -c src/fileB.c

fileB_suite.o: src/fileB_suite.c src/fileB.c 
	gcc -o bin/fileB_suite.o -c src/fileB_suite.c

fileC.o: src/fileC.c
	gcc -o bin/fileC.o -c src/fileC.c

fileC_suite.o: src/fileC_suite.c src/fileC.c 
	gcc -o bin/fileC_suite.o -c src/fileC_suite.c

clean: 
	echo "Cleaning files ..."
	rm bin/cunit_tests  bin/cunit_file.o bin/fileA.o bin/fileA_suite.o bin/fileB.o bin/fileB_suite.o bin/fileC.o bin/fileC_suite.o
