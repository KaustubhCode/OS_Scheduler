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

all: $(EDIR)/simulator

$(ODIR)/process.o: $(SDIR)/process.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/scheduler.o: $(SDIR)/scheduler.cpp $(IDIR)/process.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/simulator.o: $(SDIR)/simulator.cpp $(IDIR)/scheduler.h $(IDIR)/process.h
	$(CC) -c -o $@ $< $(CFLAGS)

# $(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/simulator: $(ODIR)/process.o $(ODIR)/scheduler.o $(ODIR)/simulator.o
	$(CC) -o $@ $^ $(CFLAGS)

# $(ODIR)/gl_sim.o: $(SDIR)/gl_sim.cpp
# 	$(CC) -c -o $@ $< $(CFLAGS)



.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EDIR)/*