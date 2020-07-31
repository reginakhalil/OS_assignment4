# Do not edit the contents of this file.
warnings_BAD: *.c
	gcc -Werror -Wall -g -std=gnu99 -o Assignment_1 *.c -lrt
	
warnings_OK: *.c
	gcc -Wall -g -std=gnu99 -o Assignment_1 *.c -lrt
	
clean: *.c
	rm Assignment_1




ROOTNAME=banker
CC=gcc
DEPS =
LIBS =pthread
OBJ = $(ROOTNAME).o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(ROOTNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -l $(LIBS)

clean:
	rm *.o $(ROOTNAME)