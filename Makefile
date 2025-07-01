CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -O2

LDLIBS=-lcurl

SRC=$(wildcard src/*.cpp)

OUTDIR=bin
OUT=$(OUTDIR)/mercury

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LDLIBS)

clean:
	rm -rf $(OUTDIR)
