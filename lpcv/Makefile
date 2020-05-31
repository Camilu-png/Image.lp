all: lib/liblpcv.a

lib/liblpcv.a: bin/core.o bin/imgproc.o bin/kernels.o
	ar rcs lib/liblpcv.a bin/core.o bin/kernels.o bin/imgproc.o

bin/core.o: include/core.h src/core.c
	gcc -c src/core.c -o bin/core.o

bin/kernels.o: include/kernels.h src/kernels.c
	gcc -c src/kernels.c -o bin/kernels.o

bin/imgproc.o: include/imgproc.h src/kernels.c src/imgproc.c 
	gcc -c src/imgproc.c -o bin/imgproc.o

clean:
	rm lib/liblpcv.a bin/*.o