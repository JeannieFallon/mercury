CXX=clang++
CXXFLAGS=-std=c++17 -Wall -Wextra -O2

SRC=$(wildcard src/*.cpp)
OUT=mercury

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
