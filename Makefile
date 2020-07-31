# Do not edit the contents of this file.
ROOTNAME=Assignment_4
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