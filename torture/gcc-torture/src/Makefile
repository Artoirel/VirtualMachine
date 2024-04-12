BIN_DIR = ../bin

SOURCES = $(wildcard *.c)
BINARIES = $(patsubst %.c, $(BIN_DIR)/%, $(SOURCES))

all: $(BINARIES)

$(BIN_DIR)/%: %.c
	$(CC) $(CFLAGS) -include stdio.h -include string.h -include stdlib.h $^ -o $@

$(BIN_DIR)/20001011-1: 20001011-1.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@

$(BIN_DIR)/20011024-1: 20011024-1.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@

$(BIN_DIR)/20030715-1: 20030715-1.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@

$(BIN_DIR)/20041214-1: 20041214-1.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/20050218-1: 20050218-1.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/20050502-1: 20050502-1.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/20050502-2: 20050502-2.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/20090711-1: 20090711-1.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/921007-1: 921007-1.c
	$(CC) $(CFLAGS)  -include stdlib.h $^ -o $@ 

$(BIN_DIR)/921110-1: 921110-1.c
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/980526-2: 980526-2.c
	$(CC) $(CFLAGS)  $^ -o $@ 

# $(BIN_DIR)/980709-1: 980709-1.c
# 	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

$(BIN_DIR)/built-in-setjmp: built-in-setjmp.c
	$(CC) $(CFLAGS)  $^ -o $@ 

# $(BIN_DIR)/float-floor: float-floor.c
# 	$(CC) $(CFLAGS)  $^ -o $@ -lm 

$(BIN_DIR)/p18298: p18298.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/pr30778: pr30778.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/pr33631: pr33631.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/pr42833: pr42833.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/pr43987: pr43987.c
	$(CC) $(CFLAGS)  $^ -o $@ 

$(BIN_DIR)/va-arg-2: va-arg-2.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

$(BIN_DIR)/string-opt-2: string-opt-2.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

$(BIN_DIR)/string-opt-5: string-opt-5.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

$(BIN_DIR)/string-opt-6: string-opt-6.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

$(BIN_DIR)/string-opt-18: string-opt-18.c
	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@

# these targets fail for one reason or another

$(BIN_DIR)/nestfunc-3: nestfunc-3.c ;
$(BIN_DIR)/nestfunc-5: nestfunc-5.c ;
$(BIN_DIR)/nestfunc-6: nestfunc-6.c ;
$(BIN_DIR)/20000822-1: 20000822-1.c ;

$(BIN_DIR)/string-opt-7: string-opt-7.c ;

$(BIN_DIR)/string-opt-8: string-opt-8.c ;

$(BIN_DIR)/string-opt-9: string-opt-9.c ;

$(BIN_DIR)/string-opt-10: string-opt-10.c ;

$(BIN_DIR)/string-opt-11: string-opt-11.c ;

$(BIN_DIR)/string-opt-12: string-opt-12.c ;

$(BIN_DIR)/string-opt-13: string-opt-13.c ;

$(BIN_DIR)/string-opt-14: string-opt-14.c ;

$(BIN_DIR)/string-opt-15: string-opt-15.c ;

$(BIN_DIR)/string-opt-17: string-opt-17.c ;

$(BIN_DIR)/wchar_t-1: wchar_t-1.c ;

$(BIN_DIR)/scope-2: scope-2.c ;

$(BIN_DIR)/complex-6: complex-6.c ;

$(BIN_DIR)/builtin-complex-1: builtin-complex-1.c ;

# $(BIN_DIR)/980709-1: 980709-1.c
# 	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

# $(BIN_DIR)/float-floor: float-floor.c
# 	$(CC) $(CFLAGS) -include stdlib.h $^ -o $@ -lm

# these fail with -O3
$(BIN_DIR)/stdarg-3: stdarg-3.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/stdarg-4: stdarg-4.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/981130-1: 981130-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/20030914-1: 20030914-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/eeprof-1: eeprof-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/980709-1: 980709-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ -lm 

$(BIN_DIR)/20020508-1: 20020508-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/complex-7: complex-7.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/regstack-1: regstack-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/va-arg-pack-1: va-arg-pack-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/stdarg-1: stdarg-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/20070919-1: 20070919-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/20071202-1: 20071202-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/float-floor: float-floor.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ -lm 

$(BIN_DIR)/pr23047: pr23047.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/pr39228: pr39228.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/20020226-1: 20020226-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/memcpy-2: memcpy-2.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/va-arg-12: va-arg-12.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/floatunsisf-1: floatunsisf-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/20040625-1: 20040625-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/20080502-1: 20080502-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/va-arg-22: va-arg-22.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/stdarg-2: stdarg-2.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/pr42691: pr42691.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

$(BIN_DIR)/960215-1: 960215-1.c
	$(CC) $(CFLAGS) -O0 -include stdlib.h $^ -o $@ 

# end -O0

# calls tgkill()
# $(BIN_DIR)/stdarg-3: stdarg-3.c ;
# $(BIN_DIR)/pr35456: pr35456.c ;
# $(BIN_DIR)/980709-1: 980709-1.c ;
# $(BIN_DIR)/va-arg-5: va-arg-5.c ;
# $(BIN_DIR)/eeprof-1: eeprof-1.c ;
# $(BIN_DIR)/nest-stdar-1: nest-stdar-1.c ;
# $(BIN_DIR)/va-arg-pack-1: va-arg-pack-1.c ;
# $(BIN_DIR)/struct-ret-1: struct-ret-1.c ;
# $(BIN_DIR)/stdarg-1: stdarg-1.c ;
# $(BIN_DIR)/va-arg-16: va-arg-16.c ;
# $(BIN_DIR)/va-arg-12: va-arg-12.c ;
# $(BIN_DIR)/va-arg-22: va-arg-22.c ;
# $(BIN_DIR)/stdarg-2: stdarg-2.c ;
# $(BIN_DIR)/pr42691: pr42691.c ;
# $(BIN_DIR)/float-floor: float-floor.c ;
# $(BIN_DIR)/floatunsisf-1: floatunsisf-1.c ;
# $(BIN_DIR)/pr23047: pr23047.c ;
# $(BIN_DIR)/pr39228: pr39228.c ;
# $(BIN_DIR)/pr44683: pr44683.c ;
# $(BIN_DIR)/980205: 980205.c ;
# $(BIN_DIR)/981130-1: 981130-1.c ;
# $(BIN_DIR)/20070919-1: 20070919-1.c ;
# $(BIN_DIR)/20071202-1: 20071202-1.c ;
# $(BIN_DIR)/memcpy-2: memcpy-2.c ;
# $(BIN_DIR)/20040625-1: 20040625-1.c ;
# $(BIN_DIR)/20030914-1: 20030914-1.c ;
# $(BIN_DIR)/regstack-1: regstack-1.c ;
# $(BIN_DIR)/20080502-1: 20080502-1.c ;
# $(BIN_DIR)/960215-1: 960215-1.c ;

clean:
	rm -f $(BINARIES)
