CXX=clang++
CXX_FLAGS=-std=c++20 -g -O2 -Wall -Wextra -Werror -Iincludes/
SRC_FILES=$(filter-out src/main.cc, $(wildcard src/**.cc src/**/*.cc src/**.cpp src/**/*.cpp)) # Automatically grab all files in folder, excluding main
TEST_DIR = tests


exec: bin/exec
	- $<

tests: vector_ray_tests sphere_tests

vector_ray_tests: bin/vector_ray_tests
	- $<

sphere_tests: bin/sphere_tests
	- $<

bin/exec: src/main.cc ${SRC_FILES}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} src/main.cc ${SRC_FILES} -o $@

bin/vector_ray_tests: tests/vector_ray_tests.cc ${SRC_FILES}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} tests/vector_ray_tests.cc ${SRC_FILES} -o $@

bin/sphere_tests: tests/sphere_tests.cc ${SRC_FILES}
	mkdir -p bin
	${CXX} ${CXX_FLAGS} tests/sphere_tests.cc ${SRC_FILES} -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*