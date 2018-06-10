all: philphix 

test: philphix test.txt replace.txt
	touch output.txt
	rm output.txt
	cat test.txt | ./philphix replace.txt > output.txt
	echo "Difference between test output and reference output"
	diff output.txt reference.txt

test2: philphix test.txt replace.txt
	cat test.txt | ./philphix replace.txt

testedge: philphix
	@echo "Making the test files!"
	@echo
	@echo "A The" > edgeDict.txt
	@echo "e o" >> edgeDict.txt
	@echo -n "A cute dog.E" > edgetest.txt
	@echo -n "The cute dog.o" > edgeref.txt
	@echo "================Running Program...================="
	cat edgetest.txt | ./philphix edgeDict.txt > edgeout.txt
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff edgeref.txt edgeout.txt
	@echo "-----------------------None!-----------------------"
	@rm -f edgeDict.txt edgeout.txt edgeref.txt edgetest.txt
	@echo

testautogen: philphix
	python3 gendict.py
	touch output.txt
	rm output.txt
	cat newtest.txt | ./philphix newrep.txt > output.txt
	echo "Difference between test output and reference output"
	diff output.txt newref.txt

testnull: philphix
	echo "A A" > null.txt
	cat philphix | ./philphix null.txt > newphilphix
	echo "Difference between test output and reference output"
	diff philphix newphilphix

philphix: philphix.o hashtable.o
	gcc -g -Wall -o philphix philphix.o hashtable.o

philphix.o: philphix.c philphix.h hashtable.h
	gcc -g -c -Wall philphix.c

hashtable.o: hashtable.c hashtable.h
	gcc -g -c -Wall hashtable.c

clean:
	rm -f *.o philphix
