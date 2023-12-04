

first: input1.txt
	./part1.sh input1.txt

second: part2.x input1.txt
	./$?

test-second: part2.x test_input1.txt
	./$?

part2.x: part2.cc
	@g++ -std=c++11 -o $@ $<

clean:
	-rm part2.x
