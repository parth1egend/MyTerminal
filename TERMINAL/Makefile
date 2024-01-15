all: terminal.o myls.o mycp.o mymv.o myps.o mygrep.c
	gcc terminal.o myls.o mycp.o mymv.o myps.o mygrep.c -lreadline -o terminal && rm *.o
terminal.o: terminal.c myhead.h
	gcc -c terminal.c
myls.o: myls.c myhead.h
	gcc -c myls.c
mycp.o: mycp.c myhead.h
	gcc -c mycp.c
mymv.o: mymv.c myhead.h
	gcc -c mymv.c
myps.o: myps.c myhead.h
	gcc -c myps.c
mygrep.o: mygrep.c myhead.h
	gcc -c mygrep.c
