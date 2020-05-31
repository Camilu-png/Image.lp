all: test_core test_flips test_color test_blur

test_core: test_core.o
	gcc test_core.c -L../lpcv/lib -llpcv -o test_core

test_core.o: test_core.c
	gcc -Wall -c test_core.c 

test_flips: test_flips.o
	gcc test_flips.c -L../lpcv/lib -llpcv -o test_flips

test_flips.o: test_flips.c
	gcc -Wall -c test_flips.c 

test_color: test_color.o
	gcc test_color.c -L../lpcv/lib -llpcv -o test_color

test_color.o: test_color.c
	gcc -Wall -c test_color.c 

test_blur: test_blur.o
	gcc test_blur.c -L../lpcv/lib -llpcv -o test_blur

test_blur.o: test_blur.c
	gcc -Wall -c test_blur.c 

clean:
	rm *.o test_core test_flips test_color test_blur