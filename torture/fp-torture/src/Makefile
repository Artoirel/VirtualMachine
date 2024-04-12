BIN_DIR = ../bin

SOURCES = $(wildcard *.c)
BINARIES = $(patsubst %.c, $(BIN_DIR)/%, $(SOURCES))

all: $(BINARIES)

$(BIN_DIR)/%: %.c
	$(CC) $(CFLAGS) -include stdio.h -include string.h -include stdlib.h $< -o $@ -lm

$(BIN_DIR)/fp_sqrt_s: fp_sqrt_s.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

$(BIN_DIR)/20030331-1: 20030331-1.c
	$(CC) $(CFLAGS)  $< -o $@ -lm

# these fail to run with -O3, use -O0
$(BIN_DIR)/20010226-1: 20010226-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $< -o $@ 

$(BIN_DIR)/fp-cmp-3: fp-cmp-3.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $< -o $@ 

$(BIN_DIR)/fp-cmp-8l: fp-cmp-8l.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $< -o $@ 

$(BIN_DIR)/fp-cmp-4l: fp-cmp-4l.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $< -o $@ 

$(BIN_DIR)/mzero3: mzero3.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $< -o $@ 

$(BIN_DIR)/mzero2: mzero2.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $< -o $@ 

# calls tgkill()
# $(BIN_DIR)/mzero6: mzero6.c ;
# $(BIN_DIR)/pr38016: pr38016.c ;
# $(BIN_DIR)/fp-cmp-8l: fp-cmp-8l.c ;
# $(BIN_DIR)/fp-cmp-8: fp-cmp-8.c ;
# $(BIN_DIR)/20010226-1: 20010226-1.c ;
# $(BIN_DIR)/fp-cmp-3: fp-cmp-3.c ;
# $(BIN_DIR)/fp-cmp-4l: fp-cmp-4l.c ;
# $(BIN_DIR)/mzero3: mzero3.c ;

clean:
	rm -f $(BINARIES)
