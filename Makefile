TARGET = hostaliases.so
LIBS += -ldl
CC = gcc
MCFLAGS = -g -Wall -fPIC $(CFLAGS)
MLDFLAGS = -shared $(CFLAGS)
PREFIX = /usr/

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(MCFLAGS) $(MLDFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(MCFLAGS) $(MLDFLAGS) $(OBJECTS) $(LIBS) -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/lib/
	install -m 755 hostaliases.so $(DESTDIR)$(PREFIX)/lib/
	mkdir -p $(DESTDIR)/etc/profile.d/
	install -m 644 hostaliases.sh $(DESTDIR)/etc/profile.d/

clean:
	-rm -f *.o
	-rm -f $(TARGET)
