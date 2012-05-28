CC=gcc
OPTS=-Wall -pedantic -std=c99
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

APPFILE=randstr

all: $(APPFILE)

$(APPFILE): $(OBJECTS)
	$(CC) -o $@ $^

.c.o:
	$(CC) -c $(OPTS) $<

clean:
	rm $(APPFILE) $(OBJECTS)

install:
	cp $(APPFILE) /usr/local/bin/

uninstall:
	rm /usr/local/bin/$(APPFILE)

