CC = gcc

OBJS = obj/main.o\
       obj/elf_helper.o\
       obj/memory.o

ODIR = obj
SDIR = src
BDIR = bin
BIN = wild

INCLUDE = -I./include

all: CFLAGS = 
all: $(BDIR)/$(BIN)

debug: CFLAGS = -g
debug: $(BDIR)/$(BIN)

$(BDIR)/$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(BDIR)/$(BIN)


$(ODIR)/%.o: $(SDIR)/%.c  
	$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@

clear:
	rm -f $(OBJS)
