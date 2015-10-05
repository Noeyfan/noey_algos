CC = ~/sandbox/gcc/bin/g++
CFLAGS = -Wall -std=c++1y
SOURCES = *.cc
COMMAND = ./a.out

test = $(CC) $(CFLAGS)

mst:
	@echo Testing ...
	@if $(CC) $(CFLAGS) mst_test.cc && $(COMMAND); then echo "All test passed."; fi

heap:
	@echo Testing ...
	@if $(CC) $(CFLAGS) heap_test.cc && $(COMMAND); then echo "All test passed."; fi

lru:
	@echo Testing ...
	@if $(CC) $(CFLAGS) lru_test.cc && $(COMMAND); then echo "All test passed."; fi

all:
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	rm *.out
