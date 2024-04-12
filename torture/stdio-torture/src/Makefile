BIN_DIR = ../bin

SOURCES = $(wildcard *.c)
BINARIES = $(patsubst %.c, $(BIN_DIR)/%, $(SOURCES))

all: $(BINARIES)

$(BIN_DIR)/%: %.c
	$(CC) $(CFLAGS) -include stdio.h -include string.h -include stdlib.h $< -o $@

$(BIN_DIR)/20001011-1: 20001011-1.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@

$(BIN_DIR)/921110-1: 921110-1.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/980709-1: 980709-1.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/scope-2: scope-2.c ;

# $(BIN_DIR)/complex-6: complex-6.c

# $(BIN_DIR)/builtin-complex-1: builtin-complex-1.c

$(BIN_DIR)/string-opt-2: string-opt-2.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

$(BIN_DIR)/string-opt-5: string-opt-5.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

$(BIN_DIR)/string-opt-6: string-opt-6.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-7: string-opt-7.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-8: string-opt-8.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-9: string-opt-9.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-10: string-opt-10.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-11: string-opt-11.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-12: string-opt-12.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-13: string-opt-13.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-14: string-opt-14.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-15: string-opt-15.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/string-opt-17: string-opt-17.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

$(BIN_DIR)/va-arg-2: va-arg-2.c
	$(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

# $(BIN_DIR)/wchar_t-1: wchar_t-1.c
	# $(CC) $(CFLAGS) -include stdlib.h $< -o $@ -lm

clean:
	rm -f $(BINARIES)
