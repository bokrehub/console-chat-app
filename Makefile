# Makefile

# Variables
FILE = $(F).cpp


#clreate FLAG variable and include -lboost_system
FLAG = -lboost_system

# Default target
all: $(FILE)
	mkdir -p bin
	g++ $(FILE) $(FLAG) -o  bin/$(F)

# Target to run the program
run: bin/$(F)
	bin/$(F)

# Target to clean up the directory
clean:
	rm -rf bin/
