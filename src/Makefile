OS=$(shell uname -s)
CC=g++
STD=-std=c++17 -Wall# -Wextra -Werror
LDFLAGS=--coverage
TFLAGS=-lgtest -lpthread -lgtest_main
TFILE=test_array.cc test_list.cc test_map.cc test_queue.cc \
 	  test_set.cc test_stack.cc test_vector.cc
R=report
EXE=test.out

all: test

test:
	$(CC) $(STD) $(TFILE) -o $(EXE) $(TFLAGS)
	./test.out

clean:
	rm -rf *.out *.o *.dSYM *.dot *.gcda *.gcno report.* report/

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h
	rm -f .clang-format

gcov_report: clean
	$(CC) $(LDFLAGS) $(STD) $(TFILE) -o $(EXE) $(TFLAGS)
	./test.out
	lcov -t "test" --no-external -o $(R).info -c -d .
	genhtml -o $(R) $(R).info	
ifeq ($(OS), Darwin)
	open -a "Google Chrome" $(R)/index.html
else
	google-chrome $(R)/index.html
endif	

rebuild: clean test

install_gtest:
	sudo apt install -y libgtest-dev
	sudo apt install -y cmake
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp lib/*.a /usr/lib

install_clang_format:
ifeq ($(OS), Darwin)
	brew install clang-format -y
else	
	sudo apt install clang-format -y
endif

install_valgrind:
	sudo apt install -y valgrind

