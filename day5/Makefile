

test-prep: test_input1.txt
	@head -n 1 $< > seeds.txt
	@tail -n +3 $< > maps.txt
	@echo "" >> maps.txt

prep: input.txt
	@head -n 1 $< > seeds.txt
	@tail -n +3 $< > maps.txt
	@echo "" >> maps.txt

first: part1.x prep
	@./$< maps.txt seeds.txt | grep "Minsta f"

second: part1.x prep
	@./$< maps.txt seeds.txt | grep "Minsta andra"

part1.x: part1.cc
	@g++ -Wall -std=c++11 -o $@ $<

clean:
	-rm part1.x maps.txt seeds.txt
