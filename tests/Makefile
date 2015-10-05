CC = ~/sandbox/gcc/bin/g++
CFLAGS = -Wall -std=c++1y
RUN = ./a.out

test = $(CC) $(CFLAGS)

.PHONY: all
all: mst heap lru

mst:
	@if $(CC) $(CFLAGS) mst_test.cc && $(RUN); then echo "mst: All test passed."; fi

heap:
	@if $(CC) $(CFLAGS) heap_test.cc && $(RUN); then echo "heap: All test passed."; fi

lru:
	@if $(CC) $(CFLAGS) lru_test.cc && $(RUN); then echo "LRU: All test passed."; fi

clean:
	rm *.out
