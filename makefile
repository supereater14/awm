BINDIR=bin
LIBDIR=lib
OBJDIR=obj
SRCDIR=src

CC=gcc
CFLAGS=-O3 -s -Wall -Wextra -pedantic -I $(LIBDIR)
LFLAGS=-L/usr/X11/lib -lX11

BINS=$(BINDIR)/awm
OBJS=$(OBJDIR)/event_handler.o $(OBJDIR)/event_actions.o $(OBJDIR)/keybind.o \
     $(OBJDIR)/reaper.o

all: $(BINS) $(OBJS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c -o $@ $<

$(BINDIR)/% : $(SRCDIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(OBJS) $<

.PHONY: clean install remove

clean:
	rm -f $(BINS) $(OBJS)

install: bin/awm
	cp bin/awm /bin/
	cp awm.desktop /usr/share/xsessions/

remove:
	rm /bin/awm
	rm /usr/share/xsessions/awm.desktop
