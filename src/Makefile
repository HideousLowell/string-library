.PHONY: all clean test s21_string.a check rebuild gcov open gcov_report
CC=gcc
FLAGS=-Werror -Wall -Wextra -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS = -lcheck
CFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: clean s21_string.a test

test: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) test.c s21_string.a -o test $(LIBS)
	./test
else
	$(CC) test.c s21_string.a -o test $(LIBS) $(LINUX)
	./test
endif

s21_string.a: s21_string.o s21_sprintf.o s21_sscanf.o
	ar rcs s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o
	cp s21_string.a libs21_string.a
	cp s21_string.a ls21_string.a
	ranlib libs21_string.a
	ranlib ls21_string.a

s21_string.o: s21_string.c
	$(CC) -c s21_string.c -o s21_string.o

s21_sprintf.o: s21_sprintf.c
	$(CC) -c s21_sprintf.c -o s21_sprintf.o

s21_sscanf.o: s21_sscanf.c
	$(CC) -c s21_sscanf.c -o s21_sscanf.o

gcov_report: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) test.c s21_string.c s21_sprintf.c s21_sscanf.c s21_string.a -o test $(LIBS)
else
	$(CC) $(CFLAGS) test.c s21_string.c s21_sprintf.c s21_sscanf.c s21_string.a -o test $(LIBS) $(LINUX)
endif
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

clean:
	rm -rf *.gc* *.o *.a *.out *.info test
	rm -rf report/

open:
	open report/index.html

rebuild: clean all

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	make test
	CK_FORK=no leaks --atExit -- ./test
	make clean