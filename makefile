IDIR = ./include
CC = g++
CFLAGS = -I$(IDIR) -std=c++11 -g

ODIR = ./build
EDIR = ./bin
SDIR = ./src

_DEPS = process.h scheduler.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = simulator.o scheduler.o process.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# all: $(EDIR)/process $(EDIR)/scheduler $(EDIR)/simulator

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/simulator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# $(ODIR)/gl_sim.o: $(SDIR)/gl_sim.cpp
# 	$(CC) -c -o $@ $< $(CFLAGS)



.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EDIR)/*