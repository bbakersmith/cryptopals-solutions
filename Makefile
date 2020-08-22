.PHONY: clean test

CC=gcc

CCFLAGS=-std=c11 -g -Wall -fno-strict-aliasing -fno-strict-overflow

INCLUDES=-Iinclude

SOURCES=$(wildcard src/*.c)

LIBRARIES=-lm

TEST_INCLUDES=$(INCLUDES) -IUnity/src -IUnity/extras/fixture/src

TEST_SOURCES=\
  Unity/src/unity.c \
  Unity/extras/fixture/src/unity_fixture.c \
	$(SOURCES) \
	$(wildcard test/test_*.c) \
	test/run_tests.c

test: build/run_tests.o
	$< -v

build/run_tests.o: build
	$(CC) $(CCFLAGS) $(TEST_INCLUDES) $(TEST_SOURCES) $(LIBRARIES) -o $@

build:
	mkdir build

clean: build
	rm build/* || true

build/1.3:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) $(LIBRARIES) bin/1.3.c -o $@

build/1.4:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) $(LIBRARIES) bin/1.4.c -o $@

build/1.6:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) $(LIBRARIES) bin/1.6.c -o $@
