.PHONY: clean test

CC=gcc

CCFLAGS=-std=c11 -g -fno-strict-aliasing -fno-strict-overflow

INCLUDES=-Isrc

SOURCES=src/set1.c

TEST_INCLUDES=$(INCLUDES) -IUnity/src -IUnity/extras/fixture/src

TEST_SOURCES=\
  Unity/src/unity.c \
  Unity/extras/fixture/src/unity_fixture.c \
	$(SOURCES) \
	test/test_set1.c \
	test/run_tests.c

test: build/run_tests.o
	$< -v

build/run_tests.o: build
	$(CC) $(CCFLAGS) $(TEST_INCLUDES) $(TEST_SOURCES) -o $@

build:
	mkdir build

clean: build
	rm build/* || true

build/1.3:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) bin/1.3.c -o $@
