
prep-p2 input1.txt.prep.txt: input1.txt
	@cat $< | cut -d: -f2 | sed -Ee 's!([^0-9])([0-9])([^0-9])!\10\2\3!g' \
               | sed -Ee 's!([0-9]+) red!\1r!g' \
               | sed -Ee 's!([0-9]+) blue!\1b!g' \
               | sed -Ee 's!([0-9]+) green!\1g!g' \
               | sed -Ee 's![ ,;]!!g' > $<.prep.txt

clean:
	-rm *.prep.txt parts.x

parts.x: parts.c
	@gcc -o $@ $<

first:
	./part1.sh input1.txt

second: input1.txt.prep.txt parts.x
	./parts.x $<
