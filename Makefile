CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/
SRC_FILES=$(filter-out src/main.cc, $(wildcard src/**.cc src/**.cpp)) # Automatically grab all files in folder, excluding main

exec: bin/exec

tests: bin/tests

bin/exec: src/main.cc
	mkdir -p bin
	${CXX} ${CXX_FLAGS} src/main.cc ${SRC_FILES} -o $@
	

bin/tests: tests/tests.cc
	mkdir -p bin
	${CXX} ${CXX_FLAGS} tests/tests.cc ${SRC_FILES} -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*