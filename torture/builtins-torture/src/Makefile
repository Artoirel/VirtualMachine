BIN_DIR = ../bin

SOURCES = $(wildcard *.c)
BINARIES = $(patsubst %.c, $(BIN_DIR)/%, $(SOURCES))

all: $(BINARIES)

# do nothing for the *-lib.c files
$(BIN_DIR)/%-lib: %-lib.c ; 

$(BIN_DIR)/%: %.c %-lib.c lib/main.c
	$(CC) $(CFLAGS) $^ -o $@

# these fail to run with -O3, use -O0
$(BIN_DIR)/complex-1: complex-1.c complex-1-lib.c lib/main.c
	$(CC) $(CFLAGS) -O0 $^ -o $@

$(BIN_DIR)/memops-asm: memops-asm.c memops-asm-lib.c lib/main.c
	$(CC) $(CFLAGS) -O0 $^ -o $@

$(BIN_DIR)/pr22237: pr22237.c pr22237-lib.c lib/main.c
	$(CC) $(CFLAGS) -O0 $^ -o $@

$(BIN_DIR)/abs-1: abs-1.c abs-1-lib.c lib/main.c
	$(CC) $(CFLAGS) -O0 $^ -o $@

# uses tgkill()
# $(BIN_DIR)/complex-1: ;
# $(BIN_DIR)/abs-1: ;
# $(BIN_DIR)/memops-asm: ;
# $(BIN_DIR)/pr22237: ;

clean:
	rm -f $(BINARIES)
