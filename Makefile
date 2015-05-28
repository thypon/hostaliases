TARGET = hostaliases.so
LIBS = -ldl
CC = gcc
CFLAGS = -g -Wall -fPIC
LDFLAGS = -shared
PREFIX = /usr/

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/lib/
	install -m 755 hostaliases.so $(DESTDIR)$(PREFIX)/lib/
	mkdir -p $(DESTDIR)/etc/profile.d/
	install -m 644 hostaliases.sh $(DESTDIR)/etc/profile.d/

clean:
	-rm -f *.o
	-rm -f $(TARGET)
