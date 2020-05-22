Botball: botball.o main.o
	gcc -o Botball t1.o main.o; rm *.o
	
botball.o: botball.cc
	gcc -c -o botball.o botball.cc

main.o: main.c
	gcc -c -o main.o main.c

clean:
	rm *.o Botball