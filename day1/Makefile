
first:
	@/bin/echo -n "First answer: "
	@./run.sh input1.txt

second: run.x
	@./run.x -f > first.txt
	@./run.x > second.txt
	@/bin/echo -n "Second answer: "
	@echo $$(paste -d'\0' first.txt second.txt | tr '\n' '+' ) 0 | bc

run.x: run.cc
	@g++ -o $@ $<

clean:
	@-rm first.txt second.txt run.x
