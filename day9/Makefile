SRC := $(wildcard *.cc)
BIN := $(SRC:.cc=.x)
CXXFLAGS := -Wall -std=c++11

first: build
	./$(BIN) input.txt

test-first: build
	./$(BIN) test_input1.txt

second:

build: $(BIN)

%.x: %.cc
	@g++ $(CXXFLAGS) -o $@ $<

clean:
	-rm $(BIN)
