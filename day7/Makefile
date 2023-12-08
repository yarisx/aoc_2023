
first: part.x input.txt
	@./$? 1

second: part.x input.txt
	@./$? 2

part.x: part.cc
	@g++ -std=c++11 -Wall $< -o $@

clean:
	-rm part.x
