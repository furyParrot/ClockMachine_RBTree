objects = output/main.o \
output/clockin_machine.o \
output/usr_time.o \
output/usr_sql3.o

clkmachine: $(objects)
	gcc $^ -o $@ -l sqlite3 -D __TEST__
output/main.o: ../src/main.c
	gcc -c $^ -o output/main.o
output/clockin_machine.o: ../src/cfiles/clockin_machine.c
	gcc -c $^ -o output/clockin_machine.o
output/usr_time.o: ../src/cfiles/usr_time.c
	gcc -c $^ -o output/usr_time.o
output/usr_sql3.o: ../src/cfiles/usr_sql3.c
	gcc -c $^ -o output/usr_sql3.o
clean:
	rm output/*.o clkmachine