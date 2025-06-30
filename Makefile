CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -O2

SRC=$(wildcard src/*.cpp)

OUTDIR=bin
OUT=$(OUTDIR)/mercury

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -rf $(OUTDIR)
