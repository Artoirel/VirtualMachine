CC = gcc
RCC = riscv-unknown-linux-gcc

OBJS = obj/main.o\
       obj/elf_helper.o\
       obj/memory.o\
       obj/register_file.o

TOBJS = test/helloworld.o

ODIR = obj
SDIR = src
BDIR = bin
BIN = vm
RBIN = helloworld

INCLUDE = -I./include

all: CFLAGS =
all: TFLAGS = -static
all: $(BDIR)/$(BIN)

debug: CFLAGS = -g
debug: $(BDIR)/$(BIN)

$(BDIR)/$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(BDIR)/$(BIN)
	$(RCC) $(TFLAGS) $(TOBJS) -o test/$(RBIN)


$(ODIR)/%.o: $(SDIR)/%.c  
	$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@
	$(RCC) -c $(TFLAGS) $< -o $@

clear:
	rm -f $(OBJS)
