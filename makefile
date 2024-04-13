CC = gcc
RCC = riscv-unknown-linux-gcc

OBJS = obj/main.o\
       obj/elf_helper.o\
       obj/memory.o\
       obj/register_file.o\
       obj/decode.o\
       obj/util.o

TOBJS = test/helloworld.o

ODIR = obj
SDIR = src
BDIR = bin
BIN = vm

INCLUDE = -I./include

all: CFLAGS = -O3 -Wall -Wextra
all: $(BDIR)/$(BIN)

debug: CFLAGS = -g
debug: $(BDIR)/$(BIN)

$(BDIR)/$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(BDIR)/$(BIN)



$(ODIR)/%.o: $(SDIR)/%.c  
	$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@


clear:
	rm -f $(OBJS)
