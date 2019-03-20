round:round.c
	gcc -o round round.c

round-test:round
	./round -h 10485760
	./round -K 1024
	./round -M 10485760
	./round -G 11529215046
	./round -E 1152921504606846976
	./round 1024

my_seq:my_seq.c
	gcc -o my_seq my_seq.c

my_seq-test:my_seq
	./my_seq 10
	./my_seq 3 4 17
	./my_seq -w 2 3 30

my_grep:my_grep.c
	gcc -o my_grep my_grep.c

my_grep-test:my_grep
	./my_grep -n -c love when_u_are_old.txt
	./my_grep -v love when_u_are_old.txt

my_hexdump:my_hexdump.c
	gcc -o my_hexdump my_hexdump.c

my_hexdump-test:my_hexdump
	./my_hexdump when_u_are_old.txt

clean:
	rm -f round.exe my_seq.exe my_grep.exe my_hexdump.exe
