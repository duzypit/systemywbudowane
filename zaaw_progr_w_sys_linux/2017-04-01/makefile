cc = gcc
#cc = ~/embedded_C/buildroot-build/host/usr/bin/i586-buildroot-linux-uclibc-gcc

all: main

sample_lib.o: sample_lib.c
	$(cc) -c -fpic -Werror -Wall -o sample_lib.o sample_lib.c

libsample_lib.so: sample_lib.o
	$(cc) -shared -o libsample_lib.so sample_lib.o

main.o: main.c
	$(cc) -c -o main.o main.c

main: main.o libsample_lib.so
	$(cc) -L/home/user/zut/programowanie_c/04 -Wall -o main main.o -lsample_lib

clean:
	-rm -rf *.o *.so

