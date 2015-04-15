CC = gcc
CFLAGS = -Wall -Wextra 
LDFLAGS = 
RM = rm -rf
SRC = $(wildcard *.c)
OBJECTS = $(SRC:.c=.o)
TARGET = libsoul.a

BINDIR = .

all : $(OBJECTS)
	ar rs $(TARGET) $(OBJECTS) 
	$(RM) $(OBJECTS)

install : $(TARGET)
	cp -f $(TARGET) $(BINDIR)
	make clean

clean :
	$(RM) $(OBJECTS) $(TARGET)
	
