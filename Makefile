all: pi1 pi4 pi3 pi2

p1: practica3/pi1.c
	gcc -o bin/pi1 practica3/pi1.c

p3: practica3/pi3.c
	gcc -o bin/pi3 practica3/pi3.c

p4: practica3/pi4.c
	gcc -o bin/pi4 practica3/pi4.c

p2: practica3/pi2.c
	gcc -o bin/pi2 practica3/pi2.c -lpthread

clean:
	rm bin/pi1 bin/pi2 bin/pi3 bin/pi4
