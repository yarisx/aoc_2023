SRC := $(wildcard *.cc)
BIN := $(SRC:.cc=.x)
CXXFLAGS := -Wall -std=c++11

first: build
	./$(BIN) input.txt 1

test-first: build
	./$(BIN) test_input1.txt 1

second: build
	./$(BIN) input.txt 2

test-second: build
	./$(BIN) test_input1.txt 2

build: $(BIN)

%.x: %.cc
	@g++ $(CXXFLAGS) -o $@ $<

clean:
	-rm $(BIN)
