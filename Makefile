# Linux/Unix vsmake's standar Makefile 
# Works with:  g++ -Wall -lstdc++ -I./include src/*.cpp -o vsmake

CUSTOM_INCLUDES = -I./include

CPP = g++
CPPFLAGS = -Wall -lstdc++
CPPDEFS = -DNDEBUG
CPP_FILES = $(wildcard src/*.cpp)

prefix = /usr/local
bindir = $(prefix)/bin


ALL: vsmake

vsmake: $(CPP_FILES)
	$(CPP) $(CPPFLAGS) $(CUSTOM_INCLUDES) $(CPP_FILES) -o $@

all: ALL

CLEAN::
	-@rm -f vsmake
clean: CLEAN


install: vsmake
	install -m 0755 vsmake $(bindir)

.PHONY: install


