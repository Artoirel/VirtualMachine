CC = /usr/local/bin/riscv64-unknown-linux-gnu-gcc
CFLAGS = -O0 -static 

# export all variables to the sub-makes
export

all:
	@echo "Building all torture tests with CFLAGS: $(CFLAGS)"
	$(MAKE) -C gcc-torture/src
	$(MAKE) -C fp-torture/src
	$(MAKE) -C stdio-torture/src
	$(MAKE) -C builtins-torture/src

.PHONY: gcc-torture
gcc-torture:
	$(MAKE) -C gcc-torture/src

.PHONY: fp-torture
fp-torture:
	$(MAKE) -C fp-torture/src

.PHONY: stdio-torture
stdio-torture:
	$(MAKE) -C stdio-torture/src

.PHONY: bulitins-torture
builtins-torture:
	$(MAKE) -C builtins-torture/src

clean:
	$(MAKE) -C gcc-torture/src clean
	$(MAKE) -C fp-torture/src clean
	$(MAKE) -C stdio-torture/src clean
	$(MAKE) -C builtins-torture/src clean

