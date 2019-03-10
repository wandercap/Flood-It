CC = gcc
CFLAGS = -g -Wall -Wno-unused-result 

ODIR = bin
SDIR = src
IDIR = include

_DEPS = graph.h heap.h hashtable.h map.h util.h astar.h queue.h heuristics.h stack.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graph.o map.o hashtable.o heap.o floodit.o astar.o queue.o heuristics.o stack.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
floodit: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f floodit $(ODIR)/*.o
