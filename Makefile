.PHONY: clean test

CC=gcc

TEST_FLAGS=-std=c11 -g -fno-strict-aliasing -fno-strict-overflow

TEST_INCLUDES=-Isrc -IUnity/src -IUnity/extras/fixture/src

TEST_SOURCES=\
  Unity/src/unity.c \
  Unity/extras/fixture/src/unity_fixture.c \
  src/set1.c \
	test/test_set1.c \
	test/run_tests.c

test: build/run_tests.o
	$< -v

build/run_tests.o: build
	$(CC) $(TEST_INCLUDES) $(TEST_SOURCES) -o $@

build:
	mkdir build

clean: build
	rm build/* || true
